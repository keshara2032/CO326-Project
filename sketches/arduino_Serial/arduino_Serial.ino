#include <SoftwareSerial.h>

SoftwareSerial mySerial (2, 3);             //Virtual Rx and Tx pins of the arduino

int interval = 2000;
unsigned long current_time = 0;

int count = 0;

 
void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
}


void loop() {
  String serialData;
  
  if(mySerial.available() > 0){
    serialData = mySerial.readStringUntil('\r');
    serialData.trim();

    if(serialData.length() > 0){
      Serial.print("Received from nodeMCU: ");
      Serial.println(serialData);
    }
  }

  current_time = millis();
  
  String str = "Payload ";
  String data = str + count;
     
  mySerial.println(data);
  Serial.println("'" + data + "'" + " sent to nodeMCU!");
    
  count++;

  while(millis() < current_time + interval);
}





