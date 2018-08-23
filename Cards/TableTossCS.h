#pragma once
#include "CardsSet.h"

class TableTossCS : public CardsSet
{
public:
	TableTossCS(int sizeTableTossCS = 0) : CardsSet(sizeTableTossCS)
	{

	}

	void initPos()
	{
		if (getSizeSet() != 0)
		{
			int oneStep = 708 / getSizeSet();
			for (size_t i = 0; i < getSizeSet(); i++)
			{
				getCard(i)->SetPostition(300 + oneStep * i, 298);
			}
		}
	}

	~TableTossCS();
};

