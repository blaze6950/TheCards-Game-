#pragma once
#include "Header.h"
#include "BotCS.h"
#include "ClickedCard.h"
#include "ColodaCS.h"
#include "Kozir.h"
#include "PlayerCS.h"
#include "TableBeatingCS.h"
#include "TableTossCS.h"
#include "uLose.h"
#include "uWon.h"
#include "NumOfColoda.h" // кол-во карт в колоде
#include "TimerT.h"

class GameProc
{
private:
	//TimerT timer;
	ColodaCS coloda{ 52 }; BotCS bot{ 6 }; PlayerCS player{ 6 }; TableTossCS tableToss{ 0 }; TableBeatingCS tableBeating{ 0 }; Kozir kozir; Card* clickedCard = nullptr;
	unique_ptr<uLose> isLose = nullptr; unique_ptr<uWon> isWon = nullptr;
	String fon = "fon.png";
	Image imageFon, imagePass, imageTake;
	Texture textureFon, texturePass, textureTake;
	Sprite spriteFon, spritePass, spriteTake;
	bool isOn = true;
	bool isClick = false; //флаг, определяющий, был ли клик на карте, если да, то карта прилепляется к курсору
	bool isUrCourse = true; //флаг, показывающий чей ход
	bool isTake = false;//флаг, который указывает, когда бот или игрок нажали взять, это дает дополнительное время, чтобы подкинуть карт
	bool butTake = false; bool butPass = false;// флаги кнопок взять\пас
	bool stop = false; // флаг, залупный, чтобы останавливать нажатие кнопки take
	sf::RenderWindow* window; sf::Event* event;
	NumOfColoda* sizeColoda = nullptr;
public:
	GameProc(sf::RenderWindow* window, sf::Event* event)
	{
		/*for (size_t i = 0; i < 52; i++)
		{
		cout << coloda[i].getRang() << " = " << coloda[i].getValue() << endl;
		}*/
		imageFon.loadFromFile("images/" + fon), imagePass.loadFromFile("images/pass.png"), imageTake.loadFromFile("images/take.png");
		textureFon.loadFromImage(imageFon), texturePass.loadFromImage(imagePass), textureTake.loadFromImage(imageTake);
		spriteFon.setTexture(textureFon), spritePass.setTexture(texturePass), spriteTake.setTexture(textureTake);
		spritePass.setTextureRect(IntRect(0, 0, 256, 62)), spriteTake.setTextureRect(IntRect(0, 0, 256, 62));
		spritePass.setPosition(0, windowH - 62), spriteTake.setPosition(0, windowH - 62);
		this->window = window; this->event = event;
		isOn = true;
		sizeColoda = new NumOfColoda(window, event);
		distribution();
		initPos();
	}

	bool singleIsOn()
	{
		return isOn;
	}

	void distribution() // раздача карт
	{
		int card1 = 0, card2 = 0;
		srand(time(0));
		for (size_t i = 0; i < 6; i++)
		{
			card1 = rand() % coloda.getSizeSet(); card2 = rand() % coloda.getSizeSet();
			while (card1 == card2)
			{
				card1 = rand() % coloda.getSizeSet(); card2 = rand() % coloda.getSizeSet();
			}
			*player.getCard(i) = coloda.dropCard(card1);
			*bot.getCard(i) = coloda.dropCard(card2);
		}
		for (size_t i = 0; i < bot.getSizeSet(); i++)
		{
			std::cout << "№" << i << ". " << bot.getCard(i)->getRang() << " - " << bot.getCard(i)->getValue() << std::endl;
		}
		std::cout << "================================================================================\n";
		card1 = rand() % coloda.getSizeSet();//рандомный козырь
		kozir = coloda.dropCard(card1);
		whoFirstCourse();//определяем, кто первый ходит
	}

	void whoFirstCourse()
	{
		bool playerKozir = false;
		bool botKozir = false;
		Card* lowerRangP;
		Card* lowerRangB;
		lowerRangP = player.isContainsKozir(&kozir);
		lowerRangB = bot.isContainsKozir(&kozir);
		if (lowerRangP != nullptr)
		{
			playerKozir = true;
		}
		if (lowerRangB != nullptr)
		{
			botKozir = true;
		}
		if (playerKozir)
		{
			if (botKozir)
			{
				if (lowerRangB->getValue() > lowerRangP->getValue())
				{
					isUrCourse = true;
				}
				else{
					isUrCourse = false;
				}
			}
			else{
				isUrCourse = true;
			}
		}
		else if (botKozir)
		{
			isUrCourse = false;// ходит бот, т.к. у игрока нет козырей
		}
		else{
			isUrCourse = true;// по идее должен быть рандом, но мне лень, поэтому если нет козыря ни у кого, то ходит игрок
		}
	}

	void KeyEscape()
	{
		isOn = false;
		isLose.release();
		isWon.release();
		coloda.resetCardsSet();
		player.resetCardsSet();
		bot.resetCardsSet();
		tableToss.resetCardsSet();
		tableBeating.resetCardsSet();
		kozir.~Kozir();
		delete sizeColoda;
		Card::setCounter(0);
		//GameProc::~GameProc();
	}

	void initPos() // инициализирует положение каждой карты на руках
	{
		tableToss.initPos();
		tableBeating.initPos(tableToss.getSizeSet(), isUrCourse);
		player.initPos();
		bot.initPos();
		kozir.initPos();
	}

	void load()// рисует каждый элемент
	{
		initPos();
		window->clear();
		window->draw(spriteFon);
		tableToss.drawCardsSet();
		tableBeating.drawCardsSet();
		bot.drawCardsSet();
		player.drawCardsSet();
		kozir.draw();
		window->draw(spritePass);
		window->draw(spriteTake);
		sizeColoda->draw(coloda.getSizeSet());
		//window.display();
	}

	bool update()// главная функция, обрабатывающая ввод
	{
		if (isOn)
		{
			if (isLose != nullptr || isWon != nullptr)
			{
				if (isLose == nullptr)
				{
					if (isWon->update()){ KeyEscape(); }
				}
				else{
					if (isLose->update()){ KeyEscape(); }
				}
				return false;
			}
			load();
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				KeyEscape();
				return true;
			}
			if (event->type == Event::MouseMoved)
			{
				stop = true;
				MoveMouse();
			}
			if (event->type == Event::MouseButtonReleased)
			{
				if (stop)
				{
					stop = false;
					ButtonMouse();
				}
			}
			funcTreatment();
			/*if (timer.update(*window))
			{
				if (isUrCourse)
				{
					if (tableToss.getSizeSet() == 0)
					{
						isLose.reset(new uLose(window, event));
					}
					else{
						butPass = true;
					}
				}
				else{
					butTake = true;
					fromTableToBotOrPlayer();
				}
			}*/
			return false;
		}
		else{
			return true;
		}

	}

	void MoveMouse()
	{
		int x = event->mouseMove.x;
		int y = event->mouseMove.y;
		if (isClick)
		{
			cardsRefresh(x, y, true);
		}
		else if (x > 0 && x < 257 && y > windowH - 62 && y < windowH)
		{
			spritePass.setTextureRect(IntRect(256, 0, 256, 62));
			spriteTake.setTextureRect(IntRect(256, 0, 256, 62));
		}
		else if (x > 276 && x < 984 && y > windowH - cardH - 50 && y < windowH && !isClick)
		{
			cardsRefresh(x, y, false);
		}
		else if (!isClick){
			cardsRefresh(x, y, false);
		}
	}
	void ButtonMouse()
	{
		if (event->mouseButton.button == 0)
		{
			int x = event->mouseButton.x;
			int y = event->mouseButton.y;
			if (isClick)
			{
				if (x > 300 && x < 960 && y > 200 && y < windowH - 200)
				{
					tableFunc();
				}
				isClick = false;
			}
			else if (x > 0 && x < 257 && y > windowH - 62 && y < windowH)
			{
				buttonFuncClc();
			}
			else{
				if (x > 276 && x < 984 && y > windowH - cardH - 50 && y < windowH)
				{
					isClick = true;
					cardsRefresh(x, y, true);
				}
				else{
					isClick = false;
				}
			}

		}
	}

	void cardsRefresh(int x, int y, bool clc)
	{
		spritePass.setTextureRect(IntRect(0, 0, 256, 62));
		spriteTake.setTextureRect(IntRect(0, 0, 256, 62));
		if (player.getSizeSet() == 0)
		{
			return;
		}
		int oneStep = 708 / player.getSizeSet();
		if (clc)
		{
			if (clickedCard == nullptr)
			{
				for (size_t i = 0; i < player.getSizeSet(); i++)
				{
					if (x >(276 + oneStep * i) && x < (276 + oneStep * (i + 1)) && y > windowH - cardH - 50)
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
			clickedCard = nullptr;
			player.cardsRefresh(x, y);
		}
	}

	void funcTreatment()//функция, которая находится в ф-ции апдейт и следит за кол-вом карт, за кнопками(пас, взять), за раздачей карт
	{
		buttonFunc();
		isBotCourse();
		retreat();
		if (coloda.getSizeSet() == 0)
		{
			if (bot.getSizeSet() == 0)
			{
				std::cout << "U LOSE!\n";
				isLose.reset(new uLose(window, event));
			}
			else if (player.getSizeSet() == 0)
			{
				std::cout << "U WON!\n";
				isWon.reset(new uWon(window, event));
			}
		}
	}
	void buttonFunc()
	{
		if (isUrCourse)
		{
			if (tableToss.getSizeSet() > 0)
			{
				spriteTake.setPosition(-256, 698);
				spritePass.setPosition(0, windowH - 62);
			}
			else{
				spriteTake.setPosition(-256, 698);
				spritePass.setPosition(-256, 698);
			}
		}
		else{
			if (tableToss.getSizeSet() > 0)
			{
				spritePass.setPosition(-256, 698);
				spriteTake.setPosition(0, windowH - 62);
			}
			else{
				spriteTake.setPosition(-256, 698);
				spritePass.setPosition(-256, 698);
			}
		}
	}
	void buttonFuncClc()
	{
		if (isUrCourse)
		{
			if (tableToss.getSizeSet() > 0)
			{
				butPass = true;
			}
		}
		else{
			if (tableToss.getSizeSet() > 0)
			{
				butTake = true;
				fromTableToBotOrPlayer();
			}
		}
	}

	void retreat()
	{
		if (tableBeating.getSizeSet() == tableToss.getSizeSet() && butPass)
		{
			butPass = false;
			tableBeating.resetCardsSet();
			tableBeating.nullPos();
			tableToss.resetCardsSet();
			refreshDistribution();
			//timer.Start();
		}
	}

	void isBotCourse()//определяет этот ход бота или нет, вызывается в йункции апдейтtable
	{
		if (!isUrCourse)
		{
			if (tableToss.getSizeSet() != 6)
			{
				botCourse();
			}
			else{
				butPass = true;
				retreat();
			}
		}
		else if (tableToss.getSizeSet() > 0 && isUrCourse){
			if (tableBeating.getSizeSet() != 6)
			{
				if (tableToss.getSizeSet() != tableBeating.getSizeSet())
				{
					defenseBot();
				}
				else{
					retreat();
					if (tableToss.getSizeSet() == 0)
					{
						isUrCourse = false;
					}
				}
			}
			else{
				butPass = true;
				retreat();
			}
		}
		else{
			return;
		}
	}

	void botCourse()//ф-ция, выбирающая карты, которыми будет ходить бот
	{
		/*for (size_t i = 0; i < bot.getSizeSet(); i++)
		{
			std::cout << "№" << i << ". " << (Rang)bot.getCard(i)->getRang() << " - " << (Value)bot.getCard(i)->getValue() << std::endl;
		}
		cout << "===========================================\n";*/
		int tes = 0;
		if (tableToss.getSizeSet() == 0)
		{
			unique_ptr<Card> lowerRang(new Card);
			*lowerRang = *bot.getCard(0);
			for (size_t i = 0; i < bot.getSizeSet(); i++)
			{
				if (lowerRang->getValue() > bot.getCard(i)->getValue())
				{
					if (bot.getCard(i)->getRang() != kozir.getRang())
					{
						*lowerRang = *bot.getCard(i);
					}
				}
			}
			for (size_t i = 0; i < bot.getSizeSet(); i++)
			{
				if (*lowerRang == *bot.getCard(i))
				{
					fromBotToTableToss(&bot.dropCard(i));
				}
			}
		}
		else if (tableToss.getSizeSet() > 0){ // блок кода, когда на столе уже есть карты
			for (size_t i = 0; i < tableToss.getSizeSet(); i++)
			{
				for (size_t z = 0; z < bot.getSizeSet(); z++)
				{
					if (bot.getCard(z)->getValue() == tableToss.getCard(i)->getValue())
					{
						tes += fromBotToTableToss(&bot.dropCard(z));
					}
				}
			}
			for (size_t i = 0; i < tableBeating.getSizeSet(); i++)
			{
				for (size_t z = 0; z < bot.getSizeSet(); z++)
				{
					if (bot.getCard(z)->getValue() == tableBeating.getCard(i)->getValue())
					{
						tes += fromBotToTableToss(&bot.dropCard(z));
					}
				}
			}
			if (tes == 0)
			{
				butPass = true;
				if (tableBeating.getSizeSet() == tableToss.getSizeSet())
				{
					isUrCourse = true;
				}
			}
			retreat();
		}
	}
	void defenseBot()//ф-ция, отвечающая за отбивание карт ботом
	{
		if (!isTake)
		{
			bool bito = false;
			for (size_t i = tableBeating.getSizeSet(); i < tableToss.getSizeSet(); i++)
			{
				for (size_t z = 0; z < bot.getSizeSet(); z++)
				{
					if (bot.getCard(z)->isBetter(*tableToss.getCard(i), kozir.getRang()))
					{
						if (!bito)
						{
							fromBotToTableBeating(&bot.dropCard(z));
							bito = true;
							break;
						}
					}
				}
			}
			if (bito == false)
			{
				isTake = true;
			}
		}
		else{
			if (butPass)
			{
				isUrCourse = true;
				isTake = false;
				fromTableToBotOrPlayer();
			}
		}
	}
	int fromBotToTableToss(Card* card)//ф-ция для бота, которая передает карту столу, когда бот ходит или подкидывает
	{
		tableToss.addCard(*card);
		cout << "TableBeating: " << tableBeating.getSizeSet() << "TableToss: " << tableToss.getSizeSet() << endl;
		return 1;
	}
	void fromBotToTableBeating(Card* card)//ф-ция для бота, которая передает карты столу, когда бот отбивается
	{
		tableBeating.addCard(*card);
		cout << "TableBeating: " << tableBeating.getSizeSet() << "TableToss: " << tableToss.getSizeSet() << endl;
	}

	void tableFunc() // функция для обработки карт, для подкидывания пользователем
	{
		if (isUrCourse)
		{
			if (tableToss.getSizeSet() < 7)
			{
				if (tableToss.getSizeSet() > 0)
				{
					bool canI = false;
					for (size_t i = 0; i < tableToss.getSizeSet(); i++)
					{
						if (tableToss.getCard(i)->getValue() == clickedCard->getValue())
						{
							canI = true;
							break;
						}
					}
					for (size_t i = 0; i < tableBeating.getSizeSet(); i++)
					{
						if (tableBeating.getCard(i)->getValue() == clickedCard->getValue())
						{
							canI = true;
							break;
						}
					}
					if (!canI)
					{
						return;
					}
				}
				tableToss.addCard(*clickedCard);
				for (size_t i = 0; i < player.getSizeSet(); i++)
				{
					if (*player.getCard(i) == *clickedCard)
					{
						player.dropCard(i);
					}
				}
			}
		}
		else{
			playerDefense();
		}
		cout << "TableBeating: " << tableBeating.getSizeSet() << "TableToss: " << tableToss.getSizeSet() << endl;
	}
	//////////////////////////////////////////////////////////надо переделать алгоритм!
	void fromTableToBotOrPlayer()//ф-ция, забирающая карты со стола и отдающая или боту или игроку
	{
		cout << "TableBeating: " << tableBeating.getSizeSet() << "TableToss: " << tableToss.getSizeSet() << endl;
		if (!isUrCourse)
		{
			while (true)
			{
				if (tableBeating.getSizeSet() > 0)
				{
					player.addCard(tableBeating.dropCard(0));
				}
				else{
					break;
				}
			}
			while (true)
			{
				if (tableToss.getSizeSet() > 0)
				{
					player.addCard(tableToss.dropCard(0));
				}
				else{
					break;
				}
			}
			//timer.Start();
		}
		else{
			while (true)
			{
				if (tableBeating.getSizeSet() > 0)
				{
					bot.addCard(tableBeating.dropCard(0));
				}
				else{
					break;
				}
			}
			while (true)
			{
				if (tableToss.getSizeSet() > 0)
				{
					bot.addCard(tableToss.dropCard(0));
				}
				else{
					break;
				}
			}
			//timer.Start();
		}
		refreshDistribution();
	}

	void refreshDistribution()//ф-ция, которая восполняет недостаток карт до 6
	{
		if (coloda.getSizeSet() != 0)
		{
			if (bot.getSizeSet() < 6)
			{
				int card = 0;
				for (size_t i = bot.getSizeSet(); i < 6; i++)
				{
					if (coloda.getSizeSet() == 0)
					{
						break;
					}
					card = rand() % coloda.getSizeSet();
					bot.addCard(coloda.dropCard(card));
				}
			}
			if (player.getSizeSet() < 6)
			{
				int card = 0;
				for (size_t i = player.getSizeSet(); i < 6; i++)
				{
					if (coloda.getSizeSet() == 0)
					{
						break;
					}
					card = rand() % coloda.getSizeSet();
					player.addCard(coloda.dropCard(card));
				}
			}
		}
		initPos();
	}

	void playerDefense()
	{
		int x = event->mouseButton.x;
		int y = event->mouseButton.y;
		if (tableToss.getSizeSet() != 0)
		{
			int oneStep = 708 / tableToss.getSizeSet();
			for (size_t i = 0; i < tableToss.getSizeSet(); i++)
			{
				if (x > 300 + oneStep * i && x < 300 + oneStep * i + oneStep)
				{
					if (tableBeating.getElPos(i))
					{
						if (clickedCard->isBetter(*tableToss.getCard(i), kozir.getRang()))
						{
							tableBeating.addCard(*clickedCard);
							tableBeating.initPosArray(i, tableToss.getSizeSet());
							for (size_t i = 0; i < player.getSizeSet(); i++)
							{
								if (*player.getCard(i) == *clickedCard)
								{
									player.dropCard(i);
									break;
								}
							}
						}
					}
				}
			}
		}
	}

	~GameProc();
};

