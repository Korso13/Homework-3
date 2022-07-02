#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <list>
#include <algorithm>
#include <forward_list>
#include <string>

using namespace std;

//========================================================================================================================================
//Task 1. Unique words lister
//========================================================================================================================================
/*
Создать шаблонную функцию, которая принимает итераторы на начало и конец последовательности слов, и выводящую в консоль список уникальных слов 
(если слово повторяется больше 1 раза, то вывести его надо один раз). 
Продемонстрировать работу функции, передав итераторы различных типов.
*/

template <class ItType>
void UniqueWordsList(ItType it_begin, ItType it_end)
{
	set<string> WordsSet(it_begin, it_end);
	cout << "Уникальные слова в последовательности: ";
	for (auto const& word : WordsSet)
		cout << word << " ";
	cout << endl;
}


int main()
{
	system("chcp 1251");
	
	//========================================================================================================================================
	//Task 1. Unique words lister
	//========================================================================================================================================
	{
		vector<string> words2{"жёлтый", "красный", "серый", "белый", "чёрный", "синий", "жёлтый", "белый", "серый"};
		vector<string>::iterator w2Start= words2.begin();
		vector<string>::iterator w2End = prev(words2.end(), 2);
		list<string> words3(words2.begin(), words2.end());
		forward_list<string> words1(words2.begin(), words2.end());

		UniqueWordsList(words1.begin(), words1.end());
		UniqueWordsList(w2Start, w2End);
		UniqueWordsList(words3.begin(), words3.end());
	}


	//========================================================================================================================================
	//Task 2. Text processor
	//========================================================================================================================================
	cout << endl;

	{
		string stringBacklog;
		cout << "Введите текст: ";
		getline(cin, stringBacklog);

		multimap<int, string> SentenceMap;
		int WordCount{ 0 };
		auto pos1 = stringBacklog.begin();
		auto pos2 = pos1;
		string temp;
		do
		{
			temp.clear();
			temp.resize(stringBacklog.size());
			pos2 = find(pos1, stringBacklog.end(), '.');
			copy(pos1, pos2 + 1, temp.begin());
			unique(temp.begin(), temp.end(), [](char _ch1, char _ch2) {if (_ch1 == ' ' && _ch2 == ' ') return true; else return false; });
			WordCount = count(temp.begin(), temp.end(), ' ');
			WordCount++; //counting last word that ends with comma not whitespace
			SentenceMap.insert({WordCount, temp});
			WordCount = 0;
			if (pos2 + 1 == stringBacklog.end())
				break;
			pos1 = pos2 + 2;
		} while (pos2 + 1 != stringBacklog.end());

		for (auto const& elem : SentenceMap)
			cout << elem.second << " Кол-во слов: " << elem.first << endl;
	}

	return 0;
}
