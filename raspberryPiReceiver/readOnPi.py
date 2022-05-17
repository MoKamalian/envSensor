"""
Author: amir kamalian, carlington palmer
Date:   17-May-2022
Description:
"""
import serial as sr
import cayenne.client as cncl
import time
from psr.parser import ENVParser

# port and authentication info for cayenne
MQTT_USR = "MQTTusername"
MQTT_PASS = "MQTTpassword"
MQTT_CLID = "MQTTclientID"
port_name = "/dev/ttyACM0"

# initialize client object to establish connection to cayenne.  Port 8883 is meant
# for secure connections if needed in the begin method.
client = cncl.CayenneMQTTClient()
client.begin(MQTT_USR, MQTT_PASS, MQTT_CLID)

# data format acceptable to parser.
# test = "sensorName:sensor1,temperature:21.43,pressure:22.52,illuminance:54,humidity:33.5,uva:11,uvb:12,uvIndex:17"

# initialize parser object
parser1 = ENVParser()


port = sr.Serial(port_name, 9600)
print(port.name)

i = 0
time_stamp = 0

while True:
    # reading from serial port on the Raspberry Pi
    read_input = port.readline()
    temp = str(int(port.readline(), 16))
    print(temp)
    print(read_input)

    # parsing the received data through the serial port
    parser1.data(temp)
    parser1.parse()

    # data values
    VALUES = parser1.getList(["sensorName", "temperature", "pressure", "humidity", "uvIndex"])
    SENSOR   = VALUES[0]
    TEMP     = VALUES[1]
    PRESSURE = VALUES[2]
    HUMIDITY = VALUES[3]
    UVINDEX  = VALUES[4]

    # sending data out to cayenne dashboard
    client.loop()

    if time.time() > (time_stamp + 10):
        client.celsiusWrite(1, TEMP)







