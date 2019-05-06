#include <iostream>
#include <Windows.h>




//#define TARGET_X64
//
//#ifdef TARGET_X64
//typedef unsigned __int64 addr_ptr;
//#else
//typedef unsigned int addr_ptr;
//#endif



typedef uint64_t QWORD;
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

	//std::cout << std::hex << std::uppercase << basePointer << '\t';
	ReadProcessMemory(hProcess, (LPCVOID)basePointer, lpvBuffer, sizeof(QWORD), NULL);
	basePointer = readAddress;
	//std::cout << std::hex << basePointer << std::endl;

	for (int i = 0; i < depth-1; i++) {
		basePointer += Offsets[i];

		//std::cout << std::hex << std::uppercase <<'['<< basePointer <<" + " << Offsets[i]<<']' << '\t';
		ReadProcessMemory(hProcess, (LPCVOID)basePointer, lpvBuffer, sizeof(QWORD), NULL);
		basePointer = readAddress;
		//std::cout << std::hex << basePointer << std::endl;

	}

	char stringBuffer[578];
	LPVOID pStringBuffer = &stringBuffer;

	basePointer += Offsets[depth - 1];
	ReadProcessMemory(hProcess, (LPCVOID)basePointer, pStringBuffer, sizeof(char)* 578, NULL);

//	std::cout << stringBuffer;


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

int main() {





	LPCTSTR LGameWindow = "Path of Exile";
	HWND hGameWindow = FindWindow(NULL, LGameWindow);
	if (!hGameWindow) {
		std::cout << "Game not found. GetLastError = " << std::dec << GetLastError() << std::endl;
		return EXIT_FAILURE;
	}
	std::cout << "Game found" << std::endl;

	//Finding the processID of the game window
	DWORD  processID = 9716;
	GetWindowThreadProcessId(hGameWindow, &processID);
	if (processID == NULL)
	{
		std::cout << "Getting window PID failed. GetLastError = " << std::dec << GetLastError() << std::endl;
		system("pause > nul");
		return EXIT_FAILURE;
	}
	std::cout << "Using PID : " << processID << std::endl;

	//Opening a process to get the permissions to RPM or WPM
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processID);
	if (hProcess == NULL)
	{
		std::cout << "OpenProcess failed. GetLastError = " << std::dec << GetLastError() << std::endl;
		system("pause > nul");
		return EXIT_FAILURE;
	}
	std::cout << "OpenProcess succeeded. (got the permission)." << std::endl;


	///////////////////////////

	QWORD basePointer = 0x00007ff76b360000 + 0x01C880B0;
	QWORD healthOffsets[] = { 0x188, 0x108, 0x0, 0x0};


	char chat[578];
	char newChat[578];	

	while (1) 
	{
		strcpy_s(newChat, getValueUsingPtrChain(basePointer, healthOffsets, 4, hProcess));
		if (strcmp(chat, newChat) != 0) {
			std::cout << newChat;
			strcpy_s(chat, getValueUsingPtrChain(basePointer, healthOffsets, 4, hProcess));
		}
		Sleep(200);
	}
	

	std::cin.ignore();


}
