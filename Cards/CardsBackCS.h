#pragma once
#include "CardsSet.h"

class CardsBackCS : public CardsSet
{
public:
	CardsBackCS(int sizeBotCS) : CardsSet(sizeBotCS)
	{

	}

	void initPos()
	{
		if (this->changed)
		{
			if (getSizeSet() != 0)
			{
				int oneStep = 708 / getSizeSet();
				for (size_t i = 0; i < getSizeSet(); i++)
				{
					getCard(i)->SetPostition(276 + oneStep * i, 797);
				}
			}
			this->changed = false;
		}
	}
	void drawCardsSet()// рисуем весь набор
	{
		doInvisibleCS();
		CardsSet::drawCardsSet();
	}
	void doInvisibleCS()
	{
		if (this->getSizeSet() != 0)
		{
			for (size_t i = 0; i < this->getSizeSet(); i++)
			{
				getCard(i)->doInvisible();
			}
		}
	}

	~CardsBackCS();
};

