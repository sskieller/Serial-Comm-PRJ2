#include "Transmitting.h"

void Transmitting(BOOL Status, HANDLE handleSerialCommPort, char dataToSerialPortBuffer[], std::wstring comID) {
	
	// #############################   WriteFile()   #################################################

	// Writing data to the opened COM port uses the WriteFile() function.
	// This function can be used to write both into files and into I/O ports.


	DWORD dWordNumberOfBytesToWrite;	// Number of bytes to write into the port
	DWORD dWordNumberOfBytesWritten = 0;	// Number of bytes already succesfully written into the port

	dWordNumberOfBytesToWrite = sizeof(dataToSerialPortBuffer);	// Number of bytes = size of buffer


																// Checking for error
	Status = WriteFile(handleSerialCommPort,		// Handle for the CommPort
		dataToSerialPortBuffer,		// Data which is to be written to the CommPort
		dWordNumberOfBytesToWrite,	// Number of bytes to write
		&dWordNumberOfBytesWritten,	// Number of bytes already succesfully written
		NULL);						// Is it overlapped? NULL = No

	if (Status == TRUE)	// If succesfully writing to Port
	{
		std::cout << "Character: \"" << dataToSerialPortBuffer << "\" written to port" << std::endl;
	}
	else // If not succesfully writing to Port
	{
		std::wcout << "Writing to " << comID << " was unsuccesful." << std::endl;
	}
	// #############################   Closing the CommPort   ########################################

	std::wcout << "Closing " << comID << "." << std::endl;
	CloseHandle(handleSerialCommPort);	// Closing the serial port
	std::cout << "+=============================================+" << std::endl;
}

void toTransmit(char * dataToSerialPortBuffer)
{
	std::string dataToSend;
	std::cout << "Please insert the data to send: " << std::endl;
	std::cin >> dataToSend;

	dataToSerialPortBuffer = new char[dataToSend.length() + 1];
	std::strcpy(dataToSerialPortBuffer, dataToSend.c_str());	// Data to write to the serial port

}

