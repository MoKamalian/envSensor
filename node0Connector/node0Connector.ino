/*
 * author: amir kamalian
 * date:   05-May-2022
 * description: 
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
  if(packet) {
    String temp;
    while(LoRa.available()) {
      temp += (char) LoRa.read();
    }
    Serial.println(temp);
  }
  
   
}
