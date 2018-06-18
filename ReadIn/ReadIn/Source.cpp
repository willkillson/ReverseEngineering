#include <iostream>
#include <Windows.h>

int main() {

	int intRead = 0;
	HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, false, 13604);// https://msdn.microsoft.com/en-us/library/windows/desktop/ms684320(v=vs.85).aspx

	if (handle == NULL) {
		std::cout << "OpenProcess failed. Error code : " << GetLastError() << std::endl;
		return 0;
	}

	LPCVOID lpcvBasePointer = (LPCVOID)0x00EFFB48;//LPCVOID is Long Pointer Const void
	LPVOID lpvBufferPointer = &intRead;//LPVOID is Long Pointer Void


	if (ReadProcessMemory(handle, lpcvBasePointer, lpvBufferPointer,sizeof(int),NULL) == NULL) {//https://msdn.microsoft.com/en-us/library/windows/desktop/ms680553(v=vs.85).aspx
		std::cout << "ReadProcessMemory failed. Error code : " << GetLastError() << std::endl;
		return 0;
	}

	std::cout << "intRead = " << intRead << std::endl;


}