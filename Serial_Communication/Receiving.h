#pragma once
#include <Windows.h>
#include <iostream>
#include <string>


std::string Recieving(BOOL Status, HANDLE handleSerialCommPort, std::wstring comID);