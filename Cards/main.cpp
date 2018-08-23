#pragma once
#include "Header.h"
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(windowW, windowH), "CARDS", sf::Style::Resize);sf::Event* event = new sf::Event;
#include <iostream>
#include "Menu.h"
#include "GameProc.h"
#include "GameProcM.h"
#include "Options.h"
///#include "WinUser.h"
//#include "wincon.h"
//#include "Windows.h"

using namespace sf;

int main()
{	
	Image icon;
	if (!icon.loadFromFile("images/CARDSico3.png"))
	{
		return 1;
	}
	window->setIcon(29, 32, icon.getPixelsPtr());
	//ShowWindow(GetConsoleWindow(), SW_HIDE);
	Card::setWANDE(window, event);
	GameProc* singleGame = nullptr;
	GameProcM* multyGame = nullptr;
	Options* opt = nullptr;
	/*Clock clock;
	Clock gameTimeClock; */
	window->setVerticalSyncEnabled(true);
	float currentFrame = 0;
	Menu MainMenu(window, event, &singleGame, &multyGame, &opt);
	while (window->isOpen())
	{
		/*float time = clock.getElapsedTime().asMicroseconds();*/
		while (window->pollEvent(*event))
		{
			if (event->type == sf::Event::Closed)
				window->close();

			if (event->type == Event::MouseMoved)
			{

			}
		}

		if (singleGame == nullptr && multyGame == nullptr && opt == nullptr)
		{
			MainMenu.update();
		}
		if (singleGame != nullptr)
		{
			MainMenu.Turn(singleGame->update());
		}
		if (multyGame != nullptr)
		{
			if (singleGame == nullptr)
			{
				MainMenu.Turn(multyGame);
			}
		} 
		if (opt != nullptr)
		{
			if (singleGame == nullptr && multyGame == nullptr)
			{
				MainMenu.Turn(opt->update());
			}
		}
		window->display();
	}

	return 0;
}