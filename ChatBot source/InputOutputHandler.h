#include <iostream>
#include <Windows.h>
#include <WinUser.h>
#include "WindowHandler.h"
#include "Psapi.h" //https://docs.microsoft.com/en-us/windows/desktop/api/psapi/nf-psapi-enumprocessmodules
#include <sstream>

#pragma once
class InputOutputHandler {

public:
	InputOutputHandler() {
		this->mButton = 0;
		this->mInput.type = INPUT_KEYBOARD;
		this->mInput.ki.wScan = 0;
		this->mInput.ki.time = 0;
		this->mInput.ki.dwExtraInfo = 0;

	}
	void convertNewlineToNull(string pString);
	void transcode(string pString);



private:
	INPUT mInput;
	DWORD mButton;

	void press();


	


};



void InputOutputHandler::transcode(string pString) {
	auto itb = pString.begin();
	auto ite = pString.end();

	while (itb < ite) {
		//Uppercase Letters
		if (*itb >= '@' && *itb <= 'z') {
			mInput.ki.wVk = 0x10; //0x10 is shift
			mInput.ki.dwFlags = 0; // 0 for key press
			SendInput(1, &mInput, sizeof(INPUT));

			switch (*itb) {
			case 64://@ symbol
				mButton = 0x32; //2 key
				press();
				break;
			case 65:
				mButton = 0x41;
				press();
				break;
			case 66:
				mButton = 0x42;
				press();
				break;
			case 67:
				mButton = 0x43;
				press();
				break;
			case 68:
				mButton = 0x44;
				press();
				break;
			case 69:
				mButton = 0x45;
				press();
				break;
			case 70:
				mButton = 0x46;
				press();
				break;
			case 71:
				mButton = 0x47;
				press();
				break;
			case 72:
				mButton = 0x48;
				press();
				break;
			case 73:
				mButton = 0x49;
				press();
				break;
			case 74:
				mButton = 0x4A;
				press();
				break;
			case 75:
				mButton = 0x4B;
				press();
				break;
			case 76:
				mButton = 0x4C;
				press();
				break;
			case 77:
				mButton = 0x4D;
				press();
				break;
			case 78:
				mButton = 0x4E;
				press();
				break;
			case 79:
				mButton = 0x4F;
				press();
				break;
			case 80:
				mButton = 0x50;
				press();
				break;
			case 81:
				mButton = 0x51;
				press();
				break;
			case 82:
				mButton = 0x52;
				press();
				break;
			case 83:
				mButton = 0x53;
				press();
				break;
			case 84:
				mButton = 0x54;
				press();
				break;
			case 85:
				mButton = 0x55;
				press();
				break;
			case 86:
				mButton = 0x56;
				press();
				break;
			case 87:
				mButton = 0x57;
				press();
				break;
			case 88:
				mButton = 0x58;
				press();
				break;
			case 89:
				mButton = 0x59;
				press();
				break;
			case 90:
				mButton = 0x5A;
				press();
				break;
			}
			mInput.ki.wVk = 0x10; //0x10 is shift
			mInput.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
			SendInput(1, &mInput, sizeof(INPUT));
		}
		//Lowercase Letters
		if (*itb >= 'a' && *itb <= 'z') {
			mButton = VkKeyScanA(*itb);
			press();
		}
		//Numbers
		if (*itb >= '0' && *itb <= '9') {
			mButton = VkKeyScanA(*itb);
			press();
		}
		//Grammer Symbols
		{
			if (*itb == ' ') {
				mButton = VkKeyScanA(*itb);
				press();
			}
			if (*itb == '.') {
				mButton = 0xBE;
				press();
			}
			if (*itb == ',') {
				mButton = 0xBC;
				press();
			}

		}
		//Math
		{
			if (*itb == '+') {
				mButton = 0xBB;
				press();
			}
			if (*itb == '-') {
				mButton = 0xBD;
				press();
			}
		}

		//'\0' treated as enter key
		if (*itb == '\n') {
			mButton = 0x0D;
			press();
		}




		itb++;

	}
}

void InputOutputHandler::press() {
	mInput.ki.wVk = mButton;
	mInput.ki.dwFlags = 0; // 0 for key press
	SendInput(1, &mInput, sizeof(INPUT));

	mInput.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
	SendInput(1, &mInput, sizeof(INPUT));
}