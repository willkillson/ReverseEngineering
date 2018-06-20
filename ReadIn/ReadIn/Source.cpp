#include <iostream>
#include <Windows.h>


DWORD  findPointerAddress(int PointerLevel, HANDLE hProcess, DWORD  offsets[], DWORD  BaseAddress)
{
	DWORD  pointerAddress;
	DWORD  pointerTemp;

	for (int i = 0; i < PointerLevel; i++)
	{
		if (i == 0)
			ReadProcessMemory(hProcess, (LPCVOID)BaseAddress, &pointerTemp, sizeof(pointerTemp), NULL);


		pointerAddress = pointerTemp + offsets[i];
		std::cout << "Ptr - " << i << " " << pointerAddress << std::endl;
		ReadProcessMemory(hProcess, (LPCVOID)pointerAddress, &pointerTemp, sizeof(pointerTemp), NULL);
	}
	return pointerAddress;
}


int main() {

		int pid = 0;
		uintptr_t addressToRead = 0x0;

		int intRead = 0;
		std::string CplusplusStringRead;
		CplusplusStringRead.reserve(128);
		char stringRead[128];
		int *ptr2intRead = NULL;
		int **ptr2ptrRead = NULL;
		int ***ptr2ptr2ptrRead = NULL;
		DWORD valueToRead = NULL;



	
			int answer = -1;//menu
			while (1) {
				std::cout << "What are we reading?" << std::endl << std::endl;
				std::cout << "0: Integer" << std::endl;
				std::cout << "1: c++ string" << std::endl;
				std::cout << "2: c_string" << std::endl;
				std::cout << "3: ptr2int" << std::endl;
				std::cout << "4: ptr2ptr" << std::endl;
				std::cout << "5: ptr2ptr2ptr" << std::endl;
				std::cout << "6: readPtrChain" << std::endl;
				std::cin >> answer;
				if ((answer <= 6) && (answer >= 0))
					break;
				std::cout << "Your answer is not recognized." << std::endl;
			}

			std::cout << "Enter a the PID of the application to open." << std::endl;
			std::cin >> pid;
			std::cout << "Enter an address to read." << std::endl;
			std::cin >> std::hex >> addressToRead;

			HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, false, pid);// https://msdn.microsoft.com/en-us/library/windows/desktop/ms684320(v=vs.85).aspx

			if (handle == NULL) {
				std::cout << "OpenProcess failed. Error code : " << GetLastError() << std::endl;
				return 0;
			}

			LPCVOID lpcvBasePointer = (LPCVOID)addressToRead;//LPCVOID is Long Pointer Const void

			LPVOID lpvInt = &intRead;//LPVOID is Long Pointer Void
			LPVOID lpvCplusplusString = &CplusplusStringRead;//LPVOID is Long Pointer Void
			LPVOID lpvCstring = &stringRead;//LPVOID is Long Pointer Void
			LPVOID lpvPtr2int = &ptr2intRead;//LPVOID is Long Pointer Void
			LPVOID lpvPtr2ptr = &ptr2ptrRead;//LPVOID is Long Pointer Void
			LPVOID lpvPtr2ptr2ptr = &ptr2ptr2ptrRead;//LPVOID is Long Pointer Void


			switch (answer) {

			case 0:
				if (ReadProcessMemory(handle, lpcvBasePointer, lpvInt, (sizeof(int)), NULL) == NULL) {//https://msdn.microsoft.com/en-us/library/windows/desktop/ms680553(v=vs.85).aspx
					std::cout << "ReadProcessMemory failed. Error code : " << GetLastError() << std::endl;
					CloseHandle(handle);
					return 0;
				}
				std::cout << "intRead = " << intRead << std::endl;
				break;
			case 1:
				if (ReadProcessMemory(handle, lpcvBasePointer, lpvCplusplusString, sizeof(std::string)*128, NULL) == NULL) {//https://msdn.microsoft.com/en-us/library/windows/desktop/ms680553(v=vs.85).aspx
					std::cout << "ReadProcessMemory failed. Error code : " << GetLastError() << std::endl;
					CloseHandle(handle);
					return 0;
				}
				std::cout << "CplusplusString = " << &CplusplusStringRead << std::endl;
				break;
			case 2:
				if (ReadProcessMemory(handle, lpcvBasePointer, lpvCstring, (sizeof(char)*128), NULL) == NULL) {//https://msdn.microsoft.com/en-us/library/windows/desktop/ms680553(v=vs.85).aspx
					std::cout << "ReadProcessMemory failed. Error code : " << GetLastError() << std::endl;
					CloseHandle(handle);
					return 0;
				}
				std::cout << "stringRead = " << stringRead << std::endl;
				break;
			case 3:
				if (ReadProcessMemory(handle, lpcvBasePointer, lpvPtr2int, 4, NULL) == NULL) {//https://msdn.microsoft.com/en-us/library/windows/desktop/ms680553(v=vs.85).aspx
					std::cout << "ReadProcessMemory failed. Error code : " << GetLastError() << std::endl;
					CloseHandle(handle);
					return 0;
				}
				std::cout << "ptr2intRead = " << ptr2intRead << std::endl;
				break;
			case 4:
				if (ReadProcessMemory(handle, lpcvBasePointer, lpvPtr2ptr, 4, NULL) == NULL) {//https://msdn.microsoft.com/en-us/library/windows/desktop/ms680553(v=vs.85).aspx
					std::cout << "ReadProcessMemory failed. Error code : " << GetLastError() << std::endl;
					CloseHandle(handle);
					return 0;
				}
				std::cout << "ptr2ptrRead = " << ptr2ptrRead << std::endl;
				break;
			case 5:
				if (ReadProcessMemory(handle, lpcvBasePointer, lpvPtr2ptr2ptr, 4, NULL) == NULL) {//https://msdn.microsoft.com/en-us/library/windows/desktop/ms680553(v=vs.85).aspx
					std::cout << "ReadProcessMemory failed. Error code : " << GetLastError() << std::endl;
					CloseHandle(handle);
					return 0;
				}
				std::cout << "ptr2ptr2ptrRead = " << ptr2ptr2ptrRead << std::endl;
				break;
			case 6:
				DWORD  healthOffsets[] = { 0x58,0xA0, 0x108,0x38,0x8,0x18,0x5C };
				valueToRead = findPointerAddress(7, handle, healthOffsets, addressToRead);
				std::cout << "ValueOfChain = " << *&valueToRead << std::endl;
				break;
			}
			CloseHandle(handle);

		
}