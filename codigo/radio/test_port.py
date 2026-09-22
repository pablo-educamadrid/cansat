import sys
import glob
import serial


def serial_ports():
    """ Lists serial port names

        :raises EnvironmentError:
            On unsupported or unknown platforms
        :returns:
            A list of the serial ports available on the system
    """
    if sys.platform.startswith('win'):
        ports = ['COM%s' % (i + 1) for i in range(256)]
    elif sys.platform.startswith('linux') or sys.platform.startswith('cygwin'):
        # this excludes your current terminal "/dev/tty"
        ports = glob.glob('/dev/tty[A-Za-z]*')
    elif sys.platform.startswith('darwin'):
        ports = glob.glob('/dev/tty.*')
    else:
        raise EnvironmentError('Unsupported platform')

    result = []
    index = 0;
    for port in ports:
        try:
            s = serial.Serial(port)
            s.close()
            result.append((index,port))
            index = index+1
        except (OSError, serial.SerialException):
            pass
        
    return result


if __name__ == '__main__':
    ports = serial_ports()
    print "select port: "
    for p in ports:
        print(str(p[0]) + ": - " + p[1])
    

    val = input("Enter your value: ")
    index = int(val)
    print("selected port")
    selected_port = ports[index][1]
    print(selected_port)

    ser = serial.Serial(
        # Serial Port to read the data from
        port=selected_port,
 
        #Rate at which the information is shared to the communication channel
        baudrate = 9600,
   
        #Applying Parity Checking (none in this case)
        parity=serial.PARITY_NONE,
 
       # Pattern of Bits to be read
        stopbits=serial.STOPBITS_ONE,
     
        # Total number of bits to be read
        bytesize=serial.EIGHTBITS,
 
        # Number of serial commands to accept before timing out
        timeout=1
        )
    # Pause the program for 1 second to avoid overworking the serial port
    for i in range(100):
        x=ser.readline()
        print x
        print i