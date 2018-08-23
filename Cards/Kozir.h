#pragma once
#include "Card.h"

class Kozir : public Card
{
public:
	Kozir()
	{
		SetRotation(90);
	}

	void initPos()
	{
		Card::SetPostition(cardH, 298);
	}

	Kozir& operator=(Card &nSet) //перегрузка оператора присваивания
	{
		//this->getSprite().setTextureRect(IntRect(nSet.getPositionW(), nSet.getPositionH(), cardW, cardH));
		this->setSprite(nSet.getSprite());
		this->setOX(nSet.getOX()), this->setOY(nSet.getOY());
		this->setRang(nSet.getRang()), this->setValue(nSet.getValue());
		this->setPositionH(nSet.getPositionH()); this->setPositionW(nSet.getPositionW());
		this->SetRotation(90);
		return *this;
	}

	~Kozir();
};

