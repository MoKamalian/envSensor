/*
 * author: sarah newman, amir kamalian, carlington palmer
 * date:   05-May-2022
 * description: this is a basic program to recieve data from another Arduino MKR 1300 
 * series with an Dipole Antenna for Arduino attached.  This program uses the 915E6 
 * frequency and should be changed depending on the location you are in.  No processing 
 * of the packets is done in this program. 
 */
#include <SPI.h>
#include <LoRa.h>


void setup() {

  /* initialize serial communication */
  Serial.begin(9600); 
  while(!Serial);

 
  Serial.println("LoRa Receiver");
  
  /* initialize LoRa communication */
  if(!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);  
  }

}


void loop() {

// try to parse packet

  int packetSize = LoRa.parsePacket();

  if(packetSize) {
  /* received a packet
   * Serial.print("Received packet ");
   * read packet */
    String temp;
    while(LoRa.available()) {
      temp += (char) LoRa.read();
    }
    /* print out the parsed packet recieved */
    Serial.println(temp);
  }

}
