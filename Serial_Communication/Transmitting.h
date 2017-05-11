#pragma once
#include <Windows.h>
#include <iostream>
#include <string>

void Transmitting(BOOL Status, HANDLE handleSerialCommPort, char dataToSerialPortBuffer[], std::wstring comID);


void toTransmit(char * dataToSerialPortBuffer);