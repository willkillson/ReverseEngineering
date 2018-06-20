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
int getValueUsingPtrChain(QWORD bp, QWORD Offsets[], int depth, HANDLE hProcess) {

	bool fail_flag = false;

	QWORD readAddress = 0;
	QWORD basePointer = bp;

	LPVOID lpvBuffer = &readAddress;

	//std::cout << std::hex << std::uppercase << basePointer << '\t';
	ReadProcessMemory(hProcess, (LPCVOID)basePointer, lpvBuffer, sizeof(QWORD), NULL);
	basePointer = readAddress;
	//std::cout << std::hex << basePointer << std::endl;

	for (int i = 0; i < depth; i++) {
		basePointer += Offsets[i];

		//std::cout << std::hex << std::uppercase << basePointer << '\t';
		ReadProcessMemory(hProcess, (LPCVOID)basePointer, lpvBuffer, sizeof(QWORD), NULL);
		basePointer = readAddress;
		//std::cout << std::hex << basePointer << std::endl;

	}



	if (fail_flag)
		std::cout << "getValueUsingPtrChain: failed" << std::endl;

	return (int)readAddress;
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

	QWORD basePointer = 0x7FF7B43C5CB8;
	QWORD healthOffsets[] = { 0x58, 0xA0, 0x108, 0x38, 0x8, 0x18, 0x5C };

	//QWORD neSw = basePointer + 0x230;

	while (1) {
		int hp = getValueUsingPtrChain(basePointer, healthOffsets, 7, hProcess);
		int neSw = getFloatUsingAddress(basePointer + 0x230, hProcess);
		int nwSe = getFloatUsingAddress(basePointer + 0x234, hProcess);
		std::cout << std::dec << hp << std::endl;
		std::cout << std::dec << neSw << std::endl;
		std::cout << std::dec << nwSe << std::endl;
		Sleep(100);
	}

	std::cin.ignore();


}

