#include <SPI.h>
#include <LoRa.h>


void setup() {

  /* initialize serial communication */
  Serial.begin(9600); 
  while (!Serial);

 
  Serial.println("LoRa Receiver");
  
  /* initialize LoRa communication */
  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);  
  }

}


void loop() {

// try to parse packet

int packetSize = LoRa.parsePacket();

if (packetSize) {
  
  // received a packet
  
  //Serial.print("Received packet ");
  
  
  // read packet
  
  String temp;
  
  while (LoRa.available()) {
  
  temp += (char) LoRa.read();
  
  }
  
  
  Serial.println(temp);


// print RSSI of packet

// Serial.print("' with RSSI ");

// Serial.println(LoRa.packetRssi());

}

}
