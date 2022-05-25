
Skip to content
Pulls
Issues
Marketplace
Explore
@MoKamalian
MoKamalian /
envSensor
Public

Code
Issues
Pull requests
Actions
Projects
Wiki
Security
Insights

More
envSensor/README.md
@MoKamalian
MoKamalian Update README.md
Latest commit 972c245 6 minutes ago
History
1 contributor
58 lines (43 sloc) 2.43 KB
# Environmental Sensors

## Purpose: 

The purpose of this project was to establish sensor nodes that would collect environmental data such as tempurature, pressure, humidity etc.  The data is then send to a cloud service via a Raspberry Pi.  The environmental data is then displayed onto a dashboard for viewing.

## Materials used: 
1. Arduino MKR ENV 1300 series
	- Arduino MKR ENV Shield 
	- Dipole Antenna for Arduino
2. Arduino Uno series
	- Dragino Lora shield v95 (915MHz for North America) 
3. Raspberry Pi with Raspberry Pi OS installed

## Setup: 
### Collecting Environmental Data ~ 
- Required Kit: 
	1. Arduino MKR WAN 1300 series -> https://store-usa.arduino.cc/products/arduino-mkr-wan-1300-lora-connectivity
	2. Arduino MKR ENV Shield      -> https://www.arduino.cc/en/Guide/MKRENVShield
	3. Dipole Antenna for Arduino  -> https://store.arduino.cc/products/dipole-pentaband-waterproof-antenna

Setup for environmental collection:
1. Mount the MKR ENV Shield on the MKR WAN 1300 series
	- The ENV shield itself collects the following environmental data: temperature, humidity, pressure, UV Index, UVB, UVA, and illuminance.  You will need to ensure the "Arduino_MKRENV" library is downloaded from the library manager via the Arduino IDE.  This is the library that is used to collect the data where you can use the 'read' methods in order to read the data[^1].   
		```C++
		#include <Arduino_MKRENV.h>
		
		void setup() {
		    Serial.begin(9600);
		    while (!Serial);
		    
		    if (!ENV.begin()) {
		        Serial.println("Failed to initialize MKR ENV shield!");
		    while (1);
		    }
		}
		void loop() {
		
		    // read all the sensor values
		    float temperature = ENV.readTemperature();
		    float humidity    = ENV.readHumidity();
		    float pressure    = ENV.readPressure();
		    float illuminance = ENV.readIlluminance();
		    float uva         = ENV.readUVA();
		    float uvb         = ENV.readUVB();
		    float uvIndex     = ENV.readUVIndex();
		    /* ------ etc. ------*/
		```  
2. Ensure the Dipole Antenna is attached to the Ardunino MKR WAN 1300 series.  Once the antenna is connected you can compile and upload ./basicSend/basicSens.ino via the Arduino IDE.  Once uploading is complete open the serial monitor, environmental data sould be printing on the monior and being sent via the antenna.  
3. ![arduino+antenna](./image_assets/arduino_antenna.png)
[^1]: https://docs.arduino.cc/tutorials/mkr-env-shield/mkr-env-shield-basic. 

   


