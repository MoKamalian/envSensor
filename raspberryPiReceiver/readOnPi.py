import serial as sr
from psr.parser import ENVParser

port_name = "/dev/ttyACM0"

test = "sensorName:sensor1,temperature:21.43,pressure:22.52,illuminance:54,humidity:33.5,uva:11,uvb:12,uvIndex:17"
parser1 = ENVParser(test)

parser1.parse()

temp = parser1.getList(["temperature", "pressure", "humidity"])
print(temp)

for key in parser1.finalArray:
    print("{key}: {value}".format(key=key, value=parser1.finalArray[key]))

port = sr.Serial(port_name, 9600)
print(port.name)
s = [0]
while True:
    read_input = port.readline()
    s[0] = str(int(port.readline(), 16))
    print(s[0])
    print(read_input)


