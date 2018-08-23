#pragma once
#define fontSize 40
#include <SFML/Graphics.hpp>
#include <string>
#include "Header.h"

class NumOfColoda
{
	sf::Font font;//шрифт 
	sf::Text text;//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	sf::RenderWindow* window; sf::Event* event;
public:
	NumOfColoda(sf::RenderWindow* window, sf::Event* event)
	{
		this->window = window; this->event = event;
		font.loadFromFile("SHOWG.TTF");//передаем нашему шрифту файл шрифта
		this->text.setCharacterSize(fontSize);
		this->text.setFont(font);
		char str[100];
		sprintf_s(str, "%d", 39);
		this->text.setString(str);
		//this->text.setColor(sf::Color::Black);
		this->text.setStyle(sf::Text::Regular);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый
		this->text.setPosition(50, 256);//задаем позицию текста, центр камеры

	}

	void draw(int size)
	{
		char str[100];
		sprintf_s(str, "%d", size);
		this->text.setString(str);
		window->draw(text);
	}

	~NumOfColoda();
};

