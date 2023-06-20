#define STATUS_LED 2        //PORT C

#define RES 250000    // Width of the low gap between bits to cause a frame to latch

#define NS_PER_SEC (1000000000L)          // Note that this has to be SIGNED since we want to be able to check for negative values of derivatives

#define CYCLES_PER_SEC (F_CPU)

#define NS_PER_CYCLE ( NS_PER_SEC / CYCLES_PER_SEC )

#define NS_TO_CYCLES(n) ( (n) / NS_PER_CYCLE )

enum color{RED, GREEN, BLUE, YELLOW, ORANGE, CIANO, MAGENTA, GRAY, WHITE};

void sendBit(bool bitVal);
void sendByte(char _byte);
void setLED(char red, char green, char blue);
void setLED(color color);


void setLED(color color)
{
    switch (color)
    {
        case RED : setLED(255,0,0);
        break;
        case GREEN : setLED(0,255,0);
        break;
        case BLUE : setLED(0,0,255);
        break;
        case YELLOW : setLED(255,255,0);
        break;
        case ORANGE : setLED(255,69,0);
        break;
        case CIANO : setLED(0,255,255);
        break;
        case MAGENTA : setLED(255,0,255);
        break;
        case GRAY : setLED(128,128,128);
        break;
        case WHITE : setLED(255,255,255);
        break;
    }
}
void setLED(char red, char green, char blue)
{
    sendByte(green);          // Neopixel wants colors in green then red then blue order
    sendByte(red);
    sendByte(blue);
}
void sendByte(char _byte) {

    for (char i = 0;i < 8;i++) {

        sendBit(_byte && 0x80);                // Neopixel wants bit in highest-to-lowest order
        // so send highest bit (bit #7 in an 8-bit byte since they start at 0)
        _byte <<= 1;                                    // and then shift left so bit 6 moves into 7, 5 moves into 6, etc
    }
}
void sendBit(bool bitVal) {

    if (bitVal) {        // 0 bit

        asm volatile (
            "sbi %[port], %[bit] \n\t"        // Set the output bit
            ".rept %[onCycles] \n\t"                                // Execute NOPs to delay exactly the specified number of cycles
            "nop \n\t"
            ".endr \n\t"
            "cbi %[port], %[bit] \n\t"                              // Clear the output bit
            ".rept %[offCycles] \n\t"                               // Execute NOPs to delay exactly the specified number of cycles
            "nop \n\t"
            ".endr \n\t"
            ::
            [port]    "I" (_SFR_IO_ADDR(PORTC)),
            [bit]   "I" (STATUS_LED),
            [onCycles]  "I" (NS_TO_CYCLES(900) - 2),    // 1-bit width less overhead  for the actual bit setting, note that this delay could be longer and everything would still work
            [offCycles]   "I" (NS_TO_CYCLES(600) - 2)     // Minimum interbit delay. Note that we probably don't need this at all since the loop overhead will be enough, but here for correctness

            );

    }
    else {          // 1 bit

        asm volatile (
            "sbi %[port], %[bit] \n\t"        // Set the output bit
            ".rept %[onCycles] \n\t"        // Now timing actually matters. The 0-bit must be long enough to be detected but not too long or it will be a 1-bit
            "nop \n\t"                                              // Execute NOPs to delay exactly the specified number of cycles
            ".endr \n\t"
            "cbi %[port], %[bit] \n\t"                              // Clear the output bit
            ".rept %[offCycles] \n\t"                               // Execute NOPs to delay exactly the specified number of cycles
            "nop \n\t"
            ".endr \n\t"
            ::
            [port]    "I" (_SFR_IO_ADDR(PORTC)),
            [bit]   "I" (STATUS_LED),
            [onCycles]  "I" (NS_TO_CYCLES(400) - 2),
            [offCycles] "I" (NS_TO_CYCLES(900) - 2)

            );
    }
}