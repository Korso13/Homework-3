#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "BJ_Classes_Functions.h"

//Card class methods:

void Card::Flip()
{
	m_faceUp = !m_faceUp;
}

Ranks Card::GetValue() const
{
	return m_value;
}

//Hand class methods:

void Hand::Add(Card* card)
{
	m_hand.push_back(card);
}

void Hand::Clear()
{
	m_hand.clear();
	m_hand.resize(0);
	m_hand.shrink_to_fit();
}

int Hand::GetValue() const
{
	int sum{ 0 };
	int aces{ 0 };
	for (size_t i = 0; i < m_hand.size(); i++)
	{
		if (m_hand[i]->GetValue() == ace)
		{
			sum += 11;
			aces++;
		}
		else
			sum += m_hand[i]->GetValue();
	}

	//if total value exceeds 21 we remove extra 10 points per ace reducing it from 11 to 1. This way aces work even if drawn from index 0 and value exceeds 21 later on
	if (sum > 21 && aces > 0)
		sum = sum - (aces * 10);

	return sum;
}

//GenericPlayer class methods:
bool GenericPlayer::IsBoosted() const
{
	if (GetValue() > 21)
		return true;
	else
		return false;
};

void GenericPlayer::Bust() const
{
	std::cout << "У игрока " << m_name << " перебор!" << std::endl;
};