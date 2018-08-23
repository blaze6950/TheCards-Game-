#pragma once
#include "CardsSet.h"

class TableBeatingCS : public CardsSet
{
	int pos[6];
public:
	TableBeatingCS(int sizeTableBeatingCS) : CardsSet(sizeTableBeatingCS)
	{
		for (size_t i = 0; i < 6; i++)
		{
			pos[i] = -1;
		}
	}

	void initPos(int sizeTableTossCS, bool isUrCourse)
	{
		if (getSizeSet() != 0 && isUrCourse == true)
		{
			int oneStep = 708 / sizeTableTossCS;
			for (size_t i = 0; i < getSizeSet(); i++)
			{
				getCard(i)->SetPostition(330 + oneStep * i, 310);
			}
		}
		else{
			if (sizeTableTossCS != 0)
			{
				int oneStep = 708 / sizeTableTossCS;
				for (size_t i = 0; i < getSizeSet(); i++)
				{
					for (size_t z = 0; z < sizeTableTossCS; z++)
					{
						if (pos[i] == z)
						{
							getCard(i)->SetPostition(330 + oneStep * pos[i], 310);
						}
					}
				}
			}
		}
	}

	void initPosArray(int z, int sizeTableTossCS)
	{
		if (sizeTableTossCS != 0)
		{
			pos[getSizeSet() - 1] = z;
		}
	}

	bool getElPos(int i)
	{
		for (size_t z = 0; z < this->getSizeSet(); z++)
		{
			if (pos[z] == i)
			{
				return false;
			}
		}
		return true;
	}

	void nullPos()
	{
		for (size_t i = 0; i < 6; i++)
		{
			pos[i] = -1;
		}
	}

	~TableBeatingCS();
};

