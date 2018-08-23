#pragma once
#include "Header.h"
using namespace sf;

class Card
{
private:
	static Image imageCard;
	static Texture textureCard;

	Sprite spriteCard;
	int x = 0, y = 0; // координаты карты
	Rang rang = Rang(0); // масть карты
	Value value = Value(0); // цифра или человек
	int positionW = 0; // позиция спрайта на тайлсете, в зависимости от карты
	int positionH = 0; // позиция спрайта на тайлсете, в зависимости от карты
	static int counter; // статическая переменная, считающая кол-во созданных карт, не может быть больше 52
	static sf::RenderWindow* window; static sf::Event* event;
public:
	Card()
	{
		if (counter == 0)
		{
			imageCard.loadFromFile("images/cardsset2.png");
			textureCard.loadFromImage(imageCard);
		}
		if (counter == 52)
		{
			spriteCard.setTexture(textureCard);
			spriteCard.setTextureRect(IntRect(positionW, positionH, cardW, cardH));
			return;
		}
		rang = Rang(counter / 13);
		value = Value(counter % 13);
		positionW = int(counter % 13) * cardW;
		positionH = int(counter / 13) * cardH;

		spriteCard.setTexture(textureCard);
		spriteCard.setTextureRect(IntRect(positionW, positionH, cardW, cardH));
		counter++;
	}

#pragma region Get
	Image getImage()const
	{
		return this->imageCard;
	}
	Texture getTexture()const
	{
		return this->textureCard;
	}
	Sprite getSprite()const
	{
		return this->spriteCard;
	}
	int getOX()const
	{
		return this->x;
	}
	int getOY()const
	{
		return this->y;
	}
	Rang getRang()const
	{
		return this->rang;
	}
	Value getValue()const
	{
		return this->value;
	}
	int getPositionW()const
	{
		return this->positionW;
	}
	int getPositionH()const
	{
		return this->positionH;
	}
	static int getCounter()
	{
		return counter;
	}
#pragma endregion геттеры  
#pragma region Set
	void setImage(Image imageCard)
	{
		this->imageCard = imageCard;
	}
	void setTexture(Texture textureCard)
	{
		this->textureCard = textureCard;
	}
	void setSprite(Sprite spriteCard)
	{
		this->spriteCard = spriteCard;
	}
	void setOX(int x)
	{
		this->x = x;
	}
	void setOY(int y)
	{
		this->y = y;
	}
	void setRang(Rang rang)
	{
		this->rang = rang;
	}
	void setValue(Value value)
	{
		this->value = value;
	}
	void setPositionW(int positionW)
	{
		this->positionW = positionW;
	}
	void setPositionH(int positionH)
	{
		this->positionH = positionH;
	}
	static void setCounter(int counter)
	{
		Card::counter = counter;
	}
#pragma endregion сеттеры

	bool isBetter(Card& card, Rang kozir) // проверка. побьет ли данная карта(this) передаваемую карту, rare - козырь
	{
		if (this->getRang() == card.getRang())
		{
			if (this->getValue() > card.getValue())
			{
				return true;
			}
			else{
				return false;
			}
		}
		else if (this->getRang() == kozir)
		{
			return true;
		}
		else{
			return false;
		}
	}
	void SetPostition(int Ox, int Oy)
	{
		this->setOX(Ox);
		this->setOY(Oy);
		this->spriteCard.setPosition(this->x, this->y);
	}
	void SetRotation(float degrees)
	{
		this->spriteCard.rotate(degrees);
	}
	void draw()
	{
		window->draw(this->spriteCard);
	}
	void doInvisible()// скрывает карту, рисую рубашку вместо карты
	{
		this->spriteCard.setTexture(textureCard);
		this->spriteCard.setTextureRect(IntRect(1280, 0, cardW, cardH));
	}

	Card(const Card& nSet)
	{
		//spriteCard.setTextureRect(IntRect(nSet.getPositionW(), nSet.getPositionH(), cardW, cardH));
		spriteCard = nSet.getSprite();
		this->setOX(nSet.getOX()), this->setOY(nSet.getOY());
		this->setRang(nSet.getRang()), this->setValue(nSet.getValue());
		this->setPositionH(nSet.getPositionH()); this->setPositionW(nSet.getPositionW());
	}
	Card& operator=(Card &nSet) //перегрузка оператора присваивания
	{
		//spriteCard.setTextureRect(IntRect(nSet.getPositionW(), nSet.getPositionH(), cardW, cardH));
		spriteCard = nSet.getSprite();
		this->setOX(nSet.getOX()), this->setOY(nSet.getOY());
		this->setRang(nSet.getRang()), this->setValue(nSet.getValue());
		this->setPositionH(nSet.getPositionH()); this->setPositionW(nSet.getPositionW());

		return *this;
	}
	friend bool operator==(const Card& fCard, const Card& sCard);

	static void setWANDE(sf::RenderWindow* window, sf::Event* event)
	{
		Card::window = window; Card::event = event;
	}

	~Card();
};

