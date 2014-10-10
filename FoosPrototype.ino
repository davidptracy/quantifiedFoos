// Dependency of ID20Reader. Must include in main file due to Arduino software limitations.
#include <SoftwareSerial.h>                           
#include <ID20Reader.h>

#include <Bridge.h>
#include <Process.h>

//create a process for calling WS
Process ws;

char sensorStr[512];

int rx_pin = 8; //Data input pin
int tx_pin = 1; //Unused, but must be defined. (Nothing is sent from the Arduino to the reader.)

ID20Reader rfid(rx_pin, tx_pin); //Create an instance of ID20Reader.

void setup() {
  
  // initialize bridge and serial
  Bridge.begin();
  Serial.begin(9600);
  
  //wait for the serial monitor to open doing anything
  while (!Serial);
  
  ws.runShellCommandAsynchronously("node /mnt/sda1/arduino/node/wsFoosClient.js");
  Serial.println("========== PROCESS INITIATED ==========");
  Serial.println("====== RFID Reader - Swipe a card =====");
  
}

void loop() {
  
  rfid.read(); //Receive a tag from the reader if available
  //a tag has been read
  
  if(rfid.available()){
    String code = rfid.get(); //Get the tag
    code.toCharArray(sensorStr, 512); 
    for( int i = 0; i < code.length(); ++i ) {
      ws.write(code.charAt(i));
    }  
    ws.write('\n');
//    Serial.println(code); //Print the tag to the serial monitor  
//    for(int i = 0; i < sensorStr.length(); i++){
//      char c = charAt(i);
//    }
  }
  
  
  
    
  // pass any bytes that come in from the serial port
  // to the running node process:
  if (Serial.available()) {
    if (ws.running()) {
      ws.write(Serial.read());
    }
  }
   
  // pass any incoming bytes from the running node process
  // to the serial port:
  while (ws.available()) {
    Serial.write(ws.read());
  }
 
}
