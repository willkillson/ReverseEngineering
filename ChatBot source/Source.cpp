#include <iostream>
#include <Windows.h>
#include <WinUser.h>
#include "Psapi.h" //https://docs.microsoft.com/en-us/windows/desktop/api/psapi/nf-psapi-enumprocessmodules



//#define TARGET_X64
//
//#ifdef TARGET_X64
//typedef unsigned __int64 addr_ptr;
//#else
//typedef unsigned int addr_ptr;
//#endif
//
//typedef struct tagINPUT {
//	DWORD type;
//	union {
//		MOUSEINPUT    mi;
//		KEYBDINPUT    ki;
//		HARDWAREINPUT hi;
//	} DUMMYUNIONNAME;
//} INPUT, * PINPUT, * LPINPUT;
//
//typedef struct tagKEYBDINPUT {
//	WORD      wVk;
//	WORD      wScan;
//	DWORD     dwFlags;
//	DWORD     time;
//	ULONG_PTR dwExtraInfo;
//} KEYBDINPUT, * PKEYBDINPUT, * LPKEYBDINPUT;



using namespace std;

INPUT ip;


typedef uint64_t QWORD;

DWORD_PTR GetProcessBaseAddress(DWORD processID)
{

	/*
		This code was lifted from,
		https://stackoverflow.com/questions/26572459/c-get-module-base-address-for-64bit-application
	*/

	DWORD_PTR   baseAddress = 0;
	HANDLE      processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processID);
	HMODULE* moduleArray;
	LPBYTE      moduleArrayBytes;
	DWORD       bytesRequired;

	if (processHandle)
	{
		if (EnumProcessModules(processHandle, NULL, 0, &bytesRequired))
		{
			if (bytesRequired)
			{
				moduleArrayBytes = (LPBYTE)LocalAlloc(LPTR, bytesRequired);

				if (moduleArrayBytes)
				{
					unsigned int moduleCount;

					moduleCount = bytesRequired / sizeof(HMODULE);
					moduleArray = (HMODULE*)moduleArrayBytes;

					if (EnumProcessModules(processHandle, moduleArray, bytesRequired, &bytesRequired))
					{
						baseAddress = (DWORD_PTR)moduleArray[0];
					}

					LocalFree(moduleArrayBytes);
				}
			}
		}

		CloseHandle(processHandle);
	}

	return baseAddress;
}

float getFloatUsingAddress(QWORD bp, HANDLE hProcess) {
	bool fail_flag = false;

	float inRead = 0;
	LPVOID lpvBuffer = &inRead;

	ReadProcessMemory(hProcess, (LPCVOID)bp, lpvBuffer, sizeof(float), NULL);


	return inRead;


}

char* getValueUsingPtrChain(QWORD bp, QWORD Offsets[], int depth, HANDLE hProcess) {

	bool fail_flag = false;

	QWORD readAddress = 0;
	QWORD basePointer = bp;

	LPVOID lpvBuffer = &readAddress;

	std::cout << std::hex << std::uppercase << basePointer << '\t';
	ReadProcessMemory(hProcess, (LPCVOID)basePointer, lpvBuffer, sizeof(QWORD), NULL);
	basePointer = readAddress;
	std::cout << std::hex << basePointer << std::endl;

	for (int i = 0; i < depth-1; i++) {
		basePointer += Offsets[i];

		std::cout << std::hex << std::uppercase <<'['<< basePointer <<" + " << Offsets[i]<<']' << '\t';
		ReadProcessMemory(hProcess, (LPCVOID)basePointer, lpvBuffer, sizeof(QWORD), NULL);
		basePointer = readAddress;
		std::cout << std::hex << basePointer << std::endl;

	}

	char stringBuffer[578];
	LPVOID pStringBuffer = &stringBuffer;

	basePointer += Offsets[depth - 1];
	ReadProcessMemory(hProcess, (LPCVOID)basePointer, pStringBuffer, sizeof(char)* 578, NULL);

	std::cout << stringBuffer;


	if (fail_flag)
		std::cout << "getValueUsingPtrChain: failed" << std::endl;

	return stringBuffer;
}

void clearScreen(int x, int y) {

	HANDLE hOut;
	COORD Position;

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	Position.X = x;
	Position.Y = y;
	SetConsoleCursorPosition(hOut, Position);


	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

void clearScreen() {

	HANDLE hOut;
	COORD Position;

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);


	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

void printChat(char *message) {


	string m(message);

	auto itb = m.begin();
	auto ite = m.end();

	m.replace(itb+20, itb + 54, "");

	while (*itb != '\n'&& itb<ite) {
		printf("%c", *itb);
		itb++;
	}

	printf("\n");

}

void press() {
	// Press the "A" key
	ip.ki.wVk = 0x0D; // virtual-key code for the "a" key
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	// Release the "A" key
	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
}

//
//
//int main() {
//
//
//
//
//
//	LPCTSTR LGameWindow = "Path of Exile";
//	HWND hGameWindow = FindWindow(NULL, LGameWindow);
//	if (!hGameWindow) {
//		std::cout << "Game not found. GetLastError = " << std::dec << GetLastError() << std::endl;
//		return EXIT_FAILURE;
//	}
//	std::cout << "Game found" << std::endl;
//
//	//Finding the processID of the game window
//	DWORD  processID = 9716;
//	GetWindowThreadProcessId(hGameWindow, &processID);
//	if (processID == NULL)
//	{
//		std::cout << "Getting window PID failed. GetLastError = " << std::dec << GetLastError() << std::endl;
//		system("pause > nul");
//		return EXIT_FAILURE;
//	}
//	std::cout << "Using PID : " << processID << std::endl;
//
//	//Opening a process to get the permissions to RPM or WPM
//	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processID);
//	if (hProcess == NULL)
//	{
//		std::cout << "OpenProcess failed. GetLastError = " << std::dec << GetLastError() << std::endl;
//		system("pause > nul");
//		return EXIT_FAILURE;
//	}
//	std::cout << "OpenProcess succeeded. (got the permission)." << std::endl;
//
//
//	///////////////////////////
//
//	QWORD basePointer = GetProcessBaseAddress(processID);
//	basePointer += 0x01C8EB10;
//	QWORD healthOffsets[] = { 0x68, 0x0, 0x0};
//
//
//	char chat[578];
//	char newChat[578];	
//
//
//	// Set up a generic keyboard event.
//	ip.type = INPUT_KEYBOARD;
//	ip.ki.wScan = 0; // hardware scan code for key
//	ip.ki.time = 0;
//	ip.ki.dwExtraInfo = 0;
//
//
//
//
//	while (1) 
//	{
//		strcpy_s(newChat, getValueUsingPtrChain(basePointer, healthOffsets, 3, hProcess));
//		if (strcmp(chat, newChat) != 0) {
//			printChat(newChat);
//			strcpy_s(chat, getValueUsingPtrChain(basePointer, healthOffsets, 3, hProcess));
//			press();
//		}
//		Sleep(200);
//	}
//	
//
//	std::cin.ignore();
//
//
//}
