// SteamNicknameChanger.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <Windows.h>
#include "steam/steam_api.h"
#include "SteamNicknameChanger.h"
//Tekken 7 steam appID 389730

	//figure out how I want the user to interact with my executable before I start
	// 	   	// Ask user if they want to change username >> main 
	//if yes, replace username with changed username >> new function, text file updated with new username
	// Ask user if they want to boot up tekken / change nickname
	// Can I add GUI? Like Wlauncher? provide Tekken nickname change, interface for Overlay etc.
	// If user says Yes
	// Boot up Tekken >> main 
	// Check a text file >> main 
	//search if Overlay is running. If yes, add [overlay] to changed username >> same new function
	//keep exe running, listening for event api shuts down >> function 2
	//if API shuts down, revert nickname back and exit exe. >>destructor?

int main()
{
	SteamNicknameChanger snc;
	std::cout << "Welcome to t7Launcher!\nBoot up Tekken (s)\nChange Nickname (c)\nExit launcher (e)\n";
	std::string input;
	//bool bFocusedWindow = GetConsoleWindow() == GetForegroundWindow();
	bool bTekkenOn = true;

	//right now I need user to exit out of exe gracefully (using ESC key) or else we can't change the nickname back.
	//actually, have it running to detect if tekken is on or not - default is true but when tekken is off (through steamAPI callback?), change it to false and exit loop
	//if I figure out how to intercept Tekken calling to display user's nickname on steam, I can use it that way and 
	while (bTekkenOn)
	{
		std::cin >> input;
			if (input == "s" | input == "S")
			{
				std::cin.ignore();
				//below should be handled by constructor later
				if (SteamAPI_RestartAppIfNecessary(snc.TEKKENID)) // Replace with your App ID
				{
					std::cout << "Booting up Tekken for you\n";
					//in here, I think we need to listen for tekken shutting down
				}
				else if (!SteamAPI_Init())
				{
					printf("Fatal Error - Steam must be running to play this game (SteamAPI_Init() failed).\n");
					bTekkenOn = false;
				}
				//make it handled by constructor
			}
			else if (input == "c" | input == "C")
			{
				std::cout << "You pressed C\n";
				std::cin.ignore();
				//update file TempNickname- could i do it as xml? or just txt file
			}
			else if (input == "e" | input == "E")
			{
				std::cin.ignore();
				std::cout << "Exit loop\n";
				bTekkenOn = false;
				//call destructor here
			}
		
	}
	std::cout << "Exiting t7Launcher\n";
	SteamAPI_Shutdown();
	return 1;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
