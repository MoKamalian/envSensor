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

**Setup for environmental collection:**

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

2. Connect the Arduino with the shield mounted to the computer via USB.  Select the port and corresponding MKR WAN 1300 Arduino board from the **Tools** menu.  You will need to install the **Aurdino SAMD Boards (32-bits ARM Cortex-M0+)** from the boards manager in order to be able to select the Arduino MKR WAN 1300 series board. 

3. Ensure the Dipole Antenna is attached to the Ardunino MKR WAN 1300 series.  Once the antenna is connected you can compile and upload ./basicSend/basicSens.ino via the Arduino IDE.  Once uploading is complete open the serial monitor, environmental data sould be printing on the monior and being sent via the antenna.    
![arduino+antenna](./image_assets/arduino_antenna.png)  

4. Troubleshooting issues: 
	- Port selection greyed out: on Windows computer you may simply have to unplug and replug the Arduino into the USB port.  On Linux you may have to open the Arduino IDE with `sudo` privilages[^2].  


### One to One Connection to a Reciever Node ~  
- Required Kit: 
	1. 2 X Arduino MKR WAN 1300 series -> https://store-usa.arduino.cc/products/arduino-mkr-wan-1300-lora-connectivity
	2. 2 X Dipole Antenna for Arduino  -> https://store.arduino.cc/products/dipole-pentaband-waterproof-antenna
	3. 1 X Arduino MKR ENV Shield      -> https://www.arduino.cc/en/Guide/MKRENVShield

**Setup for simple one to one connection:** 
1. This setup involves connecting two Arduino MKR ENV 1300 series via LoRa, one being the sender node and one being the reciever node.  The setup essentially involves the sender node transmitting data and the reciever listening and readnig the tranmitted data; both using radio frequency number 915E6 (for North America)[^3].

2. As before set up an Arduino MKR ENV 1300 series with the ENV Shield, and have it collect environmental data.

3. You will require the **SPI** and the **LoRa** libraries downloaded in order to establish the connection.  

	```C++
	#include <Arduino_MKRENV.h>
	#include <LoRa.h>

	String sensorName = "sensor1,";
	
	/*-----------inside void setup------------*/
	  /* initialize the LoRa connection */
	  if (!LoRa.begin(915E6)) {
	    Serial.println("Starting LoRa failed!");
	    while (1);
	  }


	/*-----------inside void loop-------------*/ 
	  // send packet
	  LoRa.beginPacket();

	  LoRa.print("sensorName:");
	  LoRa.print(sensorName);

	  LoRa.print("temperature:");
	  LoRa.print(temperature);
	  LoRa.print(",");
	/*------------------etc.------------------*/
	  ```


[^1]: https://docs.arduino.cc/tutorials/mkr-env-shield/mkr-env-shield-basic.
[^2]: https://forum.arduino.cc/t/port-grayed-out-under-tools-port/408689
[^3]: https://docs.arduino.cc/tutorials/mkr-wan-1300/lora-send-and-receive
