#include "Card.h"


Card::~Card()
{

}

int Card::counter = 0;
Image Card::imageCard;
Texture Card::textureCard;
sf::RenderWindow* Card::window;
sf::Event* Card::event;

bool operator == (const Card& fCard, const Card& sCard)
{
	if (fCard.getRang() == sCard.getRang() && fCard.getValue() == sCard.getValue())
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
