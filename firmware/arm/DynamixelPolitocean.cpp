#include "DynamixelPolitocean.h"

//SC16IS740 REGISTER ADDRESSES

#define THR        0x00 << 3
#define RHR        0x00 << 3
#define IER        0x01 << 3
#define FCR        0x02 << 3
#define IIR        0x02 << 3
#define LCR        0x03 << 3
#define MCR        0x04 << 3
#define LSR        0x05 << 3
#define MSR        0x06 << 3
#define SPR        0x07 << 3
#define TXLVL      0x08 << 3
#define RXLVL      0x09 << 3
#define DLAB       0x80 << 3
#define IODIR      0x0A << 3
#define IOSTATE    0x0B << 3
#define IOINTMSK   0x0C << 3
#define IOCTRL     0x0E << 3
#define EFCR       0x0F << 3

#define DLL        0x00 << 3
#define DLH        0x01 << 3
#define EFR        0x02 << 3

#define HEADER      0xFF


SC16IS740::SC16IS740(TwoWire& I2C_port, const int I2C_add, unsigned long freq = 16000000)
    :port(I2C_port), _deviceAddress(I2C_add), QUARTZ_freq(freq)
{}

//-------------------- private functions ---------------------------

char SC16IS740::readRegister(char regAddress) {
    port.beginTransmission(_deviceAddress);
    port.write(regAddress);
    port.endTransmission();
    port.requestFrom(_deviceAddress, 1);


    if (port.available()) {
        return port.read(); // read values in the input register
    }
    else return -1;
}

void SC16IS740::writeRegister(char regAddress, char data) {
    port.beginTransmission(_deviceAddress);
    port.write(regAddress);
    port.write(data);
    port.endTransmission();

}


//-------------------- public functions ---------------------------


void SC16IS740::setAddress(char addr)
{
    _deviceAddress = addr;
}

void SC16IS740::begin() {

    port.setClock(100000);          //I2C at max speed to avoid latencies 
    port.begin();                   //Wire.begin()      NECESSARY
    //default values : BAUDRATE = 57600 ; QUARTZ_freq = 16000000
    uint16_t presc;
    uint16_t divisor;
    presc = 1 + 3 * ((readRegister(MCR) & (1 << 7)) >> 7);
    divisor = QUARTZ_freq / (presc * baud_ * 16);

    writeRegister(LCR, 0x80);               // LCR[7] = 1 NEEDED TO PROGRAM BAUDRATE, DLL, DLH
    writeRegister(DLL, divisor & 0xFF);     //take only 8 LSBs
    writeRegister(DLH, divisor >> 8);       //take only 8 MSBs

    writeRegister(LCR, 0xBF);       // access EFR register
    //writeRegister(EFR, 0x10);     //enhanced functions enabled, BUT WE DONT USE THEM (hardware and software flow control)
    writeRegister(LCR, 0x03);       // 8 data bit, 1 stop bit, no parity, RETURN TO GENERAL REGISTER ADDRESSING
    writeRegister(IER, 0x00);       //INTERRUPT DISABLED
    writeRegister(FCR, 0x07);       //reset all the TX and RX FIFOs, FIFO MODE ON ==> HERE NOT SENT AND NOT READ MESSAGES ARE STORED IN RX AND TX FIFOS
    enableInvDirectionControl();    //RTS = 1 when transmitting, RTS = 0 otherwise

}

void SC16IS740::begin(unsigned long baud)
{

    baud_ = baud;
    this->begin();                  //call other function after changing the baudrate
}

void SC16IS740::setFreq(unsigned long freq = 16000000)
{
    QUARTZ_freq = freq;
    this->begin();        //start again with the new frequency
}


void SC16IS740::end(void)
{
    port.endTransmission();
}

void SC16IS740::flush()
{
    //writeRegister(FCR, 0x06); // reset TXFIFO, reset RXFIFO, non FIFO mode
    uint8_t tmp;

    do {
        tmp = readRegister(LSR);              //LSR[5] == 1 if there is data to be SENT, wait until data sent
    } while ((tmp & 0x20) == 0);
}


bool SC16IS740::available() {

    return readRegister(RXLVL);       //RXLVL = number of bytes available in the rx buffer. If 0 ==> no data received
}

char SC16IS740::read() {
    return readRegister(RHR);
}

void SC16IS740::write(char value) {

    writeRegister(THR, value);
    this->flush();                            //wait until ALL DATA IS SENT (TX FIFO EMPTY)

}

void SC16IS740::write(char* buf, unsigned int len) {
    //works fine
    for (int i = 0;i < len;i++)
    {
        writeRegister(THR, buf[i]);
    }
    this->flush();                            //wait until ALL DATA IS SENT (TX FIFO EMPTY)

}

void SC16IS740::enableRS485mode()
{
    writeRegister(EFCR, 0x01);     //9-bit mode ENABLED
}

void SC16IS740::enableDirectionControl()
{
    //WHEN TRANSMITTING, RTS PIN GOES AT 0, not useful to control the DE/RO pin of max485

    writeRegister(EFCR, 0x10);
}

void SC16IS740::enableInvDirectionControl()
{
    //WHEN TRANSMITTING, RTS PIN GOES AT 1 ==> CONNECT IT TO THE DE/RO PIN OF THE MAX 485

    writeRegister(EFCR, 0x30);           //RTSCONV = 1,RTSINVER = 1
}





//DYNAMIXEL FUNCTIONS


DynamixelPolitocean::DynamixelPolitocean(TwoWire& I2C_port, const int I2C_addr, unsigned char DXL_ID = 1, unsigned long freq = 16000000)
    :id(DXL_ID)
{
    sc16is740 = new SC16IS740(I2C_port, I2C_addr, freq);
    instr_packet[0] = HEADER;
    instr_packet[1] = HEADER;
    instr_packet[2] = id;
    //the values are correctly stored and created
}

DynamixelPolitocean::~DynamixelPolitocean()
{
    delete sc16is740;
}

void DynamixelPolitocean::begin(unsigned long baud = 57600)
{
    //enter correctly here
    sc16is740->begin(baud);
}

char DynamixelPolitocean::checksum(char* instrpacket, char dim)
{
    int sum = 0;
    char ret = 0;
    for (int i = 2;i < dim;i++)
    {
        sum += instrpacket[i];
    }
    //EXTRACT ONLY THE 8 LSBS
    ret = (char)sum;
    ret = ~ret;
    return ret;
}

bool DynamixelPolitocean::readStatusPacket(unsigned char exp_bytes)
{

    //SPECIFY NUMBER OF BYTES YOU WANT TO RETURN
    // 
    // WAITS UNTIL TIMEOUT ELAPSES = 100ms
    //RECEIVE STATUS PACKET : WE SHOULD RECEIVE : HEADER + HEADER + ID + LENGTH + ERROR + CHKSM , where LENGTH = 2
    unsigned int time = millis();
    int rxindex = 0;            //index of the rx data
    while (rxindex < exp_bytes)
    {
        //check if data is available
        if (sc16is740->available() == true)
        {
            //data arrived
            status_packet[rxindex] = sc16is740->read();
            rxindex++;
        }
        if (millis() - time > 100)
        {
            return 1;       //timeout elapsed
        }
    }
    if (status_packet[4] != 0)
    {
        //error detected
        return 2;
    }

    return 0;
}

bool DynamixelPolitocean::setGoalPosition(int position)
{
    //INSTRUCTION PACKET COMPOSITION
    //instr_packet = (char*)malloc(9 * sizeof(int));       //allocating vector for the GOALPOSITION instruction


    //HEADERS and ID already present into the INSTRUCTION PACKET

    //INSERTING THE LENGTH OF INSTRUCTION
    instr_packet[3] = 0x05;        //INSTR + P1 + P2 + P3 + CHKSM

    //INSERTING THE INSTRUCTION - WRITE (0x03)
    instr_packet[4] = 0x03;

    //INSERTING P1 - GOAL POSITION ADDRESS in control table = 0x1E
    instr_packet[5] = 0x1E;

    //INSERTING P2 and P3 - 2 bytes value (LSB FIRST) of GOALPOSITION
    instr_packet[6] = (char)position;                  //8 LSBs of the value
    instr_packet[7] = (char)(position >> 8);           //8 MSBs of the value

    //INSERTING CHECKSUM = ~(ID + LENGTH + INSTR + P1 + P2 + P3) ONLY 8 LSBs
    instr_packet[8] = (this)->checksum(instr_packet, 8);

    //READY TO SEND
    sc16is740->write(instr_packet, 9);        //SEND 9 ELEMENTS

    return readStatusPacket(6);       //return 0 if correct , 1 otherwise

}

void DynamixelPolitocean::writebyte(char data)
{
    sc16is740->write(data);
}

void DynamixelPolitocean::writearray(char* data, unsigned int dim)
{
    sc16is740->write(data, dim);
}


bool DynamixelPolitocean::TorqueOn()
{
    //INSERTING THE LENGTH OF INSTRUCTION
    instr_packet[3] = 0x04;        //INSTR + P1 + P2 + CHKSM

    //INSERTING THE INSTRUCTION - WRITE (0x03)
    instr_packet[4] = 0x03;

    //INSERTING P1 - SET TORQUE ADDRESS in control table = 0x18
    instr_packet[5] = 0x18;

    //INSERTING P2 = 1 : torque On
    instr_packet[6] = 1;

    //INSERTING CHECKSUM = ~(ID + LENGTH + INSTR + P1 + P2 ) ONLY 8 LSBs
    instr_packet[7] = (this)->checksum(instr_packet, 7);

    //READY TO SEND
    sc16is740->write(instr_packet, 8);        //SEND 8 ELEMENTS

    return readStatusPacket(6);       //return 0 if correct , 1 otherwise
}

bool DynamixelPolitocean::TorqueOff()
{
    //INSERTING THE LENGTH OF INSTRUCTION
    instr_packet[3] = 0x04;        //INSTR + P1 + P2 + CHKSM

    //INSERTING THE INSTRUCTION - WRITE (0x03)
    instr_packet[4] = 0x03;

    //INSERTING P1 - SET TORQUE ADDRESS in control table = 0x18
    instr_packet[5] = 0x18;

    //INSERTING P2 = 0 : torque Off
    instr_packet[6] = 0;

    //INSERTING CHECKSUM = ~(ID + LENGTH + INSTR + P1 + P2 ) ONLY 8 LSBs
    instr_packet[7] = (this)->checksum(instr_packet, 7);

    //READY TO SEND
    sc16is740->write(instr_packet, 8);        //SEND 8 ELEMENTS

    return readStatusPacket(6);       //return 0 if correct , 1 otherwise
}

bool DynamixelPolitocean::LedOn()
{
    //INSERTING THE LENGTH OF INSTRUCTION
    instr_packet[3] = 0x04;        //INSTR + P1 + P2 + CHKSM

    //INSERTING THE INSTRUCTION - WRITE (0x03)
    instr_packet[4] = 0x03;

    //INSERTING P1 - LED STATUS ADDRESS in control table = 0x19
    instr_packet[5] = 0x19;

    //INSERTING P2 = 1 : led ON
    instr_packet[6] = 1;

    //INSERTING CHECKSUM = ~(ID + LENGTH + INSTR + P1 + P2 ) ONLY 8 LSBs
    instr_packet[7] = (this)->checksum(instr_packet, 7);

    //READY TO SEND
    sc16is740->write(instr_packet, 8);        //SEND 8 ELEMENTS

    return readStatusPacket(6);       //return 0 if correct , 1 otherwise
}


bool DynamixelPolitocean::LedOff()
{
    //INSERTING THE LENGTH OF INSTRUCTION
    instr_packet[3] = 0x04;        //INSTR + P1 + P2 + CHKSM

    //INSERTING THE INSTRUCTION - WRITE (0x03)
    instr_packet[4] = 0x03;

    //INSERTING P1 - LED STATUS ADDRESS in control table = 0x19
    instr_packet[5] = 0x19;

    //INSERTING P2 = 0 : led Off
    instr_packet[6] = 0;

    //INSERTING CHECKSUM = ~(ID + LENGTH + INSTR + P1 + P2 ) ONLY 8 LSBs
    instr_packet[7] = (this)->checksum(instr_packet, 7);

    //READY TO SEND
    sc16is740->write(instr_packet, 8);        //SEND 8 ELEMENTS

    return readStatusPacket(6);       //return 0 if correct , 1 otherwise
}

int DynamixelPolitocean::readTemperature()
{
    //INSERTING THE LENGTH OF INSTRUCTION
    instr_packet[3] = 0x04;        //INSTR + P1 + P2 + CHKSM

    //INSERTING THE INSTRUCTION - READ (0x02)
    instr_packet[4] = 0x02;

    //INSERTING P1 - TEMPERATURE REGISTER in control table = 0x2B
    instr_packet[5] = 0x2B;

    //INSERTING P2 = LENGTH OF DATA = 1
    instr_packet[6] = 1;

    //INSERTING CHECKSUM = ~(ID + LENGTH + INSTR + P1 + P2 ) ONLY 8 LSBs
    instr_packet[7] = (this)->checksum(instr_packet, 7);

    //READY TO SEND
    sc16is740->write(instr_packet, 8);        //SEND 8 ELEMENTS

    if (readStatusPacket(7) == 0)            //return 0 if correct , 1 otherwise
    {
        //read element at index 5
        return (int)(status_packet[5]);
    }
}

int DynamixelPolitocean::readVoltage()
{
    //INSERTING THE LENGTH OF INSTRUCTION
    instr_packet[3] = 0x04;        //INSTR + P1 + P2 + CHKSM

    //INSERTING THE INSTRUCTION - READ (0x02)
    instr_packet[4] = 0x02;

    //INSERTING P1 - VOLTAGE REGISTER in control table = 0x2A
    instr_packet[5] = 0x2A;

    //INSERTING P2 = LENGTH OF DATA = 1
    instr_packet[6] = 1;

    //INSERTING CHECKSUM = ~(ID + LENGTH + INSTR + P1 + P2 ) ONLY 8 LSBs
    instr_packet[7] = (this)->checksum(instr_packet, 7);

    //READY TO SEND
    sc16is740->write(instr_packet, 8);        //SEND 8 ELEMENTS

    if (readStatusPacket(7) == 0)            //return 0 if correct , 1 otherwise
    {
        //read element at index 5
        return (float)(status_packet[5] / 10);      //THE VOLTAGE RETURNED IS AMPLIFIED BY 10
    }
}

bool DynamixelPolitocean::setCCWAngleLimit(int limit)
{
    //INSERTING THE LENGTH OF INSTRUCTION
    instr_packet[3] = 0x05;        //INSTR + P1 + P2 + CHKSM

    //INSERTING THE INSTRUCTION - WRITE (0x03)
    instr_packet[4] = 0x03;

    //INSERTING P1 - CCW ANGLE LIMIT in control table = 0x08
    instr_packet[5] = 0x08;

    //INSERTING P2 = 8 LSB of the LIMIT
    instr_packet[6] = (char)limit;

    //INSERTING P3 = 8 MSB of the LIMIT
    instr_packet[7] = (char)(limit >> 8);

    //INSERTING CHECKSUM = ~(ID + LENGTH + INSTR + P1 + P2 + P3) ONLY 8 LSBs
    instr_packet[8] = (this)->checksum(instr_packet, 8);

    //READY TO SEND
    sc16is740->write(instr_packet, 9);        //SEND 8 ELEMENTS

    return readStatusPacket(6);       //return 0 if correct , 1 otherwise
}

bool DynamixelPolitocean::setCWAngleLimit(int limit)
{
    //INSERTING THE LENGTH OF INSTRUCTION
    instr_packet[3] = 0x05;        //INSTR + P1 + P2 + CHKSM

    //INSERTING THE INSTRUCTION - WRITE (0x03)
    instr_packet[4] = 0x03;

    //INSERTING P1 - CW ANGLE LIMIT in control table = 0x06
    instr_packet[5] = 0x06;

    //INSERTING P2 = 8 LSB of the LIMIT
    instr_packet[6] = (char)limit;

    //INSERTING P3 = 8 MSB of the LIMIT
    instr_packet[7] = (char)(limit >> 8);

    //INSERTING CHECKSUM = ~(ID + LENGTH + INSTR + P1 + P2 + P3) ONLY 8 LSBs
    instr_packet[8] = (this)->checksum(instr_packet, 8);

    //READY TO SEND
    sc16is740->write(instr_packet, 9);        //SEND 8 ELEMENTS

    return readStatusPacket(6);       //return 0 if correct , 1 otherwise
}

bool DynamixelPolitocean::setVelocity(unsigned int velocity)
{

   //HEADERS and ID already present into the INSTRUCTION PACKET

   //INSERTING THE LENGTH OF INSTRUCTION
    instr_packet[3] = 0x05;        //INSTR + P1 + P2 + CHKSM

    //INSERTING THE INSTRUCTION - WRITE (0x03)
    instr_packet[4] = 0x03;

    //INSERTING P1 - VELOCITY ADDRESS in control table = 0x20
    instr_packet[5] = 0x20;

    //INSERTING P2 and P3 - 2 bytes value (LSB FIRST) of VELOCITY
    //VELOCITY REGISTER IS ON 10 BITS ONLY
    instr_packet[6] = (char)velocity;                             //8 LSBs of the value
    instr_packet[7] = (char)((velocity >> 8) & 0x03);           //2 MSBs of the value


    //INSERTING CHECKSUM = ~(ID + LENGTH + INSTR + P1 + P2 + P3) ONLY 8 LSBs
    instr_packet[8] = (this)->checksum(instr_packet, 8);

    //READY TO SEND
    sc16is740->write(instr_packet, 9);        //SEND 9 ELEMENTS

    return readStatusPacket(6);       //return 0 if correct , 1 otherwise

}

bool DynamixelPolitocean::setVelocityWheelMode(unsigned int velocity, unsigned char dir)
{

   //HEADERS and ID already present into the INSTRUCTION PACKET


   //INSERTING THE LENGTH OF INSTRUCTION
    instr_packet[3] = 0x05;        //INSTR + P1 + P2 + CHKSM

    //INSERTING THE INSTRUCTION - WRITE (0x03)
    instr_packet[4] = 0x03;

    //INSERTING P1 - VELOCITY ADDRESS in control table = 0x20 = 32
    instr_packet[5] = 0x20;

    //INSERTING P2 and P3 - 2 bytes value (LSB FIRST) of VELOCITY
    //VELOCITY REGISTER IS ON 11 BITS ONLY

     //COMPOSING THE VELOCITY BY ATTACHING DIRECTION BIT AND VELOCITY   
    velocity = velocity | ((dir & 0x01) << 10);
    instr_packet[6] = (char)velocity;                            
    instr_packet[7] = (char)((velocity >> 8) & 0x07);           //3 MSBs of the value
    
    //INSERTING CHECKSUM = ~(ID + LENGTH + INSTR + P1 + P2 + P3) ONLY 8 LSBs
    instr_packet[8] = (this)->checksum(instr_packet, 8);

    //READY TO SEND
    sc16is740->write(instr_packet, 9);        //SEND 9 ELEMENTS

    return readStatusPacket(6);       //return 0 if correct , 1 otherwise
}

bool DynamixelPolitocean::setOperatingMode(unsigned char mode)
{
    char flag = false;
    switch (mode)
    {
    case 0: 
        //wheel mode
        setCWAngleLimit(0);
        setCCWAngleLimit(0);
        flag = true;
        break;
    case 1:
        //multi turn mode
        setCWAngleLimit(4095);
        setCCWAngleLimit(4095);
        flag = true;
        break;
    
    case 2:
        //joint mode
        setCWAngleLimit(1);
        setCCWAngleLimit(4095);
        flag = true;
        break;
    }
    return flag;
}

int DynamixelPolitocean::getPosition()
{
    //ONLY IN MULTI TURN MODE



   
    //INSERTING THE LENGTH OF INSTRUCTION
    instr_packet[3] = 0x04;        //INSTR + P1 + P2 + CHKSM

    //INSERTING THE INSTRUCTION - READ (0x02)
    instr_packet[4] = 0x02;

    //INSERTING P1 - POSITION REGISTER in control table = 0x24
    instr_packet[5] = 0x24;

    //INSERTING P2 = LENGTH OF DATA = 2 : 12 BITS VALUE
    instr_packet[6] = 0x02;

    //INSERTING CHECKSUM = ~(ID + LENGTH + INSTR + P1 + P2 ) ONLY 8 LSBs
    instr_packet[7] = (this)->checksum(instr_packet, 7);

    //READY TO SEND
    sc16is740->write(instr_packet, 8);        //SEND 8 ELEMENTS

    if (readStatusPacket(8) == 0)            //return 0 if correct , 1 otherwise
    {
        //read element at index 5
        return (int)((status_packet[6] << 8) + status_packet[5]);
    }
}

int DynamixelPolitocean::getSpeed()
{
    //INSERTING THE LENGTH OF INSTRUCTION
    instr_packet[3] = 0x04;        //INSTR + P1 + P2 + CHKSM

    //INSERTING THE INSTRUCTION - READ (0x02)
    instr_packet[4] = 0x02;

    //INSERTING P1 - VELOCITY REGISTER in control table = 0x26
    instr_packet[5] = 0x26;

    //INSERTING P2 = LENGTH OF DATA = 2 : 11 BITS VALUE
    instr_packet[6] = 0x02;

    //INSERTING CHECKSUM = ~(ID + LENGTH + INSTR + P1 + P2 ) ONLY 8 LSBs
    instr_packet[7] = (this)->checksum(instr_packet, 7);

    //READY TO SEND
    sc16is740->write(instr_packet, 8);        //SEND 8 ELEMENTS

    if (readStatusPacket(8) == 0)            //return 0 if correct , 1 otherwise
    {
        //read element at index 5

        return (int)(((status_packet[6] & 0x07) << 8) + status_packet[5]);     //EXTRACION OF 11 BITS FROM 2 BYTES
    }

}


char DynamixelPolitocean::getDirection()
{
    return ((getSpeed() & 0x400) >> 10);

}

float DynamixelPolitocean::getCurrent()
{

    float current = 0;
     //INSERTING THE LENGTH OF INSTRUCTION
    instr_packet[3] = 0x04;        //INSTR + P1 + P2 + CHKSM

    //INSERTING THE INSTRUCTION - READ (0x02)
    instr_packet[4] = 0x02;

    //INSERTING P1 - CURRENT REGISTER in control table = 0x44 = 68
    instr_packet[5] = 0x44;

    //INSERTING P2 = LENGTH OF DATA = 2 : 12 BITS VALUE
    instr_packet[6] = 0x02;

    //INSERTING CHECKSUM = ~(ID + LENGTH + INSTR + P1 + P2 ) ONLY 8 LSBs
    instr_packet[7] = (this)->checksum(instr_packet, 7);

    //READY TO SEND
    sc16is740->write(instr_packet, 8);        //SEND 8 ELEMENTS

    if (readStatusPacket(8) == 0)            //return 0 if correct , 1 otherwise
    {
        //read element at index 5
        current = ((float)((status_packet[6] & 0x0F) << 8) + (float)(status_packet[5]));     //EXTRACION OF 12 BITS FROM 2 BYTES
        current = (0.0045 * (current - 2048));                                    //mapping function of the current
        return current;                                                         //current in AMPERE
    }

}
