#include <iostream>
#include <string>
#include <sstream>
#include "BJ_Classes_Functions.h"

//========================================================================================================================================
//Task 2. Making own endll manipulator
//========================================================================================================================================

std::ostream& endll(std::ostream &out)
{
	out << '\n' << '\n';
	out.flush();
	return out;
}

//========================================================================================================================================
//Task 3. Creating player class for BJ
//========================================================================================================================================
/*
Реализовать класс Player, который наследует от класса GenericPlayer. У этого класса будет 4 метода:
• virtual bool IsHitting() const - реализация чисто виртуальной функции базового класса.
  Метод спрашивает у пользователя, нужна ли ему еще одна карта и возвращает ответ пользователя в виде true или false.
• void Win() const- выводит на экран имя игрока и сообщение, что он выиграл.
• void Lose() const - выводит на экран имя игрока и сообщение, что он проиграл.
• void Push() const - выводит на экран имя игрока и сообщение, что он сыграл вничью.
*/


class Player : public GenericPlayer
{
public:
	Player(std::string name) : GenericPlayer(name) {};
	~Player() {};

	virtual bool IsHitting() const
	{
		std::string t;
		std::cout << "Игрок " << m_name << ", нужна ли Вам ещё карта? ";
		for (;;) //fool protection
		{
			std::cin >> t;
			if (t == "yes" || t == "Yes" || t == "y" || t == "Y" || t == "да" || t == "д" || t == "Да" || t == "Д" || t == "no" || t == "No" || t == "n" || t == "N" || t == "нет" || t == "н" || t == "Нет" || t == "Н")
				break;
			else
			{
				std::cout << "Некорректный ввод! Попробуйне снова!";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << '\n' << "Нужна ли Вам ещё карта? ";
				t.clear();
			}
		}
		if ( t == "yes" || t == "Yes" || t == "y" || t == "Y" || t == "да" || t == "д" || t == "Да" || t == "Д")
			return true;
		else
			return false;
	}
	void Win() const {std::cout << "Игрок " << m_name << " выиграл!" << "\n";}
	void Lose() const { std::cout << "Игрок " << m_name << " проиграл!" << "\n"; }
	void Push() const { std::cout << "У игрока " << m_name << " и диллера очков поровну!" << "\n"; }
};

//========================================================================================================================================
//Task 4. Creating House class for BJ
//========================================================================================================================================
/*
Реализовать класс House, который представляет дилера. Этот класс наследует от класса GenericPlayer. У него есть 2 метода:
• virtual bool IsHitting() const - метод указывает, нужна ли дилеру еще одна карта. Если у дилера не больше 16 очков, 
  то он берет еще одну карту.
• void FlipFirstCard() - метод переворачивает первую карту дилера.
*/

class House : public GenericPlayer
{
public:
	House(std::string name = "Диллер") : GenericPlayer(name) {};
	~House() {};
	virtual bool IsHitting() const
	{
		if (GetValue() < 17)
			return true;
		else
			return false;
	}
	void FlipFirstCard()
	{
		m_hand[0]->Flip();
	}
};


//========================================================================================================================================
//Task 5. Overloading ostream for BJ purposes
//========================================================================================================================================
/*
Написать перегрузку оператора вывода для класса Card: 
• Если карта перевернута рубашкой вверх (мы ее не видим), вывести ХХ, если мы ее видим, вывести масть и номинал карты.
• Также для класса GenericPlayer написать перегрузку оператора вывода, который должен отображать имя игрока и его карты,
  а также общую сумму очков его карт.
*/

std::ostream& operator<<(std::ostream &out, const Card& card)
{
	if (card.m_faceUp == false)
	{
		out << "XX";
	}
	else
	{
			switch(card.m_value)
			{
			case(ace):
				out << "ace" << " of ";
				break;
			case(jack):
				out << "jack" << " of ";
				break;
			case(queen):
				out << "queen" << " of ";
				break;
			case(king):
				out << "king" << " of ";
				break;
			case(ten):
				out << "ten" << " of ";
				break;
			case(nine):
				out << "nine" << " of ";
				break;
			case(eight):
				out << "eight" << " of ";
				break;
			case(seven):
				out << "seven" << " of ";
				break;
			case(six):
				out << "six" << " of ";
				break;
			case(five):
				out << "five" << " of ";
				break;
			case(four):
				out << "four" << " of ";
				break;
			case(three):
				out << "three" << " of ";
				break;
			case(two):
				out << "two" << " of ";
				break;
			default:
				out << "fail";
			}
		
		switch (card.m_suit)
		{
		case(spades):
			out << "spades";
			break;
		case(hearts):
			out << "hearts";
			break;
		case(clubs):
			out << "clubs";
			break;
		case(diamonds):
			out << "diamonds";
			break;
		default:
			out << "fail";
		}
	}
	return out;
}

std::ostream& operator<<(std::ostream& out, const GenericPlayer& player)
{
	if(player.m_name == "Диллер")
		out << "Диллер имеет на руках следующие карты: \n";
	else
		out << "Игрок " << player.m_name << " имеет на руках следующие карты: \n";
	for (size_t i = 0; i < player.m_hand.size(); i++)
	{
		out << *(player.m_hand[i]) << '\n';
	}
	out << "Сумма всех карт игрока равна: " << player.GetValue() << '\n';
	return out;
};

int main()
{
	setlocale(LC_ALL, "Russian");
	system("chcp 1251");

	//========================================================================================================================================
	//Task 1. Input check
	//========================================================================================================================================
	/*
	Пример неправильных введенных строк:
	rbtrb
	nj34njkn
	1n
	*/

	{
		int inputValue;
		std::string tempStr;
		std::istringstream ss;
		for (;;)
		{
			std::cout << "Введите одно целое число: ";
			std::getline(std::cin, tempStr);
			ss.str(tempStr);
			if (ss >> inputValue && ss.eof())
				break;
			else
			{
				std::cout << "Некорректный ввод! Введите число повторно!";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << '\n';
				inputValue = 0;
				ss.clear();
				tempStr.clear();
			}
		}
	}

	//========================================================================================================================================
	//Checks for other tasks
	//========================================================================================================================================

	{
		std::cout << "first line" << endll;
		std::cout << "second line" << std::endl;
		std::cout << "final line" << std::endl;
	}

	{
		Player p1("John");
		std::cout << std::boolalpha << p1.IsHitting() << "\n";
		House dealer;
		Card c1(six, spades, 1);
		Card c2(two, clubs, 1);
		Card c3(queen, diamonds, 1);
		p1.Add(&c1);
		p1.Add(&c2);
		p1.Add(&c3);
		dealer.Add(&c1);
		dealer.Add(&c3);
		std::cout << p1;
		std::cout << dealer;
	}

	
	return 0;
}
