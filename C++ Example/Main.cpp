// Main.cpp
// 
// The following example sends serial - binary data via UDP to the drive.
// The target port is 19660. The target IP address is 192.168.1.4
// Please read AN121 UDP Command Mode for more implementation details.

#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include "CopleyUDP.h"

using namespace std;

int main()
{
    // Set this to the the drives IP address (configurable in CME)
    std::string IP = "192.168.1.4";
    int PORT = 19658;// Listening for ASCII commands (default) 
    WSASession Session;
    UDPSocket Socket;
    string data;        // String which will contain ASCII commands 
    string response;
    char* byteArray{};
    int ret;
    char buffer[50];

    try
    {
        PORT = 19660; // Listening for Serial Binary commands
        Socket.Bind(PORT);

        if (PORT == 19660) // Handle serial binary responses
        {
            // This block of code can handle 
            byteArray = new char[4]{ 0x00, 0x00, 0x00, 0x00 }; // Check that the amp is there
            Socket.SendTo(IP, PORT, byteArray, 4);
            cout << "Serial Binary Command Sent\n";
            ret = Socket.RecvFrom(buffer, sizeof(buffer), 0);   // Find out how many bytes we read
            cout << "Response received: ";
            for (int i = 0; i < ret; i++)
            {
                cout << hex << setw(2) << setfill('0') << unsigned(buffer[i]) << " ";
            }
            cout << endl << endl;
            delete[] byteArray, buffer;

            byteArray = new char[4]{ 0x0c, 0x01, 0x00, char(0xa0) }; // Get the Event Status Register
            Socket.SendTo(IP, PORT, byteArray, 4);
            cout << "Serial Binary Command Sent\n";
            ret = Socket.RecvFrom(buffer, sizeof(buffer), 0);   // Find out how many bytes we read
            cout << "Response received: ";
            for (int i = 0; i < ret; i++)
            {
                cout << hex << setw(2) << setfill('0') << unsigned(buffer[i]) << " ";
            }
            cout << endl << endl;
            delete[] byteArray, buffer;

            byteArray = new char[4]{ 0x0c, 0x01, 0x10, char(0x80) }; // Get Drive Model Number from Flash
            Socket.SendTo(IP, PORT, byteArray, 4);
            cout << "Serial Binary Command Sent\n";
            ret = Socket.RecvFrom(buffer, sizeof(buffer), 0);   // Find out how many bytes we read
            cout << "Response received: ";
            for (int i = 0; i < ret; i++)
            {
                cout << buffer[i];
            }
            cout << endl << endl;
            delete[] byteArray, buffer;

            byteArray = new char[4]{ 0x0c, 0x01, 0x00, char(0x94) }; // Get Firmware Version from RAM
            Socket.SendTo(IP, PORT, byteArray, 4);
            cout << "Serial Binary Command Sent\n";
            ret = Socket.RecvFrom(buffer, sizeof(buffer), 0);   // Find out how many bytes we read
            cout << "Response received: ";
            for (int i = 0; i < ret; i++)
            {
                cout << hex << setw(2) << setfill('0') << unsigned(buffer[i]) << " ";
            }
            cout << endl << endl;
            delete[] byteArray, buffer;

            byteArray = new char[6]{ 0x0D, 0x02, 0x00, 0x24, 0x00, 0x16 }; // Set Desired State to 22
            Socket.SendTo(IP, PORT, byteArray, sizeof(byteArray));
            cout << "Serial Binary Command Sent\n";
            ret = Socket.RecvFrom(buffer, sizeof(buffer), 0);   // Find out how many bytes we read
            cout << "Response received: ";
            for (int i = 0; i < ret; i++)
            {
                cout << hex << setw(2) << setfill('0') << unsigned(buffer[i]) << " ";
            }
            cout << endl << endl;
            delete[] byteArray, buffer;

            byteArray = new char[4]{ 0x0c, 0x01, 0x00, char(0x24) }; // Get Desired State
            Socket.SendTo(IP, PORT, byteArray, sizeof(byteArray));
            cout << "Serial Binary Command Sent\n";
            ret = Socket.RecvFrom(buffer, sizeof(buffer), 0);   // Find out how many bytes we read
            cout << "Response received: ";
            for (int i = 0; i < ret; i++)
            {
                cout << hex << setw(2) << setfill('0') << unsigned(buffer[i]) << " ";
            }
            cout << endl << endl;
            delete[] byteArray, buffer;

            byteArray = new char[6]{ 0x0D, 0x02, 0x00, 0x24, 0x00, 0x1e }; // Set Desired State to 30
            Socket.SendTo(IP, PORT, byteArray, sizeof(byteArray));
            cout << "Serial Binary Command Sent\n";
            ret = Socket.RecvFrom(buffer, sizeof(buffer), 0);   // Find out how many bytes we read
            cout << "Response received: ";
            for (int i = 0; i < ret; i++)
            {
                cout << hex << setw(2) << setfill('0') << unsigned(buffer[i]) << " ";
            }
            cout << endl << endl;
            delete[] byteArray, buffer;

            byteArray = new char[4]{ 0x0c, 0x01, 0x00, char(0x24) }; // Get Desired State
            Socket.SendTo(IP, PORT, byteArray, sizeof(byteArray));
            cout << "Serial Binary Command Sent\n";
            ret = Socket.RecvFrom(buffer, sizeof(buffer), 0);   // Find out how many bytes we read
            cout << "Response received: ";
            for (int i = 0; i < ret; i++)
            {
                cout << hex << setw(2) << setfill('0') << unsigned(buffer[i]) << " ";
            }
            cout << endl << endl;
            delete[] byteArray, buffer;


            byteArray = new char[2]{ 0x07, 0x00 }; // Get Operating Mode
            Socket.SendTo(IP, PORT, byteArray, sizeof(byteArray));
            cout << "Serial Binary Command Sent\n";
            ret = Socket.RecvFrom(buffer, sizeof(buffer), 0);   // Find out how many bytes we read
            cout << "Response received: ";
            for (int i = 0; i < ret; i++)
            {
                cout << hex << setw(2) << setfill('0') << unsigned(buffer[i]) << " ";
            }
            cout << endl << endl;
            delete[] byteArray, buffer;
        }
        else // Handle ASCII responses
        {
            // Send an ASCII formatted string to the drive
            data = "g r0x24\r"; // Get desired state
            cout << "ASCII Command Sent: " << data << endl;
            Socket.SendTo(IP, PORT, data.c_str(), data.size());
            ret = Socket.RecvFrom(buffer, sizeof(buffer), 0);
            response = string(buffer);
            cout << "Data received: " << response << endl;

            data = "s r0xa4 0xffff\r"; // Clear latched event status register
            cout << "ASCII Command Sent: " << data << endl;
            Socket.SendTo(IP, PORT, data.c_str(), data.size());
            ret = Socket.RecvFrom(buffer, sizeof(buffer), 0);
            response = string(buffer);
            cout << "Data received: " << response << endl;
        }

    }
    catch (exception& ex)
    {
        cout << ex.what();
    }

}