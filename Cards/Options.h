#pragma once
#include "Header.h"
#include <io.h>
#define fontSize 40

using namespace sf;

class Options
{
	Image imageFon, imageVertSync, imageBackCard1, imageBackCard2;
	Texture textureFon, textureVertSync, textureBackCard1, textureBackCard2;
	Sprite spriteFon, spriteVertSync, spriteBackCard1, spriteBackCard2;
	Font font;//шрифт 
	Text VertSync, BackCard1, BackCard2;//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	RenderWindow* window; sf::Event* event;
	bool* redOrBlue;
	bool isOn = true;
	static bool VSync;
	static bool redOrBlue1;
	bool cs2 = false, cs3 = false, cs4 = false;
	bool stop = false; // флаг, залупный, чтобы останавливать нажатие кнопки take
public:
	Options(sf::RenderWindow* window, sf::Event* event, bool* redOrBlue)
	{
		this->window = window; this->event = event;
		this->redOrBlue = redOrBlue;
		imageFon.loadFromFile("images/fon.png"), imageVertSync.loadFromFile("images/butRub.png"), imageBackCard1.loadFromFile("images/butDot1.png"), imageBackCard2.loadFromFile("images/butDot2.png");
		textureFon.loadFromImage(imageFon), textureVertSync.loadFromImage(imageVertSync), textureBackCard1.loadFromImage(imageBackCard1), textureBackCard2.loadFromImage(imageBackCard2);
		spriteFon.setTexture(textureFon), spriteVertSync.setTexture(textureVertSync), spriteBackCard1.setTexture(textureBackCard1), spriteBackCard2.setTexture(textureBackCard2);
		font.loadFromFile("SHOWG.TTF");//передаем нашему шрифту файл шрифта
		this->VertSync.setCharacterSize(fontSize), this->BackCard1.setCharacterSize(fontSize), this->BackCard2.setCharacterSize(fontSize);
		this->VertSync.setFont(font), this->BackCard1.setFont(font), this->BackCard2.setFont(font);
		this->VertSync.setString("V-Sync : "), this->BackCard1.setString("Red : "), this->BackCard2.setString("Blue : ");
		//this->text.setColor(sf::Color::Black);
		this->VertSync.setStyle(sf::Text::Regular), this->BackCard1.setStyle(sf::Text::Regular), this->BackCard2.setStyle(sf::Text::Regular);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый
		this->VertSync.setPosition(10, 348), this->BackCard1.setPosition(10, 398), this->BackCard2.setPosition(10, 448);
		spriteVertSync.setPosition(200, 348), spriteBackCard1.setPosition(200, 398), spriteBackCard2.setPosition(200, 448);
		if (!redOrBlue1)
		{
			spriteBackCard1.setTextureRect(IntRect(0, 0, 40, 40)), spriteBackCard2.setTextureRect(IntRect(40, 0, 40, 40));
		}
		else{
			spriteBackCard1.setTextureRect(IntRect(40, 0, 40, 40)), spriteBackCard2.setTextureRect(IntRect(0, 0, 40, 40));
		}
		if (VSync)
		{
			spriteVertSync.setTextureRect(IntRect(0, 0, 100, 40));
		}
		else{
			spriteVertSync.setTextureRect(IntRect(100, 0, 100, 40));
		}
	}


	void load()
	{
		window->draw(spriteFon);
		window->draw(spriteVertSync);
		window->draw(spriteBackCard1);
		window->draw(spriteBackCard2);
		window->draw(VertSync);
		window->draw(BackCard1);
		window->draw(BackCard2);
	}
	bool update()
	{
		int x, y;
		if (isOn)
		{
			load();
			y = event->mouseButton.y;
			x = event->mouseButton.x;
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				//KeyEscape();
				return true;
			}
			if (event->type == Event::MouseMoved)
			{
				stop = true;
			}
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				if (!stop)
				{
					return false;
				}
				stop = false;
				if (x > 200 && x < 300 && y > 348 && y < 388)
				{
					if (!VSync)
					{
						spriteVertSync.setTextureRect(IntRect(0, 0, 100, 40));
						VSync = true;
						window->setVerticalSyncEnabled(VSync);
					}
					else{
						spriteVertSync.setTextureRect(IntRect(100, 0, 100, 40));
						VSync = false;
						window->setVerticalSyncEnabled(VSync);
					}
					return false;

				}
				else if (x > 200 && x < 240 && y > 398 && y < 398 + 40)
				{
					if (!redOrBlue1)
					{
						spriteBackCard1.setTextureRect(IntRect(40, 0, 40, 40));
						spriteBackCard2.setTextureRect(IntRect(0, 0, 40, 40));
						if (_access("images/cardsset3.png", 0) != -1)
						{
							cs3 = true;
						}
						else{
							cs3 = false;
						}
						if (_access("images/cardsset2.png", 0) != -1)
						{
							cs2 = true;
						}
						else{
							cs2 = false;
						}
						if (_access("images/cardsset4.png", 0) != -1)
						{
							cs4 = true;
						}
						else{
							cs4 = false;
						}
						if (cs2)
						{
							if (cs3)
							{
								rename("images/cardsset2.png", "images/cardsset4.png");
								rename("images/cardsset4.png", "images/cardsset2.png");
							}
							else{
								rename("images/cardsset2.png", "images/cardsset3.png");
								rename("images/cardsset4.png", "images/cardsset2.png");
							}
						}
						else{
							rename("images/cardsset4.png", "images/cardsset2.png");
						}
						//strcpy_s(cardssset, "images/cardsset4.png");
						redOrBlue1 = true;
						*redOrBlue = true;
					}
					return false;
				}
				else if (x > 200 && x < 240 && y > 448 && y < 488)
				{
					if (redOrBlue1)
					{
						spriteBackCard2.setTextureRect(IntRect(40, 0, 40, 40));
						spriteBackCard1.setTextureRect(IntRect(0, 0, 40, 40));
						if (_access("images/cardsset3.png", 0) != -1)
						{
							cs3 = true;
						}
						else{
							cs3 = false;
						}
						if (_access("images/cardsset2.png", 0) != -1)
						{
							cs2 = true;
						}
						else{
							cs2 = false;
						}
						if (_access("images/cardsset4.png", 0) != -1)
						{
							cs4 = true;
						}
						else{
							cs4 = false;
						}
						if (cs2)
						{
							if (cs3)
							{
								rename("images/cardsset2.png", "images/cardsset4.png");
								rename("images/cardsset3.png", "images/cardsset2.png");
							}
							else{
								rename("images/cardsset2.png", "images/cardsset3.png");
								rename("images/cardsset3.png", "images/cardsset2.png");
							}
						}
						else{
							rename("images/cardsset3.png", "images/cardsset2.png");
						}
						//strcpy_s(cardssset, "images/cardsset3.png");
						redOrBlue1 = false;
						*redOrBlue = false;
					}
					return false;
				}
				else{
					return false;
				}
			}
			/*else
			{
				if (x > 405 && x < 405 + 529 && y > 335 && y < 335 + 112)
				{
					spriteSingle.setTextureRect(IntRect(0, 0, 529, 112)), spriteMulty.setTextureRect(IntRect(0, 0, 533, 112)), spriteOptions.setTextureRect(IntRect(0, 0, 532, 112)), spriteExit.setTextureRect(IntRect(0, 0, 535, 112));
					spriteSingle.setTextureRect(IntRect(529, 0, 529, 112));
				}
				else if (x > 400 && x < 400 + 533 && y > 470 && y < 470 + 112)
				{
					spriteSingle.setTextureRect(IntRect(0, 0, 529, 112)), spriteMulty.setTextureRect(IntRect(0, 0, 533, 112)), spriteOptions.setTextureRect(IntRect(0, 0, 532, 112)), spriteExit.setTextureRect(IntRect(0, 0, 535, 112));
					spriteMulty.setTextureRect(IntRect(533, 0, 533, 112));
				}
				else if (x > 400 && x < 400 + 533 && y > 605 && y < 605 + 112)
				{
					spriteSingle.setTextureRect(IntRect(0, 0, 529, 112)), spriteMulty.setTextureRect(IntRect(0, 0, 533, 112)), spriteOptions.setTextureRect(IntRect(0, 0, 532, 112)), spriteExit.setTextureRect(IntRect(0, 0, 535, 112));
					spriteOptions.setTextureRect(IntRect(532, 0, 532, 112));
				}
				else if (x > 400 && x < 400 + 533 && y > 740 && y < 740 + 112)
				{
					spriteSingle.setTextureRect(IntRect(0, 0, 529, 112)), spriteMulty.setTextureRect(IntRect(0, 0, 533, 112)), spriteOptions.setTextureRect(IntRect(0, 0, 532, 112)), spriteExit.setTextureRect(IntRect(0, 0, 535, 112));
					spriteExit.setTextureRect(IntRect(535, 0, 535, 112));
				}
				else{
					spriteSingle.setTextureRect(IntRect(0, 0, 529, 112)), spriteMulty.setTextureRect(IntRect(0, 0, 533, 112)), spriteOptions.setTextureRect(IntRect(0, 0, 532, 112)), spriteExit.setTextureRect(IntRect(0, 0, 535, 112));
				}
			}*/
		}
	}



	~Options();
};

