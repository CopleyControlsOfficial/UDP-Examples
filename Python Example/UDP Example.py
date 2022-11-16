# The following example sends serial-binary data via UDP to the drive.
# The target port is 19660. The target IP address is 192.168.0.99.
# Please read AN121 UDP Command Mode for more implementation details.

import socket
import time

# Copley Controls UDP Test

isconnected = False
Com_Socket = socket.socket(socket.AF_INET, # Internet
                socket.SOCK_DGRAM) # UDP
command = [0x00, 0x00, 0x00, 0x00]  # quick check to see if amp is there
Com_Socket.sendto(bytearray(command), ("192.168.0.99", 19660))

sresponse, addr = Com_Socket.recvfrom(50) # buffer size is 50 bytes

if(sresponse[0] > 0):
    print("Amp reported an error would procces that here.")
    isconnected = False
else:
    if(sresponse[1] > 0): #check data length
        data = bytearray(sresponse)
        del data[0:2]
        isconnected = True                                        
        print("Data Received: {0}".format(data))
    else:
        isconnected = True
        print("Zero data length command was accepted by the drive.")

if(isconnected): # now lets poll the drive
    command = [0x0C, 0x01, 0x00, 0xA0] # Get the Event Status Register
    StartTime = time.time() 
    Com_Socket.sendto(bytearray(command), ("192.168.0.99", 19660))
    sresponse, addr = Com_Socket.recvfrom(50) # buffer size is 50 bytes
    EndTime = time.time()
    TotalTime = (EndTime - StartTime) 
    if(sresponse[0] > 0):
        print("Amp reported an error would procces that here.")
    else:
        if(sresponse[1] > 0): #check data length
            data = bytearray(sresponse)
            del data[0:2]
            intresponse = int.from_bytes(sresponse[2:((sresponse[1]*2)+2)], byteorder='big', signed=True)
            hexresponse = "{0}".format(['0x%02x' % b for b in sresponse]) 
            print("")           
            print("Rcv Data Int: {0}".format(intresponse))
            #print("Rcv Data Hex: {0}".format(hexresponse))
            print("Total Time: {0}".format("{:.{}f}".format(TotalTime, 4)))
            print("")
        else:
            print("Zero data length command was accepted by the drive.")

    command = [0x0C, 0x01, 0x10, 0x80 ] #Get Drive Model Number from Flash
    StartTime = time.time() 
    Com_Socket.sendto(bytearray(command), ("192.168.0.99", 19660))
    sresponse, addr = Com_Socket.recvfrom(50) # buffer size is 50 bytes
    EndTime = time.time()
    TotalTime = (EndTime - StartTime) 

    if(sresponse[0] > 0):
        print("Amp reported an error would procces that here.")
    else:
        if(sresponse[1] > 0): #check data length
            data = sresponse.decode() #proccess as string
            strresponse = data[2:].strip('\0') #strip first 2 char and all trailing zeros
            hexresponse = "{0}".format(['0x%02x' % b for b in sresponse]) 
            print("")           
            print("Rcv Data string: {0}".format(strresponse))
            #print("Rcv Data Hex: {0}".format(hexresponse))
            print("Total Time: {0}".format("{:.{}f}".format(TotalTime, 4)))
            print("")
        else:
            print("Zero data length command was accepted by the drive.")

if(Com_Socket != None):
    Com_Socket.close()
