/*
  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program. If not, see <http://www.gnu.org/licenses/>.

  Original code credit: DIYOSEPP - EspUnoWifi  =>  https://github.com/DIYOSEPP/EspUnoWiFi

  ATTENTION: INSTALL LIBRARY WebSockets by Markus Sattler FIRST!!!
  
  Modified by Claudio Raccomandato 02/12/2020
*/

#include <Arduino.h>
#include <ArduinoOTA.h>
#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WebSocketsServer.h>
#include <WiFiUdp.h>
#include <math.h>
#include <pgmspace.h>
#include "html.h"

//*****************************************************************************************************************************************************************
// CONFIGURATION
//*****************************************************************************************************************************************************************

#define DEFAULT_AP_SSID "esp-bridge"    // default ssid access point
#define DEFAULT_AP_PSWD ""              // default password access point, deve contenere ALMENO 8 caratteri, lasciare vuota per avere la connessione aperta
#define RST_TARGET_PIN 2                // pin collegato al reset dell'arduino
#define AP_WIFI_CHANNEL 11               // canale di comunicazione wifi (da 1 a 13)
//#define AP_UPLOAD_AUTHORIZATION         // commetare se non si vuole chiesta la password per caricare il codice
#define VERSION "1.0.0a"                // la versione del codice 

//*****************************************************************************************************************************************************************

IPAddress gateway(192,168,4,1);
IPAddress submask(255,255,255,0);

#define eeprom_size 512
#pragma pack(push)
#pragma pack(1)
typedef struct {
    char flag[2];
    char apssid[32];
    char appswd[32];
    unsigned char apip[4];
    unsigned int bardrate;
    unsigned int bardrate_isp;
} EEPROM_CONFIG;
EEPROM_CONFIG econfig;
#pragma pack(pop)

const int resetPin = RST_TARGET_PIN;
void resetTarget() {
    pinMode(resetPin, OUTPUT_OPEN_DRAIN);
    digitalWrite(resetPin, LOW);
    delay(10);
    digitalWrite(resetPin, HIGH);
}

unsigned char read_page_buff[128];
unsigned char write_page_buff[sizeof(read_page_buff)];
int address = 0;
int baseaddr = 0;
int total_write = 0;
uint8_t dity = 0;

WiFiServer avrOTA(80);
WiFiClient avrOTA_Clients[8];
unsigned int avrOTA_Client_LastIndex = 0;

WiFiServer msgserver(8080);
WiFiClient msgclient;

WiFiUDP Udp;
IPAddress udp_address;
unsigned int udp_port = 0;
unsigned long udp_last = 0;

WebSocketsServer webSocket = WebSocketsServer(81);

//#define debug(fmt, ...)
// if(msgclient)if(msgclient.connected())msgclient.printf(fmt, ##__VA_ARGS__)
#define debug(...)

inline uint8_t ctoh(char c) {
    return (c & 0x10) ? /*0-9*/ c & 0xf : /*A-F, a-f*/ (c & 0xf) + 9;
}
const char *head_frm =
    "HTTP/1.1 %d OK\r\nContent-Type: "
    "text/html\r\nAccess-Control-Allow-Origin:*\r\nContent-Length: "
    "%d\r\nConnection : close\r\n\r\n";

void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload,
                    size_t lenght) {
    switch (type) {
        case WStype_DISCONNECTED:
            break;
        case WStype_CONNECTED:
            break;
        case WStype_TEXT:
        case WStype_BIN:
            Serial.write(payload, lenght);
            break;
    }
}

void save_eeprom() {
    EEPROM.put(0, econfig);
    EEPROM.commit();
}

void load_eeprom() {
    EEPROM.get(0, econfig);

    if (econfig.flag[0] != 0xaa || econfig.flag[1] != 0x55) {
        memset(&econfig, 0, sizeof(econfig));
        econfig.flag[0] = 0xaa;
        econfig.flag[1] = 0x55;
        save_eeprom();
    }
    if (econfig.bardrate == 0 || econfig.bardrate > 2000000)
        econfig.bardrate = 115200;
    if (econfig.bardrate_isp == 0 || econfig.bardrate_isp > 2000000)
        econfig.bardrate_isp = 115200;
    if (strlen(econfig.apssid) == 0) {
        strcpy(econfig.apssid, DEFAULT_AP_SSID);
        strcpy(econfig.appswd, DEFAULT_AP_PSWD);
    }
    if(econfig.apip[0] != 192){
        econfig.apip[0] = 192;
        econfig.apip[1] = 168;
        econfig.apip[2] = 1;
        econfig.apip[3] = 1;
    }
}

void setup() {
    EEPROM.begin(eeprom_size);
    load_eeprom();
    Serial.begin(econfig.bardrate);
    Serial.print("apip:");
    Serial.println(String(econfig.apip[0]) + "." + String(econfig.apip[1]) + "." + String(econfig.apip[2]) + "." + String(econfig.apip[3]));
    Serial.print("apssid:");
    Serial.println(econfig.apssid);
    Serial.print("appswd:");
    Serial.println(econfig.appswd);
    
    WiFi.mode(WIFI_AP);
    IPAddress ip(econfig.apip[0], econfig.apip[1], econfig.apip[2], econfig.apip[3]);
    WiFi.softAPConfig(ip, gateway, submask);
    if (strlen(econfig.apssid)) {
        if (strlen(econfig.appswd) < 8)
            WiFi.softAP(econfig.apssid, "", AP_WIFI_CHANNEL, false, 1);
        else
            WiFi.softAP(econfig.apssid, econfig.appswd, AP_WIFI_CHANNEL, false, 1);
    }

    resetTarget();

    if (strlen(econfig.apssid)) {
        ArduinoOTA.setHostname(econfig.apssid);
    }
#ifdef AP_UPLOAD_AUTHORIZATION
    if (strlen(econfig.appswd) > 0) 
    {
        ArduinoOTA.setPassword(econfig.appswd);
    }
#endif
    ArduinoOTA.begin();

    avrOTA.begin();
    msgserver.begin();

    webSocket.begin();
    webSocket.onEvent(webSocketEvent);

    Udp.begin(82);
}

void home_html(WiFiClient wc) {
    wc.setTimeout(10000);
    int dlen = strlen(econfig.apssid) -2;
    
    String localip = WiFi.softAPIP().toString();
    dlen += localip.length() - 2;

    String gate = gateway.toString();
    dlen += gate.length() - 2;
    
    String subnet = submask.toString();
    dlen += subnet.length() - 2;

    String dns = String(econfig.apssid) + ".local";
    dns.toLowerCase();
    dlen += dns.length() - 2;

    wc.printf(head_frm, 200, strlen_P(index_html) + dlen);
    wc.printf_P(index_html, localip.c_str(), econfig.apssid, localip.c_str(), subnet.c_str(), gate.c_str(), dns.c_str(), VERSION);
}

void setssid(WiFiClient wc) {
    String line;
    int contentLen = 0;
    do {
        line = wc.readStringUntil('\n');
        line.toLowerCase();
        if (line.indexOf("content-length") >= 0) {
            contentLen = line.substring(line.indexOf(':') + 1).toInt();
        }
    } while (line != String("\r"));

    char key[256];
    int pos = 0;
    char *value = NULL;
    char tssid[32];
    char tpswd[32];
    unsigned char tip[4];
    memset(tssid, 0, sizeof(tssid));
    memset(tpswd, 0, sizeof(tpswd));
    memset(tip, 0, sizeof(tip));
    while (contentLen) {
        char c = wc.read();
        contentLen--;
        if (c == '&' || contentLen == 0) {
            if (c != '&') key[pos++] = c;
            key[pos] = '\0';
            if (strstr_P(key, PSTR("ssid"))) {
                if (value) {
                    for (int i = 0; i < sizeof(tssid) - 1; i++) {
                        tssid[i] = value[i];
                        if (value[i] == '\0') break;
                    }
                }
            } else if (strstr_P(key, PSTR("pswd"))) {
                if (value) {
                    for (int i = 0; i < sizeof(tpswd) - 1; i++) {
                        tpswd[i] = value[i];
                        if (value[i] == '\0') break;
                    }
                }
            } else if (strstr_P(key, PSTR("ip"))) {
                if (value) {
                    String ip_s = String(value);
                    int dotIndex = ip_s.indexOf('.');
                    //  Search for the next dot just after the first
                    int secondDotIndex = ip_s.indexOf('.', dotIndex + 1);
                    //  Search for the next dot just after the second
                    int thirdDotIndex = ip_s.indexOf('.', secondDotIndex + 1);
                    tip[0] = (ip_s.substring(0, dotIndex)).toInt();
                    tip[1] = (ip_s.substring(dotIndex+1, secondDotIndex)).toInt();
                    tip[2] = (ip_s.substring(secondDotIndex+1, thirdDotIndex)).toInt();
                    tip[3] = (ip_s.substring(thirdDotIndex+1)).toInt();
                }
            }
            pos = 0;
            key[0] = '\0';
            value = NULL;
        } else if (c == '%') {
            c = ctoh(wc.read());
            c <<= 4;
            c |= ctoh(wc.read()) & 0x0f;
            contentLen -= 2;
            key[pos++] = c;
        } else if (c == '=') {
            key[pos++] = '\0';
            value = key + pos;
        } else if ((c != '\r') && (c != '\n')) {
            key[pos++] = c;
        }
        if (pos == sizeof(key)) break;
    }

    save_eeprom();
    strcpy(econfig.apssid, tssid);
    strcpy(econfig.appswd, tpswd);
    econfig.apip[0] = tip[0];
    econfig.apip[1] = tip[1];
    econfig.apip[2] = tip[2];
    econfig.apip[3] = tip[3];
    WiFi.softAPdisconnect();
    if (strlen(tssid)) {
        IPAddress ip(tip[0],tip[1],tip[2],tip[3]);
        WiFi.softAPConfig(ip, gateway, submask);
        if (strlen(tpswd) < 8)
            WiFi.softAP(tssid, "", AP_WIFI_CHANNEL, false, 1);
        else
            WiFi.softAP(tssid, tpswd, AP_WIFI_CHANNEL, false, 1);
    }
    MDNS.notifyAPChange();
    MDNS.update();
    save_eeprom();
    while (msgclient.availableForWrite()) msgclient.flush();
    while (wc.availableForWrite()) wc.flush();
    wc.stop();
    msgclient.stop();
    delay(100);
    ESP.restart(); //ESP.reset();
    //while (wc.availableForWrite()) wc.flush();
    //ESP.restart();//ESP.reset();
}

byte msgPipeBuff[512];
unsigned long last_time_tx = 0;
int last_time_tx_available = 0;
unsigned long last_time_tx_pass_tick = 0;
void loop() {
    static bool msdn_inited = false;
    if (!msdn_inited && WiFi.status() == WL_CONNECTED) {
        if (MDNS.begin(econfig.apssid)) {
            MDNS.enableArduino(8266);
            MDNS.addService("websock", "tcp", 81);
            MDNS.addService("message", "tcp", 8080);
            MDNS.addService("http", "tcp", 80);
            MDNS.addService("remotecontrol", "udp", 82);
            MDNS.update();
            msdn_inited = true;
        }
    }
    if (msdn_inited) MDNS.update();
    ArduinoOTA.handle();

    webSocket.loop();
    int n = 0;
    n = Udp.parsePacket();
    if (n) {
        while (n) {
            int len = Udp.read(
                msgPipeBuff, n > sizeof(msgPipeBuff) ? sizeof(msgPipeBuff) : n);
            Serial.write(msgPipeBuff, n);
            n -= len;
            delay(0);
        }
        udp_port = Udp.remotePort();
        udp_address = Udp.remoteIP();
        udp_last = millis();
    } else {
        if ((unsigned long)(millis() - udp_last) > 500) udp_port = 0;
    }

    if (msgserver.hasClient()) {
        if (msgclient) msgclient.stop();
        msgclient = msgserver.available();
        msgclient.setNoDelay(true);
    }

    if (msgclient && msgclient.connected()) {
        while (n = msgclient.available()) {
            n = msgclient.readBytes(
                msgPipeBuff, n > sizeof(msgPipeBuff) ? sizeof(msgPipeBuff) : n);
            Serial.write(msgPipeBuff, n);
            delay(0);
        }
    }
    n = Serial.available();
    if (n != last_time_tx_available) {
        last_time_tx_pass_tick = millis();
        last_time_tx_available = n;
    }
    bool tx = (millis() - last_time_tx > 30);
    tx = tx || (millis() - last_time_tx_pass_tick > 2);
    tx = tx && n;
    tx = tx || (n > sizeof(msgPipeBuff) / 2);
    if (tx) {
        do {
            n = Serial.available();
            n = Serial.readBytes(
                msgPipeBuff, n > sizeof(msgPipeBuff) ? sizeof(msgPipeBuff) : n);
            if (msgclient && msgclient.connected())
                msgclient.write(msgPipeBuff, n);
            webSocket.broadcastBIN(msgPipeBuff, n);
            if (udp_port) {
                Udp.beginPacket(udp_address, udp_port);
                Udp.write(msgPipeBuff, n);
                Udp.endPacket();
            }
            delay(0);
        } while (Serial.available() > sizeof(msgPipeBuff) / 4);
        last_time_tx = millis();
    }

    if (avrOTA.hasClient()) {
        avrOTA_Client_LastIndex++;
        int index;
        for (int i = 0; i < sizeof(avrOTA_Clients) / sizeof(avrOTA_Clients[0]);
             i++, avrOTA_Client_LastIndex++) {
            index = avrOTA_Client_LastIndex %
                    (sizeof(avrOTA_Clients) / sizeof(avrOTA_Clients[0]));
            if (!avrOTA_Clients[index]) break;
            if (!avrOTA_Clients[index].connected()) break;
        }

        avrOTA_Client_LastIndex %=
            (sizeof(avrOTA_Clients) / sizeof(avrOTA_Clients[0]));
        if (avrOTA_Clients[avrOTA_Client_LastIndex])
            avrOTA_Clients[avrOTA_Client_LastIndex].stop();
        avrOTA_Clients[avrOTA_Client_LastIndex] = avrOTA.available();
        avrOTA_Clients[avrOTA_Client_LastIndex].setNoDelay(true);
    }
    for (int i = 1; i <= sizeof(avrOTA_Clients) / sizeof(avrOTA_Clients[0]);
         i++) {
        WiFiClient avrOTA_client =
            avrOTA_Clients[(avrOTA_Client_LastIndex + i) %
                           (sizeof(avrOTA_Clients) /
                            sizeof(avrOTA_Clients[0]))];
        if (avrOTA_client && avrOTA_client.connected() &&
            avrOTA_client.available()) {
            String s = avrOTA_client.readStringUntil('\n');
            s.toLowerCase();

            int pos = s.lastIndexOf("baudrate=");
            if (pos > 0) {
                while (s[pos++] != '=')
                    ;
                unsigned int trate = 0;
                while (s[pos] >= '0' && s[pos] <= '9') {
                    trate *= 10;
                    trate += s[pos] - '0';
                    pos++;
                }
                if (trate > 0 && trate <= 2000000) {
                    if (econfig.bardrate != trate) {
                        econfig.bardrate = trate;
                        save_eeprom();
                        Serial.begin(trate);
                    }
                }
            }
            pos = s.lastIndexOf("baudrateisp=");
            if (pos > 0) {
                while (s[pos++] != '=')
                    ;
                unsigned int trate = 0;
                while (s[pos] >= '0' && s[pos] <= '9') {
                    trate *= 10;
                    trate += s[pos] - '0';
                    pos++;
                }
                if (trate > 0 && trate <= 2000000) {
                    if (econfig.bardrate_isp != trate) {
                        econfig.bardrate_isp = trate;
                        save_eeprom();
                    }
                }
            }
            if (s.indexOf("sync") > 0) {
                String respone("Esp8266 for UnoOTA, SYNC OK!");
                respone += millis();
                if (s.indexOf("post") >= 0) {
                    avrOTA_client.printf(head_frm, 204, respone.length());
                    avrOTA_client.print(respone);
                } else {
                    avrOTA_client.printf(head_frm, 200, respone.length());
                    avrOTA_client.print(respone);
                }
            } else if (s.indexOf("reset") > 0) {
                resetTarget();
                String respone("Reset OK!");
                respone += millis();
                avrOTA_client.printf(head_frm, 200, respone.length());
                avrOTA_client.print(respone);
            } else if (s.indexOf("resetEsp") > 0) {
                while (msgclient.availableForWrite()) msgclient.flush();
                while (avrOTA_client.availableForWrite()) avrOTA_client.flush();
                avrOTA_client.stop();
                msgclient.stop();
                delay(100);
                ESP.restart(); //ESP.reset();
            } else if (s.indexOf("upload") > 0) {
                String line;
                int hexLen = 0;
                do {
                    if (!avrOTA_client.available()) break;
                    line = avrOTA_client.readStringUntil('\n');
                    line.toLowerCase();
                    if (line.indexOf("content-length") >= 0) {
                        hexLen = line.substring(line.indexOf(':') + 1).toInt();
                    }
                } while (line != String("\r"));
                extern int handleHex(WiFiClient client, int hexlen);
                int handLen = handleHex(avrOTA_client, hexLen);
                Serial.begin(econfig.bardrate);
                if (handLen != hexLen) {
                    String respone("Upload Error!");
                    if (handLen < 0) {
                        respone += " can't entry bootloader!";
                    } else {
                        respone += " at Hex File(byte):";
                        respone += handLen;
                        respone += " total:";
                        respone += hexLen;
                        respone += ",";
                        respone += total_write;
                        respone += " bytes have been written";
                    }
                    avrOTA_client.printf(head_frm, 404, respone.length());
                    avrOTA_client.print(respone);
                } else {
                    String respone("Upload done! Flash used:");
                    respone += total_write;
                    respone += " bytes";
                    avrOTA_client.printf(head_frm, 200, respone.length());
                    avrOTA_client.print(respone);
                }
            } else if ((s.indexOf("setap") > 0) && (s.indexOf("post") >= 0)) {
                setssid(avrOTA_client);
            } else if (s.indexOf("/ http") > 0) {
                home_html(avrOTA_client);
            } else if (s.indexOf("getbaudrate") > 0) {
                String respone(econfig.bardrate);
                avrOTA_client.printf(head_frm, 200, respone.length());
                avrOTA_client.print(respone);
            } else {
                avrOTA_client.printf(head_frm, 404, 0);
            }
            avrOTA_client.flush();
            // avrOTA_client.stop();
        }
    }
}

#include "stk500.h"

#define MAX_SYNC_ATTEMPTS 10

static int stk500_send(unsigned char *buf, size_t len) {
    Serial.write(buf, len);
    return len;
}
static int stk500_send(unsigned char data) {
    Serial.write(data);
    return 1;
}

static int stk500_recv(unsigned char *buf, size_t len) {
    int i = 200;
    while (i && Serial.available() < (int)len) {
        delay(1);
        i--;
    }
    int rv = Serial.readBytes(buf, len);
    if (rv < 0) {
        debug("stk500_recv(): programmer is not responding\n");
        return -1;
    }

    return 0;
}

int stk500_drain() {
    while (Serial.available()) Serial.read();
    return 0;
}

int stk500_getsync() {
    unsigned char buf[32], resp[32];
    int attempt;

    /* get in sync */
    buf[0] = Cmnd_STK_GET_SYNC;
    buf[1] = Sync_CRC_EOP;

    /*
        First send and drain a few times to get rid of line noise
    */

    stk500_send(buf, 2);
    stk500_drain();
    stk500_send(buf, 2);
    stk500_drain();

    for (attempt = 0; attempt < MAX_SYNC_ATTEMPTS; attempt++) {
        stk500_send(buf, 2);
        stk500_recv(resp, 1);
        if (resp[0] == Resp_STK_INSYNC) {
            break;
        }
        debug("stk500_getsync() attempt %d of %d: not in sync: resp=0x%02x\n",
              attempt + 1, MAX_SYNC_ATTEMPTS, resp[0]);
    }
    if (attempt == MAX_SYNC_ATTEMPTS) {
        stk500_drain();
        return -1;
    }

    if (stk500_recv(resp, 1) < 0) return -1;
    if (resp[0] != Resp_STK_OK) {
        debug("stk500_getsync(): can't communicate with device: resp=0x%02x\n",
              resp[0]);
        return -1;
    }

    return 0;
}

static int stk500_loadaddr(unsigned int addr) {
    unsigned char buf[16];
    int tries;
    tries = 0;
retry:
    tries++;
    buf[0] = Cmnd_STK_LOAD_ADDRESS;
    buf[1] = addr & 0xff;
    buf[2] = (addr >> 8) & 0xff;
    buf[3] = Sync_CRC_EOP;

    stk500_send(buf, 4);

    if (stk500_recv(buf, 1) < 0) return -1;
    if (buf[0] == Resp_STK_NOSYNC) {
        if (tries > 33) {
            debug("stk500_loadaddr(): can't get into sync\n");
            return -1;
        }
        if (stk500_getsync() < 0) return -1;
        goto retry;
    } else if (buf[0] != Resp_STK_INSYNC) {
        debug(
            "stk500_loadaddr(): (a) protocol error, expect=0x%02x, "
            "resp=0x%02x\n",
            Resp_STK_INSYNC, buf[0]);
        return -1;
    }

    if (stk500_recv(buf, 1) < 0) return -1;
    if (buf[0] == Resp_STK_OK) {
        return 0;
    }

    debug("loadaddr(): (b) protocol error, expect=0x%02x, resp=0x%02x\n",
          Resp_STK_INSYNC, buf[0]);

    return -1;
}

static int stk500_paged_write(unsigned int addr, unsigned int n_bytes,
                              unsigned char *data) {
    unsigned char buf[16];

    int a_div;
    int block_size;
    int tries;
    unsigned int n;

    a_div = 2;
    block_size = 128;

    n = addr + n_bytes;

    for (; addr < n; addr += block_size) {
        tries = 0;
    retry:
        tries++;
        stk500_loadaddr(addr / a_div);
        stk500_send(Cmnd_STK_PROG_PAGE);
        stk500_send((block_size >> 8) & 0xff);
        stk500_send(block_size & 0xff);
        stk500_send('F');
        stk500_send(data, block_size);
        stk500_send(Sync_CRC_EOP);
        data += block_size;
        if (stk500_recv(buf, 1) < 0) return -1;
        if (buf[0] == Resp_STK_NOSYNC) {
            if (tries > 33) {
                debug("stk500_paged_write(): can't get into sync\n");
                return -3;
            }
            if (stk500_getsync() < 0) return -1;
            goto retry;
        } else if (buf[0] != Resp_STK_INSYNC) {
            debug(
                "stk500_paged_write(): (a) protocol error, expect=0x%02x, "
                "resp=0x%02x\n",
                Resp_STK_INSYNC, buf[0]);
            return -4;
        }

        if (stk500_recv(buf, 1) < 0) return -1;
        if (buf[0] != Resp_STK_OK) {
            debug(
                "stk500_paged_write(): (a) protocol error, expect=0x%02x, "
                "resp=0x%02x\n",
                Resp_STK_INSYNC, buf[0]);
            return -5;
        }
    }
    return n_bytes;
}

static int stk500_paged_load(unsigned int addr, unsigned int n_bytes,
                             unsigned char *data) {
    unsigned char buf[16];
    int a_div;
    int tries;
    unsigned int n;
    int block_size;

    a_div = 2;
    block_size = 128;

    n = addr + n_bytes;
    for (; addr < n; addr += block_size) {
        tries = 0;
    retry:
        tries++;
        stk500_loadaddr(addr / a_div);
        stk500_send(Cmnd_STK_READ_PAGE);
        stk500_send((block_size >> 8) & 0xff);
        stk500_send(block_size & 0xff);
        stk500_send('F');
        stk500_send(Sync_CRC_EOP);

        if (stk500_recv(buf, 1) < 0) return -1;
        if (buf[0] == Resp_STK_NOSYNC) {
            if (tries > 33) {
                debug("stk500_paged_load(): can't get into sync\n");
                return -3;
            }
            if (stk500_getsync() < 0) return -1;
            goto retry;
        } else if (buf[0] != Resp_STK_INSYNC) {
            debug(
                "stk500_paged_load(): (a) protocol error, "
                "expect=0x%02x, resp=0x%02x\n",
                Resp_STK_INSYNC, buf[0]);
            return -4;
        }

        if (stk500_recv(data, block_size) < 0) return -1;
        data += block_size;
        if (stk500_recv(buf, 1) < 0) return -1;

        if (buf[0] != Resp_STK_OK) {
            debug(
                "stk500_paged_load(): (a) protocol error, expect=0x%02x, "
                "resp=0x%02x\n",
                Resp_STK_OK, buf[0]);
            return -5;
        }
    }
    return n_bytes;
}

int pageCheck(int curAddress) {
    int page = address / sizeof(write_page_buff);
    int curpage = curAddress / sizeof(write_page_buff);
    if (page != curpage) {
        if (dity) {
            debug("write page:%04X\n", page * sizeof(write_page_buff));
            int wb =
                stk500_paged_write(page * sizeof(write_page_buff),
                                   sizeof(write_page_buff), write_page_buff);
            if (wb != sizeof(write_page_buff)) return -1;
            int rb = stk500_paged_load(page * sizeof(write_page_buff),
                                       sizeof(read_page_buff), read_page_buff);
            if (rb != sizeof(write_page_buff)) return -1;
            int err = 0;
            for (unsigned int ck = 0; ck < sizeof(write_page_buff); ck++)
                if (read_page_buff[ck] != write_page_buff[ck]) err++;
            if (err) return -1;
        }
        address = curAddress;
        memset(read_page_buff, 0xff, sizeof(read_page_buff));
        memset(write_page_buff, 0xff, sizeof(write_page_buff));
        dity = 0;
    }
    return 0;
}

int entryBootloader() {
    Serial.begin(econfig.bardrate_isp);
    resetTarget();
    delay(500);
    int i = 0;
    while (1) {
        while (Serial.available()) Serial.read();
        Serial.write(0x30);
        Serial.write(0x20);
        delay(10);
        i++;
        if (i > 500 / 10) {
            return 0;
        }
        if (Serial.available() > 1) {
            if (Serial.read() != 0x14) continue;
            if (Serial.read() != 0x10) continue;
            return 1;
        }
    }
}

int sigleRecord(uint8_t *data, int len) {
    uint8_t cs = 0;
    uint8_t recsize = ctoh(*data++);
    recsize <<= 4;
    recsize |= ctoh(*data++);
    cs = recsize;

    if ((recsize * 2 + (1 + 2 + 1 + 1) * 2) != len) return -1;

    uint16_t addr = ctoh(*data++);
    addr <<= 4;
    addr |= ctoh(*data++);
    cs += (uint8_t)addr;

    addr <<= 4;
    addr |= ctoh(*data++);
    addr <<= 4;
    addr |= ctoh(*data++);
    cs += (uint8_t)(addr & 0xff);

    uint8_t rectype = ctoh(*data++);
    rectype <<= 4;
    rectype |= ctoh(*data++);
    cs += rectype;
    debug("addr:%04X :", addr);
    uint8_t *phexdata = data;
    for (int i = 0; i < recsize; i++) {
        uint8_t d = ctoh(*data++);
        d <<= 4;
        d |= ctoh(*data++);
        cs += d;
        phexdata[i] = d;
    }
    uint8_t csd = ctoh(*data++);
    csd <<= 4;
    csd |= ctoh(*data++);
    cs += csd;
    if (cs) return -3;

    switch (rectype) {
        case 0:
            for (int i = 0; i < recsize; i++) {
                if (pageCheck(baseaddr + addr + i)) return -2;
                write_page_buff[(baseaddr + addr + i) %
                                sizeof(write_page_buff)] = phexdata[i];
            }
            debug("\n");
            if (recsize) dity = 1;
            total_write += recsize;
            break;
        case 1:
            if (pageCheck(address + sizeof(write_page_buff))) return -1;
            break;
        case 2:
            baseaddr = (phexdata[0] << 8 | phexdata[1]) << 4;
            return 0;
        case 3:
            return 0;
        case 4:
            baseaddr = (phexdata[0] << 8 | phexdata[1]) << 16;
            return 0;
        case 5:
            return 0;
        default:
            return rectype;
            break;
    }
    return rectype;
}

uint8_t lineBuff[128];
int handleHex(WiFiClient client, int hexlen) {
    while (client.connected() && client.available() == 0) {
        delay(1);
    }
    if (client.read() != ':') return 0;
    int totalLen = 0;
    address = -1;
    baseaddr = 0;
    dity = 0;
    total_write = 0;
    memset(read_page_buff, 0xff, sizeof(read_page_buff));
    memset(write_page_buff, 0xff, sizeof(write_page_buff));
    if (!entryBootloader())
        if (!entryBootloader())
            if (!entryBootloader()) return -1;
    while (client.connected()) {
        ArduinoOTA.handle();
        if (avrOTA.hasClient()) break;
        int rl = client.readBytesUntil(
            ':', lineBuff,
            min((int)sizeof(lineBuff) - 1, hexlen - totalLen - 1));
        int dlen = rl;
        if (dlen < 10) break;
        if (lineBuff[rl - 1] == '\n') dlen--;
        if (lineBuff[rl - 2] == '\r') dlen--;
        if (dlen < 10) break;
        if (dlen & 1) break;
        totalLen += rl + 1;
        if (sigleRecord(lineBuff, dlen)) break;
    }
    return totalLen;
}
