#define dirPin 6
#define pulPin 7
#define hallSensor A7

int hallSensorReading = 1;
int dir = 0;
int speed = 250;

void setup() {

  Serial.begin(9600);
  // Declare pins as output:
  pinMode(pulPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(hallSensor, INPUT);
  digitalWrite(dirPin, dir);

  // Set the spinning direction CW/CCW:
}
void loop() {
  // These four lines result in 1 step:
  hallSensorReading = analogRead(hallSensor);

  Serial.println(hallSensorReading);

 if(hallSensorReading < 500){
  runMotor(dir, speed);
 }
}

void runMotor(int dir, int speed){
  
    for (int i=0; i<6400; i++)    //Forward 5000 steps
  {
    hallSensorReading = analogRead(hallSensor);
    if(hallSensorReading > 500) break;
    digitalWrite(dirPin,LOW);
    digitalWrite(pulPin,HIGH);
    delayMicroseconds(speed);
    digitalWrite(pulPin,LOW);
    delayMicroseconds(speed);
  }
//  for (int i=0; i<6400; i++)   //Backward 5000 steps
//  {
//  digitalWrite(dirPin,HIGH);
//    digitalWrite(pulPin,HIGH);
//    delayMicroseconds(speed);
//    digitalWrite(pulPin,LOW);
//    delayMicroseconds(speed);
//  }
}

