#define dirPin 6
#define pulPin 7
#define hallSensor 5
#define relaySig 9


int hallSensorReading =0;
int dir = 0;
int speed = 200;
int turn=LOW;

void setup() {

  Serial.begin(9600);
  // Declare pins as output:
  pinMode(pulPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(relaySig, OUTPUT);
  pinMode(hallSensor, INPUT);
  digitalWrite(dirPin, dir);

  turn=HIGH; // Initially turn irrespective of location

}

void loop() {

  
 if(turn){
  runMotor(dir, speed);
 }

// Disk has reached correct position. Filling starts
 digitalWrite(relaySig,HIGH); // Pump ON
 delay(1000); // Run pump for 1000ms
 digitalWrite(relaySig,LOW); // Pump OFF
 delay(1000);
 
 turn = HIGH; // Start Turning
 hallSensorReading = 0;

}

void runMotor(int dir, int speed){
  
    for (int i=0; i<6400; i++)    //Forward 5000 steps
  {
    // Check for position
    hallSensorReading = digitalRead(hallSensor);
    if(hallSensorReading == 1 && !turn && i>3200) break; // Stop if correct position
    
    digitalWrite(dirPin,LOW);
    digitalWrite(pulPin,HIGH);
    delayMicroseconds(speed);
    digitalWrite(pulPin,LOW);
    delayMicroseconds(speed);
    
    if(hallSensorReading == 0) turn = LOW;
  }

}

