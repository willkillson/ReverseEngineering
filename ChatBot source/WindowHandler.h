#include <iostream>
#include <Windows.h>
#include <WinUser.h>
#include <vector>

#include "Psapi.h" //https://docs.microsoft.com/en-us/windows/desktop/api/psapi/nf-psapi-enumprocessmodules
#pragma once

typedef uint64_t QWORD;
using namespace std;

class WindowHandler {
	/*
		Reads and writes to windows.
	
	*/

public:		//Variables

	//settings
	bool debug;

	//data
	const static int MAX_CHAT_SIZE = 578;
	char chat[MAX_CHAT_SIZE];

private:	//variables

	//WindowsSpecific
	DWORD processID;
	HANDLE hProcess;
	LPCTSTR LGameWindow;
	HWND hGameWindow;

	//OffSets
	QWORD   baseAddress;
	QWORD	basePointerOffset = 0x01C8EB10;

	vector<QWORD> messageOffsets = { 0x68, 0x0, 0x0 };

public:		//Functions
	WindowHandler(string windowTitle);
	~WindowHandler();

	void readData();



private:	//Functions
	void getValueUsingPtrChain();
	void getBasePointer();


};

WindowHandler::WindowHandler(string windowTitle) {
	debug = false;//default debug

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

	getBasePointer();

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

	if (debug)
		std::cout << std::hex << std::uppercase <<"["<< this->baseAddress << " + " << this->basePointerOffset << "]" << '\t'<< "->"<<'\t';

	QWORD readAddress = 0;
	QWORD basePointer = this->baseAddress + this->basePointerOffset;
	LPVOID lpvBuffer = &readAddress;

	ReadProcessMemory(hProcess, (LPCVOID)basePointer, lpvBuffer, sizeof(QWORD), NULL);
	basePointer = readAddress;

	if (debug)
		std::cout << std::hex << basePointer << std::endl;


	for (int i = 0; i < this->messageOffsets.size() - 1; i++) {
		basePointer += messageOffsets[i];

		if (debug)		
			std::cout << std::hex << std::uppercase << '[' << basePointer << " + " << messageOffsets[i] << ']' << "\t\t" << "->" << '\t';

		ReadProcessMemory(hProcess, (LPCVOID)basePointer, lpvBuffer, sizeof(QWORD), NULL);
		basePointer = readAddress;

		if (debug)
			std::cout << std::hex << basePointer << std::endl;

	}

	char stringBuffer[578];
	LPVOID pStringBuffer = &stringBuffer;

	basePointer += messageOffsets[this->messageOffsets.size()-1];
	ReadProcessMemory(hProcess, (LPCVOID)basePointer, pStringBuffer, sizeof(char) * 578, NULL);

	if (debug)
		std::cout <<"\nContents" << endl <<  stringBuffer << endl;

}

inline void WindowHandler::getBasePointer()
{

	HMODULE*	moduleArray;
	LPBYTE      moduleArrayBytes;
	DWORD       bytesRequired;


	if (this->hProcess)
	{
		if (EnumProcessModules(this->hProcess, NULL, 0, &bytesRequired))
		{
			if (bytesRequired)
			{
				moduleArrayBytes = (LPBYTE)LocalAlloc(LPTR, bytesRequired);

				if (moduleArrayBytes)
				{
					unsigned int moduleCount;

					moduleCount = bytesRequired / sizeof(HMODULE);
					moduleArray = (HMODULE*)moduleArrayBytes;

					if (EnumProcessModules(this->hProcess, moduleArray, bytesRequired, &bytesRequired))
					{
						baseAddress = (DWORD_PTR)moduleArray[0];
					}

					LocalFree(moduleArrayBytes);
				}
			}
		}
	}


}
