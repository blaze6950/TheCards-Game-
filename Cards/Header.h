#pragma once
#define cardW 98.5
#define cardH 143
#define cardSetW 1280
#define cardSetH 572
#define windowW 1366
#define windowH 688
#include <memory>
#include <SFML\Graphics.hpp>
#include <iostream>

//namespace SFMLbar // пространство имен, для объекта window и event
//{
//	using namespace sf;
//	class windowAndEvent
//	{
//	public:
//		RenderWindow window(VideoMode(windowW, windowH), "CARDS", Style::Resize);
//		static Event event;
//		windowAndEvent()
//		{
//			window
//		}
//		~windowAndEvent();
//	};
//	static windowAndEvent wAndE;
//}


enum Rang
{
	Trefa,
	Bubna,
	Chirva,
	Pika,
};

enum Value
{
	Two,
	Three,
	Four,
	Five,
	Six,
	Seven,
	Eight,
	Nine,
	Ten,
	J,
	Q,
	K,
	A,
};