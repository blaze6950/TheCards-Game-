#pragma once
#define fontSize 60
#include <SFML/Graphics.hpp>
#include <string>
#include "Header.h"
class uWon
{
	bool isOn = false;
	sf::Image imageFon, imageOk;
	sf::Texture textureFon, textureOk;
	sf::Sprite spriteFon, spriteOk;
	sf::Font font;//шрифт 
	sf::Text text;//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	sf::RenderWindow* window; sf::Event* event;
public:
	uWon(sf::RenderWindow* window, sf::Event* event)
	{
		wchar_t word1[20](L"You WON!");
		imageFon.loadFromFile("images/fon.png"), imageOk.loadFromFile("images/ok.png");
		textureFon.loadFromImage(imageFon), textureOk.loadFromImage(imageOk);
		spriteFon.setTexture(textureFon), spriteOk.setTexture(textureOk);
		spriteOk.setTextureRect(sf::IntRect(0, 0, 256, 62));
		spriteOk.setPosition(510, 400);
		font.loadFromFile("SHOWG.TTF");//передаем нашему шрифту файл шрифта
		this->text.setCharacterSize(fontSize);
		this->text.setFont(font);
		this->text.setString(word1);
		//this->text.setColor(sf::Color::Black);
		this->text.setStyle(sf::Text::Bold);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый
		this->text.setPosition(500, 250);//задаем позицию текста, центр камеры
		this->window = window; this->event = event;
		isOn = true;
	}

	void load()
	{
		window->draw(spriteFon);
		window->draw(spriteOk);
		window->draw(text);//рисую этот текст
	}

	void MoveMouse()
	{
		int x = event->mouseMove.x;
		int y = event->mouseMove.y;
		if (x > 510 && x < 767 && y > 400 && y < 462)
		{
			spriteOk.setTextureRect(sf::IntRect(256, 0, 256, 62));
		}
		else{
			spriteOk.setTextureRect(sf::IntRect(0, 0, 256, 62));
		}
	}

	bool ButtonMouse()
	{
		int x = event->mouseMove.x;
		int y = event->mouseMove.y;
		if (x > 510 && x < 767 && y > 400 && y < 462)
		{
			return true;
		}
	}

	bool update()// главная функция, обрабатывающая ввод
	{
		if (isOn)
		{
			load();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				return true;
			}
			if (event->type == sf::Event::MouseMoved)
			{
				MoveMouse();
			}
			if (event->type == sf::Event::MouseButtonReleased)
			{
				return ButtonMouse();
			}
			return false;
		}
		else{
			return true;
		}

	}

	~uWon();
};

