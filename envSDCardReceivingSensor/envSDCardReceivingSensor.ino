/*
 * author: sarah newman, amir kamalian, carlington palmer
 * date:   03-May-2022
 * description: This is the base program used for node 0; the node 0 will 
 * receive the environmental data from other sensor nodes, log it onto an 
 * micro SD card as pseudo-cache before being sent off to final node via LoRa 
 * protocol.  Use Sd.begin() with no parameters if using the default serial 
 * connection to the SD card.  Node 0 also collects sensor data. 
 * 
 * Note: you can parse the packets here but the nodes are simply meant for data 
 * transmission to the master node. 
 */

#include <Arduino_MKRENV.h>
#include <SPI.h>
#include <SD.h>
#include <LoRa.h>


using namespace std;


File myFile;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial);
 
  Serial.println("LoRa Receiver: ");
  /* initialize the LoRa connection */
  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  /* initialize the env sensor shield */
  delay(2000);
  if (!ENV.begin()) {
    Serial.println("Failed to initialize MKR ENV shield!");
    while (1);
  }

  /* SD card initialization */
  if (!SD.begin()) {
    Serial.println("initialization failed");
    while (1);
  }
 
  /* opening the file */
  Serial.println("initialization done!");
  myFile = SD.open("test.txt", FILE_WRITE);
  if (myFile) {
    Serial.println("file was opened");
  }


}


void loop() {
  // put your main code here, to run repeatedly:

  // read all the sensor values
  float temperature = ENV.readTemperature();
  float humidity = ENV.readHumidity();
  float pressure = ENV.readPressure();
  float illuminance = ENV.readIlluminance();
  float uva = ENV.readUVA();
  float uvb = ENV.readUVB();
  float uvIndex = ENV.readUVIndex();


  // print each of the sensor values

  /*
    Serial.print("Temperature = ");
    Serial.print(temperature);
    Serial.println(" °C");


    Serial.print("Humidity    = ");
    Serial.print(humidity);
    Serial.println(" %");


    Serial.print("Pressure    = ");
    Serial.print(pressure);
    Serial.println(" kPa");


    Serial.print("Illuminance = ");
    Serial.print(illuminance);
    Serial.println(" lx");


    Serial.print("UVA         = ");
    Serial.println(uva);


    Serial.print("UVB         = ");
    Serial.println(uvb);


    Serial.print("UV Index    = ");
    Serial.println(uvIndex);
    Serial.print("Sending packet: ");
    Serial.println(counter);
  */

  // send packet
    LoRa.beginPacket();
    LoRa.print("sensor1,");
    LoRa.print("temperature:");
    LoRa.print(temperature);
    LoRa.print(",");


    LoRa.print("Humidity:");
    LoRa.print(humidity);
    LoRa.print(",");

    LoRa.print("pressure:");
    LoRa.print(pressure);
    LoRa.print(",");

    LoRa.print("illuminance:");
    LoRa.print(illuminance);
    LoRa.print(",");

    LoRa.print("uva:");
    LoRa.print(uva);
    LoRa.print(",");

    LoRa.print("uvb:");
    LoRa.print(uvb);
    LoRa.print(",");

    LoRa.print("uv_index:");
    LoRa.print(uvIndex);
    LoRa.print(",");

    LoRa.endPacket();
  
  // check to see if packets are getting through
  int packet = LoRa.parsePacket();
  if(packet) {
    
    Serial.println("packet was recived");
    String temp;
    while(LoRa.available()) {
      temp += (char) LoRa.read();
    }
    Serial.println(temp);
    
  }
  

  /* file reading and writing; checks to see if file is opened and if so, writes to it */
  myFile = SD.open("cache.txt", FILE_WRITE);
  if (myFile) {
    myFile.print(temp);
  } else {
    Serial.println("could not write to the file");
  }
  myFile.close();


}
