import socket

# Copley Controls UDP Test
# The following example makes a relative trapezoidal move on Axis A of a Copley Controls servo drive.
# Please refer to AN121 which is the applications note for UDP Command Mode.
# Please also refer to AN139 which will provide helpful command sequences to command motion.

def PrintResponse(socket):
   sresponse, addr = socket.recvfrom(50) # buffer size is 50 bytes

   if(sresponse[0] > 0):
      print("Amp reported an error.")
      return False
   else:
      if(sresponse[1] > 0): #check data length
         data = sresponse.decode() #proccess as string
         strresponse = data[2:].strip('\0') #strip first 2 char and all trailing zeros
         hexresponse = "{0}".format(['0x%02x' % b for b in sresponse]) 
         print("Rcv Data string: {0}".format(strresponse))
         #print("Rcv Data Hex: {0}".format(hexresponse))
         return True
      else:
         return True


isconnected = False
ipAddress = "192.168.0.12"
udpPortForSerialBinaryData = 19660
Com_Socket = socket.socket(socket.AF_INET, # Internet
                socket.SOCK_DGRAM) # UDP

command = [0x00, 0x00, 0x00, 0x00]  # quick check to see if amp is there
Com_Socket.sendto(bytearray(command), (ipAddress, udpPortForSerialBinaryData))
isconnected = PrintResponse(Com_Socket)

if(isconnected):
   
   # set the desired state to 0x15 (trajectory generator drives position loop)
   command = [0x0D, 0x02, 0x00, 0x24, 0x00, 0x15]
   Com_Socket.sendto(bytearray(command), (ipAddress, udpPortForSerialBinaryData))
   PrintResponse(Com_Socket)
   
   # set trajectory profile mode to trapezoidal relative move (set 0xC8 to 0x100)
   command = [0x0D, 0x02, 0x00, 0xC8, 0x01, 0x00]
   Com_Socket.sendto(bytearray(command), (ipAddress, udpPortForSerialBinaryData))
   PrintResponse(Com_Socket)
   
   # set commanded position to 0x00000FA0 counts
   command = [0x0D, 0x03, 0x00, 0xCA, 0x00, 0x00, 0x0F, 0xA0]
   Com_Socket.sendto(bytearray(command), (ipAddress, udpPortForSerialBinaryData))
   PrintResponse(Com_Socket)
   
   # set max velocity to 0x00042AAB 0.1 counts/sec
   command = [0x0D, 0x03, 0x00, 0xCB, 0x00, 0x04, 0x2A, 0xAB]
   Com_Socket.sendto(bytearray(command), (ipAddress, udpPortForSerialBinaryData))
   PrintResponse(Com_Socket)
   
   # set max acceleration to 0x00042AAB 0.1 counts/sec^2
   command = [0x0D, 0x03, 0x00, 0xCC, 0x00, 0x04, 0x2A, 0xAB]
   Com_Socket.sendto(bytearray(command), (ipAddress, udpPortForSerialBinaryData))
   PrintResponse(Com_Socket)
   
   # set max deceleration to 0x00042AAB 0.1 counts/sec^2
   command = [0x0D, 0x03, 0x00, 0xCD, 0x00, 0x04, 0x2A, 0xAB]
   Com_Socket.sendto(bytearray(command), (ipAddress, udpPortForSerialBinaryData))
   PrintResponse(Com_Socket)
   
   # send trajectory update
   command = [0x11, 0x01, 0x00, 0x01]   
   Com_Socket.sendto(bytearray(command), (ipAddress, udpPortForSerialBinaryData))
   PrintResponse(Com_Socket)
   
if(Com_Socket != None):
    Com_Socket.close()
