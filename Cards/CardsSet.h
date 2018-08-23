#pragma once
#include "Header.h"
#include "Card.h"

using namespace std;

class CardsSet// ����� ������ ����, ������ �������� ����� ������ ������ ���� ������, ��� ���������� �������������
{
private:
	unique_ptr<Card[]> cardsSet = nullptr;//����� ����
	size_t sizeSet = 0;//������ ������
public:
	bool changed = true; //����, ����������� �� ��������� ������, ���� ��� ������� ����������������� ������������� ���� ������
	CardsSet(int sizeSet)
	{
		setSizeSet(sizeSet);
		if (sizeSet > 0)
		{
			cardsSet.reset(new Card[this->getSizeSet()]);
		}
		else{
			cardsSet.reset(nullptr);
		}
	}

	size_t getSizeSet()
	{
		return this->sizeSet;
	}
	unique_ptr<Card[]>& getCardsSet()//������ ������ �� ����� ����
	{
		return this->cardsSet;
	}
	Card* getCard(int card1) //������ ������ �� �����
	{
		return &this->cardsSet[card1];
	}
	void setSizeSet(size_t sizeSet)
	{
		this->sizeSet = sizeSet;
	}
	Card dropCard(int card1)//������� ����� �� ������ � ��������� ���
	{
		Card droppedCard; droppedCard = *this->getCard(card1);
		this->setSizeSet(this->getSizeSet() - 1);
		unique_ptr<Card[]> newCardsSet(new Card[this->getSizeSet()]);
		for (size_t i = 0, space = 0; i < this->getSizeSet(); i++, space++)
		{
			if (card1 != i)
			{
				newCardsSet[i] = this->cardsSet[space];
			}
			else{
				space++;
				newCardsSet[i] = this->cardsSet[space];
			}
		}
		this->cardsSet.reset(newCardsSet.release());
		changed = true;
		return droppedCard;
	}
	void addCard(Card card)// ��������� ����� � �����
	{
		unique_ptr<Card[]> newCardsSet(new Card[this->getSizeSet() + 1]);
		for (size_t i = 0; i < this->getSizeSet(); i++)
		{
			newCardsSet[i] = this->cardsSet[i];
		}
		newCardsSet[this->getSizeSet()] = card;
		this->cardsSet.reset(newCardsSet.release());
		this->setSizeSet(this->getSizeSet() + 1);
		changed = true;
	}
	void resetCardsSet()//������� ����� �� ���� � �������� �������
	{
		this->cardsSet.release();
		this->setSizeSet(0);
	}
	void drawCardsSet()// ������ ���� �����
	{
		if (this->getSizeSet() > 0)
		{
			for (size_t i = 0; i < this->getSizeSet(); i++)
			{
				this->cardsSet[i].draw();
			}
		}
	}

	~CardsSet()
	{
		cardsSet.reset(nullptr);
	}
};

