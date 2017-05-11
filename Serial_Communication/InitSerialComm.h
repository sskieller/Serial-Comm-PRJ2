#pragma once
#include <Windows.h>
#include <iostream>
#include <string>

void InitSerialComm(BOOL Status, std::wstring &comID, HANDLE &handleSerialCommPort);