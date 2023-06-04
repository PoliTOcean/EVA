#define dirPin 2               // Direction PIN
#define stepPin 3              // Step PIN
#define stepsPerRevolution 400 // Number of Steps for a Total Round
#define totalRounds 228        // Number of Rounds to drain
#define forwardPin 4           // Command status - The stepper goes counterclockwise
#define backwardPin 5          // Command status - The stepper goes clockwise
#define Enable 6               // Enable PIN (!! ENABLE = 1 ENABLES THE TORQUE !!)
int presentTotalRound = 0;     // Variable in which is stored the actual number of round
bool suca = false;             // It is true if the syringe drain the liquid
bool sputa = false;            // It is true if the syringe drop out the liquid
bool moveON = false;           // It is true on the IDLE state
bool FineCorsa = false;        // It is true if presentTotalRound is 0 either 277

void setup()
{
    // Declare pins as output:
    pinMode(stepPin, OUTPUT);
    pinMode(dirPin, OUTPUT);
    pinMode(forwardPin, INPUT);
    pinMode(backwardPin, INPUT);
    Serial.begin(9600);
}

void loop()
{
    sputa = digitalRead(forwardPin);
    suca = digitalRead(backwardPin);

// 4 status combination of the syringe
    if (suca && !sputa)
    // If suca mode
    {
        digitalWrite(dirPin, LOW);
        digitalWrite(Enable, LOW);
        moveON = true;
        // assuming FineCorsa after sputa mode and checking if it is in suca mode limit
        if (FineCorsa && presentTotalRound < totalRounds)
        {
            FineCorsa = false;
        }
    }
    else if (!suca && sputa)
    // If sputa mode
    {
        digitalWrite(dirPin, HIGH);
        digitalWrite(Enable, LOW);
        moveON = true;
        // assuming FineCorsa after suca mode and checking if it is in sputa mode limit
        if (FineCorsa && presentTotalRound > 0)
        {
            FineCorsa = false;
        }
    }
    else if ((sputa && suca) || (!sputa && !suca))
    // transition state between suca mode and sputa mode (IDLE)
    {
        digitalWrite(Enable, HIGH); // Stepper has !Enable
        moveON = false;
    }

    // Conditions to enable the stepper to move
    if (presentTotalRound <= totalRounds && presentTotalRound >= 0 && moveON && !FineCorsa)
    {
        for (int i = 0; i <= stepsPerRevolution; i++)
        {
            digitalWrite(stepPin, HIGH);
            delayMicroseconds(400);
            digitalWrite(stepPin, LOW);
            delayMicroseconds(400);
        }
        if (suca)
        {
            presentTotalRound++;
        } else if (sputa){
            presentTotalRound--;
        }
        if (presentTotalRound == 0 || presentTotalRound == totalRounds)
        {
            FineCorsa = true;
        }
    }
}