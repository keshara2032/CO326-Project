#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <WebSocketClient.h>

SoftwareSerial mySerial (D1, D2);               //Virtual Rx and Tx pins of the nodeMCU

const char * ssid = "SLT_FIBRE";
const char * password = "2240845@123";
char path[] = "/nodeMCU";
char host[] = "ws://192.168.1.7";
  
WebSocketClient webSocketClient;

//Use WiFiClient class to create TCP connections
WiFiClient client;


void setup(){
  Serial.begin(9600);
  mySerial.begin(9600);
  
  delay(10);

  //We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  delay(5000);

  //Connect to the websocket server
  if(client.connect("192.168.1.7", 3000)){
    Serial.println("Connected to web socket server");
  }else{
    Serial.println("Connection with web socket server failed.");
    while(1){
      //Hang on failure
    }
  }

  //Handshake with the server
  webSocketClient.path = path;
  webSocketClient.host = host;
  
  if(webSocketClient.handshake(client)){
    Serial.println("Handshake successful");
  }else{
    Serial.println("Handshake failed.");
    while(1){
      //Hang on failure
    }  
  }
}


void loop(){
  String incomingData;
  String outgoingData;
  String serialData;

  if(client.connected()){  
    webSocketClient.getData(incomingData);
    incomingData.trim();
  
    if(incomingData.length() > 0){
      Serial.print("Received from server: ");
      Serial.println(incomingData);

      mySerial.println(incomingData);
      Serial.println("Payload sent to arduino!");
    }
  }
  
  if(mySerial.available() > 0){
    serialData = mySerial.readStringUntil('\r');
    serialData.trim();

    if(serialData.length() > 0){
      Serial.print("Received from arduino: ");
      Serial.println(serialData);
  
      if(client.connected()){  
        outgoingData = serialData;
        
        webSocketClient.sendData(outgoingData);
        Serial.println("Payload sent to server!");
        
      }else{
        Serial.println("Client disconnected.");
        while (1){
          //Hang on disconnect.
        }
      }    
    }   
  }
}








