/*Example sketch to control a stepper motor with A4988/DRV8825 stepper motor driver and Arduino without a library. More info: https://www.makerguides.com */
/*Define stepper motor connections and steps per revolution:*/

#define dirPin 2                  // Direction PIN
#define stepPin 3                 // Step PIN
#define stepsPerRevolution 400    // Number of Steps for a Total Round 
#define totalRound 227            // Number of Rounds to drain 
#define forwardPin 4               // Status of the command
#define backwardPin 5
#define Enable 6
int presentTotalRound = 0;        // Variable in which is stored the actual number of round
bool suca = false;
bool sputa = false;
bool moveON = false;

void setup() {
  // Declare pins as output:
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(forwardPin, INPUT);
  pinMode(backwardPin, INPUT);
}
void loop() {
  sputa = digitalRead(forwardPin);                                     
  suca = digitalRead(backwardPin);
  if (suca && !sputa) {                                                        
    digitalWrite(dirPin, LOW);
    digitalWrite(Enable, LOW);
    moveON = true;
    }
  else if (sputa && !suca){
    digitalWrite(dirPin, HIGH);
    digitalWrite(Enable, LOW);
    moveON = true;
    }
  else if ((sputa && suca) || (!sputa && !suca)){
    digitalWrite(Enable, HIGH);     // Stepper has !Enable
    moveON = false;   
    }                                        
  if (presentTotalRound < totalRound * stepsPerRevolution 
      && presentTotalRound > 0 
      && moveON) {        
    
    // These four lines result in 1 step with the minimum possible of delay:
    
    digitalWrite(stepPin, HIGH);                                    
    delayMicroseconds(400);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(400);
    if (suca){
      presentTotalRound += 1;
      }
    else{
      presentTotalRound -= 1;
      }
    
    }  
 
  }
