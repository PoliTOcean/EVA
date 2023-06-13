#define dirPin 2               // Direction PIN
#define stepPin 3              // Step PIN
#define stepsPerRevolution 400 // Number of Steps for a Total Round
#define totalRound 227         // Number of Rounds to drain
#define forwardPin 4           // Status of the command
#define backwardPin 5
#define Enable 6
int presentTotalRound = 0; // Variable in which is stored the actual number of round
bool suca = false;
bool sputa = false;
bool moveON = false;
bool fineCorsaSuca = false;
bool fineCorsaSputa = false;

void setup() {
    // Declare pins as output:
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(forwardPin, INPUT);
  pinMode(backwardPin, INPUT);
}

void loop() {
  suca = digitalRead(backwardPin);
  digitalWrite(dirPin, HIGH);
    digitalWrite(Enable, LOW);
  if(suca){
   for (int i = 0; i <= stepsPerRevolution; i++)
    {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(400);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(400);
    }
  }
}
