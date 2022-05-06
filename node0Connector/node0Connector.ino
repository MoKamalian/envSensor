/*
 * author: amir kamalian, sarah newman, carlington palmer 
 * date:   05-May-2022
 * description: This program is meant for the master node that will connect multiple Arduino 
 * MKR ENV 1300 series with a MKR ENV environmental shield attached.  The master node will 
 * listen for incoming packets via LoRa and parse them.  The end nodes must be configured in 
 * such a way as to offset the timing of the packets being sent in order to prevent packet 
 * collisions; if the timings are not offset the master node will not pick up the sent packets or 
 * the recieved packets will become corrupted. 
 * 
 * The master node will forward recieved packets to a raspberry pi via serial communication.  Note 
 * that packets are not parsed here.
 * 
 * source: https://forum.arduino.cc/t/lora-multiple-transmitter-to-single-receiver/663645/12
 * 
 * Note: supposed there are two nodes being connected to the master node, delay one node to 
 * 2 seconds and the other for 4 seconds.  The greater the difference in delay times the less of 
 * a chance the packets will collide.
 * 
 * 
 */

#include <SPI.h>
#include <LoRa.h>


void setup() {
  Serial.begin(9600);
  while(!Serial);

  Serial.println("LoRa Reciever");

  /* initializing LoRa communication */
  if(!LoRa.begin(915E6)) {
    Serial.println("failed to initialize LoRa communication");
    while(1);
  }

}


void loop() {
  /* packets recived and forwarded */
  int packet = LoRa.parsePacket();
  /* if there is a packet available read it */ 
  if(packet) {
    String temp;
    while(LoRa.available()) {
      temp += (char) LoRa.read();
    }
    Serial.println(temp);

    /* forward the packet via serial communication to raspberry pi */
    
    
  }



  
  
   
}
