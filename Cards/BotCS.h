#pragma once
#include "CardsSet.h"
#include "CardsBackCS.h"
#include "Kozir.h"

class BotCS : public CardsSet
{
	CardsBackCS* cardsBack = nullptr;
public:
	BotCS(int sizeBotCS = 6) : CardsSet(sizeBotCS)
	{

	}

	void initPos()
	{
		if (this->changed)
		{
			if (getSizeSet() != 0)
			{
				if (getSizeSet() != 0)
				{
					delete cardsBack;
					cardsBack = new CardsBackCS(getSizeSet());
					int oneStep = 708 / getSizeSet();
					for (size_t i = 0; i < getSizeSet(); i++)
					{
						cardsBack->getCard(i)->doInvisible();
						cardsBack->getCard(i)->SetPostition(276 + oneStep * i, 0);
					}
				}
			}
			this->changed = false;
		}
	}
	
	void drawCardsSet()
	{
		cardsBack->drawCardsSet();
	}

	Card* isContainsKozir(Kozir* kozir)
	{
		bool contains = false;
		for (size_t i = 0; i < getSizeSet(); i++)
		{
			if (getCard(i)->getRang() == kozir->getRang())
			{
				contains = true;
			}
		}
		contains = false;
		if (contains)
		{
			Card* lowerRang = nullptr;
			for (size_t i = 0; i < getSizeSet(); i++)
			{
				if (getCard(i)->getRang() == kozir->getRang())
				{
					if (lowerRang == nullptr)
					{
						lowerRang = new Card;
						*lowerRang = *getCard(i);
					}
					else if (lowerRang->getValue() > getCard(i)->getValue())
					{
						*lowerRang = *getCard(i);
					}
				}
			}
			return lowerRang;
		}
		else{
			return nullptr;
		}
	}

	~BotCS()
	{
		delete cardsBack;
	}
};

