#pragma once
#include <vector>
#include <string>

enum Ranks { two = 2, three = 3, four = 4, five = 5, six = 6, seven = 7, eight = 8, nine = 9, ten = 10, jack = 10, queen = 10, king = 10, ace = 1 };
enum Suits { spades, clubs, diamonds, hearts };

class Card
{
protected:
	Ranks m_value;
	Suits m_suit;
	bool m_faceUp{ 0 }; //0 - рубашкой кверху, 1 - в открытую
public:
	Card(Ranks value, Suits suit, bool faceUp = 0) : m_value(value), m_suit(suit), m_faceUp(faceUp) {}

	void Flip();

	Ranks GetValue() const;
};


class Hand
{
protected:
	std::vector<Card*> m_hand;
public:
	Hand() {}
	virtual ~Hand() {}

	void Add(Card* card);

	void Clear();

	int GetValue() const;
};

class GenericPlayer : public Hand
{
protected:
	std::string m_name;
public:
	GenericPlayer(std::string name) : Hand(), m_name(name) {}
	virtual ~GenericPlayer() {}

	virtual bool IsHitting() const = 0;

	bool IsBoosted() const;

	void Bust() const;
};
