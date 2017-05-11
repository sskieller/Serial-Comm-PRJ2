#include "Receiving.h"


std::string Recieving(BOOL Status, HANDLE handleSerialCommPort, std::wstring comID) {

	// A variable that recieves a mask which indicates which type of event occured.
	// If an error occurs the value is 0. If an event occurs, in this case EV_RXCHAR, 
	// the variable dWordEventMask recieves the value 0x0001
	DWORD dWordEventMask;
	char TemporaryChar;					// Temporary char to recieve data
	char SerialRecieverBuffer[256];		// Buffer for temporary char 
	DWORD NoBytesRead;					// Checking bytes read by function ReadFile()
	int i = 0;							// Variable for storing data on SerialRecieverBuffer
	std::string recievedString;			// String for getting char data from SerialRecieverBuffer

	// ##########################   SetCommMask   ####################################################
	// Configuring Windows to monitor the CommPort for Character Reception by using setting EV_RXCHAR
	// The Comm Mask is a function who specifies a set of events to be monitored for the comm device defined by the handle.

	// Checking for error
	Status = SetCommMask(handleSerialCommPort, EV_RXCHAR);

	if (Status == FALSE)	// If function fails
	{
		std::cout << "Unsuccesful in SetCommMask." << std::endl;
	}
	else
	{
		std::cout << "Succesful in SetCommMask." << std::endl;
	}

	// ##########################   WaitCommEvent   ##################################################

	std::cout << "Waiting for data to be recieved." << std::endl;

	// Checking for error
	Status = WaitCommEvent(handleSerialCommPort,	// CommPort
		&dWordEventMask,		// Event mask to trigger
		NULL);					// Is it overlapped? NULL = No

	if (Status == FALSE)
	{
		std::cout << "Unsuccesful in setting WaitCommEvent." << std::endl;
	}
	else
	{
		i = 0;		// Resetting the buffer position
		std::wcout << "Characters recieved from " << comID << "." << std::endl;

		do
		{
			Status = ReadFile(handleSerialCommPort,	// CommPort
				&TemporaryChar,			// Buffer recieving data from port, empties automatically by ReadFile
				sizeof(TemporaryChar),	// Max number of bytes to be read
				&NoBytesRead,			// Number of bytes succesfully read
				NULL);					// Is it overlapped? NULL = No
			SerialRecieverBuffer[i] = TemporaryChar;
			i++;
		} while (NoBytesRead > 0);	// While number of bytes read is over zero, i.e. has recieved any data


		for (int j = 0; j < i - 1; j++) // i - 1 makes sure not to print the duplicated char in the end of recieved string
		{
			recievedString.push_back(SerialRecieverBuffer[j]);	// Writing the buffer to variable recieved string for return
		}


		//// Uncomment to write to terminal screen in function without string recievedString
		//// Afterwards writing the buffer to the terminal screen:
		//std::cout << std::endl << "The string recieved from controller is: " << std::endl;
		//for (int j = 0; j < i - 1; j++) // i - 1 makes sure not to print the duplicated char in the end of recieved string
		//{
		//	std::cout << SerialRecieverBuffer[j];	// Writing all the recieved characters
		//}
		//
		//std::cout << std::endl << std::endl;	// Making space


	}

	// #############################   Closing the CommPort   ########################################

	std::wcout << "Closing " << comID << "." << std::endl;
	CloseHandle(handleSerialCommPort);	// Closing the serial port
	std::cout << "+=============================================+" << std::endl;


	return recievedString;
}