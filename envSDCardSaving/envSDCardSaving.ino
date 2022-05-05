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

  Serial.println("LoRa Sender");

  /* initialize the LoRa connection */
  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);

  }

  /* initialize the env sensor shield */
  delay(2000);
  if(!ENV.begin()) {
    Serial.println("Failed to initialize MKR ENV shield!");
    while(1);
  }

  /* SD card initialization */
  if(!SD.begin()) {
    Serial.println("initialization failed");
    while(1);
  }
  /* opening the file */
  Serial.println("initialization done!");
  myFile = SD.open("test.txt", FILE_WRITE);
  
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
  //LoRa.print("Temperature: " );
  LoRa.print(temperature);
  LoRa.print(",");
  

  //LoRa.print("Humidity: ");
  LoRa.print(humidity);
  LoRa.print(",");
  
  //LoRa.print("Pressure: ");
  LoRa.print(pressure);
  LoRa.print(",");

  //LoRa.print("Illuminance: ");
  LoRa.print(illuminance);
  LoRa.print(",");

  //LoRa.print("UVA: ");
  LoRa.print(uva);
  LoRa.print(",");

  //LoRa.print("UVB: ");
  LoRa.print(uvb);
  LoRa.print(",");

  //UVIndex
  LoRa.print(uvIndex);
  LoRa.print(",");
  
  LoRa.endPacket();
  delay(1000);


  /* file reading and writing; checks to see if file is opened and if so, writes to it */
  myFile = SD.open("cache.txt", FILE_WRITE);  
  if(myFile) {
    myFile.print("temperature:");
    myFile.print(temperature);
    myFile.print(",");

    myFile.print("humidity:");
    myFile.print(humidity);
    myFile.print(",");

    myFile.print("pressure:");
    myFile.print(pressure);
    myFile.print(",");

    myFile.print("illuminance:");
    myFile.print(illuminance);

    myFile.print("uva:");
    myFile.print(uva);

    myFile.print("uvb:");
    myFile.print(uvb);

    myFile.print("uv_index:");
    myFile.print(uvIndex);

    myFile.print("\n");
    
  } else {
    Serial.println("could not write to the file");
  }
  myFile.close();
  


}
