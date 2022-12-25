#import smbus
#import time

address = 0x23  #BH1750 sensor default address given by the industry itself
start = 0x01  #LSB for starting the data transfer
stop = 0x00 #LSB for stopping the data transfer
reset = 0x07  #An address used for resetting the whole process

bus = smbus.SMBus(1)

def lightRead():
  newAddress = bus.read_i2c_block_data(address, address)
  value = lightConversion(newAddress)
  return value
  
def lightConversion(newAddress):
  conversion = ((newAddress[1] + (256 * newAddress[0]))/1.2)
  return conversion

try:
  while 1:
    intensity = lightRead()
    print(f"Reading: {intensity}")
    
    print("Status:")
    if(intensity >= 4000):
      print("Status: Too bright")
    elif(intensity >= 500 and intensity < 4000):
      print("Status: Bright")
    elif(intensity >= 100 and intensity < 500):
      print("Status: Medium")
    elif(intensity > 50 and intensity < 100):
      print("Status: Dark")
    elif(intensity < 50):
      print("Status: Too dark")
    time.sleep(1)

except KeyboardInterrupt:
  print("Exitting")
