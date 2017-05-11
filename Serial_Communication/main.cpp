#include <Windows.h>
#include <iostream>
#include <string>

#include "Receiving.h"
#include "Transmitting.h"
#include "InitSerialComm.h"


int main()
{
	// #############################   Variables of program ##########################################
	HANDLE handleSerialCommPort;
	BOOL Status = 0;	// Used for error checking different parts of the program
	std::wstring comID;						// CommPort, check device manager
	char * dataToSerialPortBuffer = "0";	// Data to send to the serial port
	std::string recievedString;				// Data from the serial port

	
	toTransmit(dataToSerialPortBuffer);
	std::cout << std::endl;

	InitSerialComm(Status, comID, handleSerialCommPort);
	std::cout << std::endl;
	
	Transmitting(Status, handleSerialCommPort, dataToSerialPortBuffer, comID);
	std::cout << std::endl;
	
	Recieving(Status, handleSerialCommPort, comID);
	std::cout << std::endl;
	
	system("PAUSE");
	return 0;
}