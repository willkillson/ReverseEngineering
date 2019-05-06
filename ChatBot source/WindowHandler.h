#include <iostream>
#include <Windows.h>
#include <WinUser.h>

#include "Psapi.h" //https://docs.microsoft.com/en-us/windows/desktop/api/psapi/nf-psapi-enumprocessmodules
#pragma once

typedef uint64_t QWORD;
using namespace std;

class WindowHandler {
	/*
		Reads and writes to windows.
	
	*/

public:
	//Variables
	DWORD processID;
	HANDLE hProcess;
	LPCTSTR LGameWindow;
	HWND hGameWindow;

	//OffSets
	QWORD   baseAddress;
	QWORD	basePointerOffset = 0x01C880B0;

	QWORD messageOffsets[4] = { 0x188, 0x108, 0x0, 0x0 };

	//data
	const static int MAX_CHAT_SIZE = 578;
	char chat[MAX_CHAT_SIZE];

public:
	//Functions
	WindowHandler(string windowTitle);
	~WindowHandler();

	void readData();



private:
	//Functions
	void getValueUsingPtrChain();


};

WindowHandler::WindowHandler(string windowTitle) {
	LGameWindow = windowTitle.c_str();
	hGameWindow = FindWindow(NULL, LGameWindow);



	if (!hGameWindow) {
		std::cout << "Get HWND failed. GetLastError = " << std::dec << GetLastError() << std::endl;
	}

	GetWindowThreadProcessId(hGameWindow, &processID);
	if (processID == NULL) {
		std::cout << "Get window PID failed. GetLastError = " << std::dec << GetLastError() << std::endl;
	}

	hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processID);
	if (hProcess == NULL)
	{
		std::cout << "Get HANDLE failed. GetLastError = " << std::dec << GetLastError() << std::endl;

	}


}

WindowHandler::~WindowHandler()
{
	CloseHandle(hProcess);
}

void WindowHandler::readData()
{
	getValueUsingPtrChain();
}

void WindowHandler::getValueUsingPtrChain()
{
	QWORD readAddress = 0;
	QWORD basePointer = this->baseAddress + this->basePointerOffset;
	LPVOID lpvBuffer = &readAddress;

	std::cout << std::hex << std::uppercase << basePointer << '\t';
	ReadProcessMemory(hProcess, (LPCVOID)basePointer, lpvBuffer, sizeof(QWORD), NULL);
	basePointer = readAddress;
	std::cout << std::hex << basePointer << std::endl;


	for (int i = 0; i < 4 - 1; i++) {
		basePointer += messageOffsets[i];

		std::cout << std::hex << std::uppercase << '[' << basePointer << " + " << messageOffsets[i] << ']' << '\t';
		ReadProcessMemory(hProcess, (LPCVOID)basePointer, lpvBuffer, sizeof(QWORD), NULL);
		basePointer = readAddress;
		std::cout << std::hex << basePointer << std::endl;

	}

	char stringBuffer[578];
	LPVOID pStringBuffer = &stringBuffer;

	basePointer += messageOffsets[3 - 1];
	ReadProcessMemory(hProcess, (LPCVOID)basePointer, pStringBuffer, sizeof(char) * 578, NULL);

	std::cout << stringBuffer;

}
