#include <iostream>
#include <Windows.h>
#include <WinUser.h>
#include "Psapi.h"
#include <sstream>

#include "WindowHandler.h"
#include "InputOutputHandler.h"
#include "kmw.h"

//https://docs.microsoft.com/en-us/windows/desktop/api/psapi/nf-psapi-enumprocessmodules

int main() 
{
	
	WindowHandler wh("Path of Exile");
	InputOutputHandler ioh;

	char newChat[WindowHandler::MAX_CHAT_SIZE];

	newChat[WindowHandler::MAX_CHAT_SIZE-1] = NULL;


	while (1) {
		wh.readData();	

		/*
			Kevin -
			Having an issue with reading from the buffer. Comparing wh.chat and newChat
			works, but sometimes we get a double message. I think unicode characters
			might be the issue. Taking a break to go for a run.

		*/
		
		
		if (!(kmw::compare(wh.chat, newChat))){
			cout << wh.chat << endl;
			strcpy_s(newChat, wh.chat);
			//cout << "Difference found - " << endl << endl;
			//cout << "*************wh.chat*************" << endl;
			//cout << wh.chat << endl;
			//cout << "*************newChat*************" << endl;
			//cout << newChat << endl;

		
			//ioh.transcode(wh.chat);
			//ioh.transcode("\n");
		}
	}

	//WindowHandler game("Path of Exile");
	//game.debug = true;
	//game.readData();




	//int delay = 3000;
	//while (1) {

	//	transcode("this is the song that nevers.", ip);
	//	press(ip, 0x0D);
	//	Sleep(delay);

	//	transcode("It goes on and on my friends.", ip);
	//	press(ip, 0x0D);
	//	Sleep(delay);

	//	transcode("Some people, started singing it", ip);
	//	press(ip, 0x0D);
	//	Sleep(delay);

	//	transcode("not knowing what it was.", ip);
	//	press(ip, 0x0D);
	//	Sleep(delay);

	//	transcode("They will continue singing it", ip);
	//	press(ip, 0x0D);
	//	Sleep(delay);

	//	transcode("forever just because", ip);
	//	press(ip, 0x0D);

	//	Sleep(delay);

	//}


}