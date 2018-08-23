#pragma once
#include "PlayerCS.h"
#include "Card.h"

class ClickedCard : public Card
{
	Card* clickedCard = nullptr;
public:
	ClickedCard();

	void cardsRefresh(int x, int y, bool clc, PlayerCS& player)
	{
		int oneStep = 708 / player.getSizeSet();
		if (clc)
		{
			if (clickedCard == nullptr)
			{
				for (size_t i = 0; i < player.getSizeSet(); i++)
				{
					if (x >(276 + oneStep * i) && x < (276 + oneStep * (i + 1)) && y > 747)
					{
						clickedCard = player.getCard(i);
						break;
					}
				}
			}
			else{
				clickedCard->SetPostition(x, y);
			}
		}
		else{
			clickedCard->~Card();
		}
	}

	ClickedCard& operator=(Card &nSet) //перегрузка оператора присваивания
	{
		//this->getSprite().setTextureRect(IntRect(nSet.getPositionW(), nSet.getPositionH(), cardW, cardH));
		this->setSprite(nSet.getSprite());
		this->setOX(nSet.getOX()), this->setOY(nSet.getOY());
		this->setRang(nSet.getRang()), this->setValue(nSet.getValue());
		this->setPositionH(nSet.getPositionH()); this->setPositionW(nSet.getPositionW());

		return *this;
	}

	~ClickedCard();
};

