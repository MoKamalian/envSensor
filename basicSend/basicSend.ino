/* 
 *  author(s): sarah newman, amir kamalian, carlington palmer
 *  date:      29-Apr-2022
 *  description: This is the base file used for the Arduino MKR ENV 1300 series with 
 *  the MKR ENV environmental shield AND Dipole Antenna for Arduino.  This program will 
 *  send packets containing environmental data.  Note the frequency being used; check to 
 *  ensure the correct frequency is set, for North America that is 915E6. 
 */
#include <Arduino_MKRENV.h>
#include <LoRa.h>


using namespace std;

String sensorName = "sensor1,";

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
  
  Serial.print("Sending packet: "); Serial.println(sensorName);

  // send packet
  LoRa.beginPacket();

  LoRa.print(sensorName);
  
  LoRa.print("temperature:");
  LoRa.print(temperature);
  LoRa.print(",");
  
  LoRa.print("humidity:");
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
  delay(4000);
}
