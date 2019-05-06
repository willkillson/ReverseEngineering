#include <iostream>
#include <Windows.h>
#include <vector>
#include "Psapi.h" //https://docs.microsoft.com/en-us/windows/desktop/api/psapi/nf-psapi-enumprocessmodules
#include <tlhelp32.h>

using namespace std;


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

HWND GetWindowHandle(string pTitle) 
{
	/*
		https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-findwindowa

		On success, this function returns the window handle.
		On failure, this function returns 0
	*/


	HWND newWindow = FindWindow(0, pTitle.c_str());

	if (newWindow == NULL) {
		cout << "GetWindowHandle - failure" << endl;
		return newWindow;
	}
	else
	{
		cout << "GetWindowHandle - success" << endl;
		return newWindow;
	}

}

DWORD GetProcessID(wstring pProcessName) {

	/*
		Code was modified based off of. 
		http://en.ciholas.fr/get-process-id-pid-from-process-name-string-c-windows-api/
	
	*/

	vector<DWORD> pids;
	wstring targetProcessName = pProcessName;
	HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); //all processes

	PROCESSENTRY32W entry; //current process
	entry.dwSize = sizeof entry;

	if (!Process32FirstW(snap, &entry)) { //start with the first in snapshot
		return 0;
	}

	do {
		if (std::wstring(entry.szExeFile) == targetProcessName) {
			pids.emplace_back(entry.th32ProcessID); //name matches; add to list
		}
	} while (Process32NextW(snap, &entry)); //keep going until end of snapshot

	for (int i(0); i < pids.size(); ++i) {
		std::cout << "GetProcessID - success" << std::endl;
		return pids[0];
	}
	std::cout << "GetProcessID - failure" << std::endl;
	return 0;

}

int main() {

	DWORD pid = GetProcessID(L"PathOfExile_x64.exe");
	HWND window = GetWindowHandle("Path of Exile");



	//DWORD_PTR baseAddress = GetProcessBaseAddress(pid);

	//uintptr_t addressToRead = 0x29492EAE840;
	//std::vector<DWORD> healthOffsets = { 0x188,0x100, 0x0 };

	//LPVOID mArray = NULL;
	//SIZE_T mArraySize = 600;



	//LPVOID valueToRead = NULL;

	//HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, false, pid);// https://msdn.microsoft.com/en-us/library/windows/desktop/ms684320(v=vs.85).aspx

	//if (handle == NULL) {
	//	std::cout << "OpenProcess failed. Error code : " << GetLastError() << std::endl;
	//	return 0;
	//}


	//CloseHandle(handle);

		
}