#define dirPin 2               // Direction PIN - VERDE
#define stepPin 7              // Step PIN - BIANCO
#define stepsPerRevolution 400 // Number of Steps for a Total Round
#define totalRound 130         // Number of Rounds to drain
#define forwardPin 4           // Status of the command
#define backwardPin 5
#define Enable 6           // BLU
int presentTotalRound = 0; // Variable itcn which is stored the actual number of round
bool suca = false;
bool sputa = false;
bool moveON = false;

void setup()
{
  // Declare pins as output:
  Serial.begin(9600);
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(forwardPin, INPUT);
  pinMode(backwardPin, INPUT);
}
void loop()
{
  sputa = digitalRead(forwardPin);
  suca = digitalRead(backwardPin);
  if (suca)
  {
    if (digitalRead(Enable) == HIGH)
      digitalWrite(Enable, LOW);
    Serial.println("suca on");
    moveON = true;
    presentTotalRound++;
    digitalWrite(dirPin, LOW);
  }
  else if (sputa)
  {
    if (digitalRead(Enable) == HIGH)
      digitalWrite(Enable, LOW);
    Serial.println("sputa on");
    digitalWrite(dirPin, HIGH);
    moveON = true;
    presentTotalRound--;
  }
  else
  {

    moveON = false;
    digitalWrite(Enable, HIGH);
  }
  if (moveON)
  {
    if (presentTotalRound <= totalRound && presentTotalRound >= 0)
    {
      Serial.println(presentTotalRound);
      for (int i = 0; i < 400; i++)
      {
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(400);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(400);
      }
    }
  }
}
