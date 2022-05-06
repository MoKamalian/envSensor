import serial as sr 

port_name = "/dev/ttyACM0"

port = sr.Serial(port_name, 9600)
print(port.name)
s = [0]
while True:
    read_input = port.readline()
    s[0] = str(int(port.readline(), 16))
    print(s[0])
    print(read_input)


