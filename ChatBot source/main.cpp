#include <iostream>
#include <Windows.h>
#include <WinUser.h>
#include "WindowHandler.h"
#include "Psapi.h" //https://docs.microsoft.com/en-us/windows/desktop/api/psapi/nf-psapi-enumprocessmodules
#include <sstream>

void press(INPUT ip, DWORD button) {

	ip.ki.wVk = button;
	ip.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &ip, sizeof(INPUT));
}
void transcode(string sInput, INPUT ip)
{

	auto itb = sInput.begin();
	auto ite = sInput.end();

	DWORD button;
	while (itb < ite) {
		//Uppercase Letters
		if (*itb >= '@' && *itb <= 'z') {
			ip.ki.wVk = 0x10; //0x10 is shift
			ip.ki.dwFlags = 0; // 0 for key press
			SendInput(1, &ip, sizeof(INPUT));

			switch (*itb) {
				case 64://@ symbol
					button = 0x32; //2 key
					press(ip, button);
					break;
				case 65:
					button = 0x41;
					press(ip, button);
					break;
				case 66:
					button = 0x42;
					press(ip, button);
					break;
				case 67:
					button = 0x43;
					press(ip, button);
					break;
				case 68:
					button = 0x44;
					press(ip, button);
					break;
				case 69:
					button = 0x45;
					press(ip, button);
					break;
				case 70:
					button = 0x46;
					press(ip, button);
					break;
				case 71:
					button = 0x47;
					press(ip, button);
					break;
				case 72:
					button = 0x48;
					press(ip, button);
					break;
				case 73:
					button = 0x49;
					press(ip, button);
					break;
				case 74:
					button = 0x4A;
					press(ip, button);
					break;
				case 75:
					button = 0x4B;
					press(ip, button);
					break;
				case 76:
					button = 0x4C;
					press(ip, button);
					break;
				case 77:
					button = 0x4D;
					press(ip, button);
					break;
				case 78:
					button = 0x4E;
					press(ip, button);
					break;
				case 79:
					button = 0x4F;
					press(ip, button);
					break;
				case 80:
					button = 0x50;
					press(ip, button);
					break;
				case 81:
					button = 0x51;
					press(ip, button);
					break;
				case 82:
					button = 0x52;
					press(ip, button);
					break;
				case 83:
					button = 0x53;
					press(ip, button);
					break;
				case 84:
					button = 0x54;
					press(ip, button);
					break;
				case 85:
					button = 0x55;
					press(ip, button);
					break;
				case 86:
					button = 0x56;
					press(ip, button);
					break;
				case 87:
					button = 0x57;
					press(ip, button);
					break;
				case 88:
					button = 0x58;
					press(ip, button);
					break;
				case 89:
					button = 0x59;
					press(ip, button);
					break;
				case 90:
					button = 0x5A;
					press(ip, button);
					break;
			}
			ip.ki.wVk = 0x10; //0x10 is shift
			ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
			SendInput(1, &ip, sizeof(INPUT));
		}	 
		//Lowercase Letters
		if (*itb >= 'a' && *itb <= 'z') {
			button = VkKeyScanA(*itb);
			press(ip, button);
		}
		//Numbers
		if (*itb >= '0' && *itb <= '9') {
			button = VkKeyScanA(*itb);
			press(ip, button);
		}
		//Grammer Symbols
		{
			if (*itb == ' ') {
				button = VkKeyScanA(*itb);
				press(ip, button);
			}
			if (*itb == '.') {
				button = 0xBE;
				press(ip, button);
			}
			if (*itb == ',') {
				button = 0xBC;
				press(ip, button);
			}

		}
		//Math
		{
			if (*itb == '+') {
				button = 0xBB;
				press(ip, button);
			}
			if (*itb == '-') {
				button = 0xBD;
				press(ip, button);
			}
		}

		//'\0' treated as enter key
		if (*itb == '\0') {
			button = 0x0D;
			press(ip, button);
		}


		

		itb++;

	}

}

int main() 
{

	WindowHandler game("Path of Exile");
	game.debug = true;
	game.readData();

	INPUT ip;
	// Set up a generic keyboard event.
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;



	int delay = 500;
	while (1) {
		transcode("this is the song that nevers.", ip);
		press(ip, 0x0D);
		Sleep(delay);
		transcode("It goes on and on my friends.", ip);
		press(ip, 0x0D);
		Sleep(delay);
		transcode("Some people, started singing it", ip);
		press(ip, 0x0D);
		Sleep(delay);
		transcode("not knowing what it was.", ip);
		press(ip, 0x0D);
		Sleep(delay);
		transcode("They will continue singing it", ip);
		press(ip, 0x0D);
		Sleep(delay);
		transcode("forever just because", ip);
		press(ip, 0x0D);
		Sleep(delay);

	}


}