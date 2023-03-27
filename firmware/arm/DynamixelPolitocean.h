#include <stdlib.h>
#include <Arduino.h>
#include <Wire.h>


enum OperatingMode {
    WHEEL = 0,
    MULTITURN = 1,
    JOINT = 2,
};

enum Direction {
    CCW = 0,
    CW = 1,
};


class SC16IS740
{
public:

    SC16IS740(TwoWire& I2C_port, const int I2C_add, unsigned long freq = 16000000);
    void begin();
    void begin(unsigned long baud);
    void end();
    bool available(void);
    char read();
    void write(char buf);
    void write(char* buf, unsigned int len);
    void flush();
    void setAddress(char addr);
    void setFreq(unsigned long freq = 16000000);         //set QUARTZ frequency of the ic 
    void enableRS485mode();                              //enable RS485 mode, NOT THE PHYSICAL LAYER, only addressing modes and multidrop mode
    void enableDirectionControl();
    void enableInvDirectionControl();                    //for the max485 DE and ~RO          


    void writeRegister(char registerAddress, char data);
    char readRegister(char registerAddress);
    char _deviceAddress;
    unsigned long baud_;
    unsigned long QUARTZ_freq;
    TwoWire& port;
private:

};



class DynamixelPolitocean
{
public:

    //NEED TO DEBUG
    //TORQUEON
    DynamixelPolitocean(TwoWire& I2C_port, const int I2C_add, unsigned char DXL_ID = 1, unsigned long freq = 16000000);
    ~DynamixelPolitocean();

    void writebyte(char data);
    void writearray(char* buf, unsigned int dim);
    void begin(unsigned long baud = 57600);
    bool setGoalPosition(int position);
    bool TorqueOn();
    bool TorqueOff();
    bool LedOn();
    bool LedOff();
    int readTemperature();
    int readVoltage();
    bool setCCWAngleLimit(int limit);
    bool setCWAngleLimit(int limit);
    bool setVelocity(unsigned int velocity);
    bool setVelocityWheelMode(unsigned int velocity, unsigned char dir);
    bool setOperatingMode(unsigned char mode);
    int getPosition();
    int getSpeed();
    float getCurrent();

private:


    unsigned char id;        //id of the Dynamixel Motor
    bool readStatusPacket(unsigned char exp_bytes);
    char checksum(char* instrpacket, char dim);
    char getDirection();
    char instr_packet[10];            //TO SEND
    char status_packet[10];        //TO RECEIVE
    SC16IS740* sc16is740;
};


class DynamixelPolitocean
{
public:
    
    //NEED TO DEBUG
    //TORQUEON
    //CW ANGLE LIMIT
    //CCW ANGLE LIMIT
    DynamixelPolitocean(TwoWire& I2C_port, const int I2C_add, unsigned int DXL_ID = 1, unsigned long freq = 16000000);
    ~DynamixelPolitocean();

    void writebyte(char data);
    void writearray(char* buf, unsigned int dim);
    void begin(unsigned long baud = 57600);
    char checksum(char* instrpacket, char dim);
    bool setGoalPosition(int position);
    bool TorqueOn();
    bool TorqueOff();
    bool LedOn();
    bool LedOff();
    int readTemperature();
    int readVoltage();
    bool setCCWAngleLimit(int limit);
    bool setCWAngleLimit(int limit);
    bool setVelocity(int velocity);
    
    
private:
    
    
    unsigned int id;        //id of the Dynamixel Motor
    bool readStatusPacket(unsigned int exp_bytes);
    char instr_packet[10];            //TO SEND
    char status_packet[10];        //TO RECEIVE
    SC16IS740* sc16is740;
};
