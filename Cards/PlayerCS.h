#pragma once
#include "CardsSet.h"
#include "Kozir.h"


class PlayerCS : public CardsSet
{
public:
	PlayerCS(int sizePlayerCS = 6) : CardsSet(sizePlayerCS)
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
					getCard(i)->SetPostition(276 + oneStep * i, windowH - cardH);
				}
			}
			this->changed = false;
		}
	}

	void cardsRefresh(int x, int y)
	{
		int oneStep = 708 / getSizeSet();
		for (size_t i = 0; i < getSizeSet(); i++)
		{
			if (x >(276 + oneStep * i) && x < (276 + oneStep * (i + 1)) && y > windowH - cardH)
			{
				getCard(i)->SetPostition(276 + oneStep * i, windowH - cardH - 50);
			}
			else{
				getCard(i)->SetPostition(276 + oneStep * i, windowH - cardH);
			}
		}
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

	~PlayerCS();
};

