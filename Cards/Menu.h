#pragma once
#define SingleButtonX 390
#define SingleButtonY 275
#define SingleButtonWidth 529
#define SingleButtonHeight 112

#define OptionsButtonX 387
#define OptionsButtonY 405
#define OptionsButtonWidth 532
#define OptionsButtonHeight 112

#define ExitButtonX 385
#define ExitButtonY 540
#define ExitButtonWidth 535
#define ExitButtonHeight 112
#include <SFML/Graphics.hpp>
#include <iostream>
#include "GameProc.h"
#include "GameProcM.h"
#include "Options.h"
using namespace sf;

class Menu
{
	bool isOn = true;
	Image imageFon, imageSingle, imageMulty, imageOptions, imageExit;
	Texture textureFon, textureSingle, textureMulty, textureOptions, textureExit;
	Sprite spriteFon, spriteSingle, spriteMulty, spriteOptions, spriteExit;
	sf::RenderWindow* window; sf::Event* event;
	GameProc** game; GameProcM** mGame; Options** opt;
	bool redOrBlue;
public:
	Menu(sf::RenderWindow* window, sf::Event* event, GameProc** game, GameProcM** mGame, Options** opt){
		imageFon.loadFromFile("images/fon.png"), imageSingle.loadFromFile("images/singleplayer.png"), imageMulty.loadFromFile("images/multyplayer.png"), imageOptions.loadFromFile("images/options.png"), imageExit.loadFromFile("images/exit.png");
		textureFon.loadFromImage(imageFon), textureSingle.loadFromImage(imageSingle), textureMulty.loadFromImage(imageMulty), textureOptions.loadFromImage(imageOptions), textureExit.loadFromImage(imageExit);
		spriteFon.setTexture(textureFon), spriteSingle.setTexture(textureSingle), spriteMulty.setTexture(textureMulty), spriteOptions.setTexture(textureOptions), spriteExit.setTexture(textureExit);
		spriteSingle.setTextureRect(IntRect(0, 0, SingleButtonWidth, SingleButtonHeight)), spriteMulty.setTextureRect(IntRect(0, 0, 533, 112)), spriteOptions.setTextureRect(IntRect(0, 0, OptionsButtonWidth, OptionsButtonHeight)), spriteExit.setTextureRect(IntRect(0, 0, ExitButtonWidth, ExitButtonHeight));
		spriteSingle.setPosition(SingleButtonX, SingleButtonY), /*spriteMulty.setPosition(400, 470),*/ spriteOptions.setPosition(OptionsButtonX, OptionsButtonY), spriteExit.setPosition(ExitButtonX, ExitButtonY);
		this->window = window; this->event = event;
		this->game = game; this->mGame = mGame;
		this->opt = opt;
	}
	void load()
	{
		window->draw(spriteFon);
		window->draw(spriteSingle);
		//window->draw(spriteMulty);
		window->draw(spriteOptions);
		window->draw(spriteExit);
	}
	void update()
	{
		int x, y;
		if (isOn)
		{
			load();
			x = event->mouseMove.x;
			y = event->mouseMove.y;
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				x = event->mouseButton.x;
				y = event->mouseButton.y;
				if (x > SingleButtonX && x < SingleButtonX + SingleButtonWidth && y > SingleButtonY && y < SingleButtonY + SingleButtonHeight)
				{
					isOn = false;
					*game = new GameProc(window, event);
				}
				else if (x > OptionsButtonX && x < OptionsButtonX + OptionsButtonWidth && y > OptionsButtonY && y < OptionsButtonY + OptionsButtonHeight)
				{
					/*isOn = false;
					*mGame = new GameProcM;*/
					isOn = false;
					*opt = new Options(window, event, &redOrBlue);
				}
				else if (x > ExitButtonX && x < ExitButtonX + ExitButtonWidth && y > ExitButtonY && y < ExitButtonY + ExitButtonHeight)
				{
					isOn = false;
					window->clear();
					event->type = Event::Closed;
					window->close();
					return;
				}
				/*else if (x > 400 && x < 400 + 533 && y > 740 && y < 740 + 112)
				{
					isOn = false;
					window->clear();
					event->type = Event::Closed;
					window->close();
					return;
				}*/
				else{

				}
			}
			else
			{
				if (x > SingleButtonX && x < SingleButtonX + SingleButtonWidth && y > SingleButtonY && y < SingleButtonY + SingleButtonHeight)
				{
					spriteSingle.setTextureRect(IntRect(0, 0, 529, 112)), spriteMulty.setTextureRect(IntRect(0, 0, 533, 112)), spriteOptions.setTextureRect(IntRect(0, 0, 532, 112)), spriteExit.setTextureRect(IntRect(0, 0, 535, 112));
					spriteSingle.setTextureRect(IntRect(529, 0, 529, 112));
				}
				else if (x > OptionsButtonX && x < OptionsButtonX + OptionsButtonWidth && y > OptionsButtonY && y < OptionsButtonY + OptionsButtonHeight)
				{
					/*spriteSingle.setTextureRect(IntRect(0, 0, 529, 112)), spriteMulty.setTextureRect(IntRect(0, 0, 533, 112)), spriteOptions.setTextureRect(IntRect(0, 0, 532, 112)), spriteExit.setTextureRect(IntRect(0, 0, 535, 112));
					spriteMulty.setTextureRect(IntRect(533, 0, 533, 112));*/
					spriteSingle.setTextureRect(IntRect(0, 0, 529, 112)), spriteMulty.setTextureRect(IntRect(0, 0, 533, 112)), spriteOptions.setTextureRect(IntRect(0, 0, 532, 112)), spriteExit.setTextureRect(IntRect(0, 0, 535, 112));
					spriteOptions.setTextureRect(IntRect(532, 0, 532, 112));
				}
				else if (x > ExitButtonX && x < ExitButtonX + ExitButtonWidth && y > ExitButtonY && y < ExitButtonY + ExitButtonHeight)
				{
					/*spriteSingle.setTextureRect(IntRect(0, 0, 529, 112)), spriteMulty.setTextureRect(IntRect(0, 0, 533, 112)), spriteOptions.setTextureRect(IntRect(0, 0, 532, 112)), spriteExit.setTextureRect(IntRect(0, 0, 535, 112));
					spriteOptions.setTextureRect(IntRect(532, 0, 532, 112));*/
					spriteSingle.setTextureRect(IntRect(0, 0, 529, 112)), spriteMulty.setTextureRect(IntRect(0, 0, 533, 112)), spriteOptions.setTextureRect(IntRect(0, 0, 532, 112)), spriteExit.setTextureRect(IntRect(0, 0, 535, 112));
					spriteExit.setTextureRect(IntRect(535, 0, 535, 112));
				}
				/*else if (x > 400 && x < 400 + 533 && y > 740 && y < 740 + 112)
				{
					spriteSingle.setTextureRect(IntRect(0, 0, 529, 112)), spriteMulty.setTextureRect(IntRect(0, 0, 533, 112)), spriteOptions.setTextureRect(IntRect(0, 0, 532, 112)), spriteExit.setTextureRect(IntRect(0, 0, 535, 112));
					spriteExit.setTextureRect(IntRect(535, 0, 535, 112));
				}*/
				else{
					spriteSingle.setTextureRect(IntRect(0, 0, 529, 112)), spriteMulty.setTextureRect(IntRect(0, 0, 533, 112)), spriteOptions.setTextureRect(IntRect(0, 0, 532, 112)), spriteExit.setTextureRect(IntRect(0, 0, 535, 112));
				}
			}
		}
	}
	void Turn(bool position)
	{
		isOn = position;
		if (position)
		{
			delete *game;
			delete *mGame;
			delete *opt;
			*opt = nullptr;
			*mGame = nullptr;
			*game = nullptr;
		}
	}
	~Menu();
};