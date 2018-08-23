#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

#define timerW 100
#define timerH 20

class TimerT
{
	Time it;
	Clock gameTime;
	const size_t time = 15;
	size_t pastTime = 0;
	Image imageTimer;
	Texture textureTimer;
	Sprite spriteTimer;
	int x, y; // координаты таймера
	bool isStart = false;
public:
	TimerT()
	{
		imageTimer.loadFromFile("images/cardsset3.png");
		textureTimer.loadFromImage(imageTimer);
		spriteTimer.setTexture(textureTimer);
		spriteTimer.setTextureRect(IntRect(0, 0, timerW, timerH));
	}

	bool update(RenderWindow& window)
	{
		if (isStart == false)
		{
			gameTime.restart();
			isStart = true;
		}
		it = gameTime.getElapsedTime();
		if (pastTime < it.asSeconds())
		{
			if (pastTime >= time)
			{
				gameTime.restart();
				pastTime = 0;
				return true;
			}
			pastTime = it.asSeconds();
			//std::cout << "Time : " << pastTime << std::endl;
			int lookTimer = pastTime * timerW;
			spriteTimer.setTextureRect(IntRect(lookTimer, 0, timerW, timerH));
			load(window);
			return false;
		}
		return false;
	}

	void Start()
	{
		gameTime.restart();
		isStart = true;
	}

	void load(RenderWindow& window)
	{
		window.draw(spriteTimer);
	}

	~TimerT()
	{
	}
};

