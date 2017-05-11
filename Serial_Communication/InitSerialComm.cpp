#include "InitSerialComm.h"

void InitSerialComm(BOOL Status, std::wstring &comID, HANDLE &handleSerialCommPort)
{
	// #############################   Naming handle   ###############################################
	// wstring: wide string to support all members of the largest extended character set (Needed for Windows API)
	std::wstring comNumber;								// For entering COM number
	std::wcout << L"\n\nEnter the port (ex: COM20): ";
	std::wcin >> comNumber;								// Getting COM number
	std::wstring comPrefix = L"\\\\.\\";				// Adding needed prefix
	comID = comPrefix + comNumber;			// Concatenating the prefix with COM

	std::cout << "+=============================================+" << std::endl;
	std::wcout << "|         Serial Transmission to " << comID << "     |" << std::endl;
	std::cout << "+=============================================+" << std::endl;

	// #############################   CreateFile()   ################################################
	handleSerialCommPort = CreateFile(comID.c_str(),		// Port name, needs to be c_str
		GENERIC_READ | GENERIC_WRITE,	// Read/Write
		0,								// No Sharing
		NULL,							// No Security
		OPEN_EXISTING,					// Open Existing Port Only
		0,								// Non Overlapped I/O // Overlapped is for multithreading programs
		NULL);							// Null for Comm Devices

										// Checking for error
	if (handleSerialCommPort == INVALID_HANDLE_VALUE)
	{
		std::cout << "Error in opening serial port." << std::endl;
	}
	else
	{
		std::wcout << "Port " << comPrefix << comNumber << " opened." << std::endl;
	}

	// #############################   SetCommState()   ##############################################

	DCB dcbSerialParams = { 0 };	// Init DCB structure for Baud rate, number of start/stop bits, data format
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);	// Setting length to number of settings


															// Checking for error
	Status = GetCommState(handleSerialCommPort, &dcbSerialParams);
	if (Status == FALSE)
	{
		std::cout << "Error in GetCommState." << std::endl;
	}
	else
	{
		std::cout << "Succesful in GetCommState." << std::endl;
	}

	// Retrieving current settings of serial port
	// GetCommState returns !0 if the function succeeds, returns 0 if function fails
	Status = GetCommState(handleSerialCommPort, &dcbSerialParams);

	// Settings for the COM port
	dcbSerialParams.BaudRate = CBR_9600;	// Setting BAUDRate = 9600
	dcbSerialParams.ByteSize = 8;			// Setting ByteSize = 8
	dcbSerialParams.StopBits = ONESTOPBIT;	// Setting StopBits = 1
	dcbSerialParams.Parity = NOPARITY;		// Setting Parity	= None

											// Settings put onto the COM port
	SetCommState(handleSerialCommPort, &dcbSerialParams);	// SetCommState( CommPort, DCB Settings)

															// Checking for error
	Status = SetCommState(handleSerialCommPort, &dcbSerialParams);
	if (Status == FALSE)
	{
		std::cout << "Error in SetCommState." << std::endl;
	}
	else
	{
		std::wcout << "Succesfully set the settings for " << comID << "." << std::endl;
		std::wcout << "   BaudRate = " << dcbSerialParams.BaudRate << "." << std::endl;
		std::wcout << "   ByteSize = " << dcbSerialParams.ByteSize << "." << std::endl;
		std::wcout << "   StopBits = " << dcbSerialParams.StopBits << "." << std::endl;
		std::wcout << "   Parity   = " << dcbSerialParams.Parity << "." << std::endl;
	}


	// #############################   SetCommTimeouts()   ###########################################

	// To prevent the program from waiting endlessly we make timeouts for the program, to only check
	// at certain intervals, which were gonna set to 50 milliseconds in this case.

	COMMTIMEOUTS timeouts = { 0 };	// Init timeout structure

									// ReadIntervalTimeout: 
									// Sets max time interval between arrival of two bytes.
									// Longer time interval means the ReadFile() function returns.
	timeouts.ReadIntervalTimeout = 50;			// Milliseconds

												// ReadTotalTimeoutConstant: 
												// Calculates total time-out period of read operations.
												// For every read operation, the value is added to the product of 
												// ReadTotalTimeoutMultiplier member + number of requested bytes.
	timeouts.ReadTotalTimeoutConstant;			// Milliseconds

												// ReadTotalTimeoutMultiplier:
												// Calculates total timee-out period for read operations.
												// For each read operation, the value is multiplied by the numbers of bytes requested to read.
	timeouts.ReadTotalTimeoutMultiplier = 10;	// Milliseconds

												// WriteTotalTimeoutConstant:
												// Used for Write operations, but similar to ReadTotalTimeoutConstant
	timeouts.WriteTotalTimeoutConstant = 50;	// Milliseconds

												// WriteTotalTimeoutMultiplier:
												// Used for Write operations, but similar to ReadTotalTimeoutMultiplier
	timeouts.WriteTotalTimeoutMultiplier = 10;	// Milliseconds


												// Checking for error
	Status = SetCommTimeouts(handleSerialCommPort, &timeouts);
	if (Status == FALSE)
	{
		std::cout << "Error in setting timeouts." << std::endl;
	}
	else
	{
		std::cout << "Succesful in setting the timeouts" << std::endl;
	}

	// ###############################################################################################
}