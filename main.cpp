#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <algorithm>
#include "Expo.hpp"

using namespace std;

//========================================================================================================================================
//Task 1. Add average of list members to list
//========================================================================================================================================
/*
Написать функцию, добавляющую в конец списка вещественных чисел элемент, значение которого равно среднему арифметическому всех его элементов.
*/

void AddAverageDouble(list<double>& _list)
{
	double sum{ 0.0 };
	for (auto const& elem : _list)
	{
		sum += elem;
	}
	_list.push_back((sum / _list.size()));
}

//========================================================================================================================================
//Task 2. Matrix determinant
//========================================================================================================================================
/*
Создать класс, представляющий матрицу. Реализовать в нем метод, вычисляющий определитель матрицы. Для реализации используйте контейнеры из STL.
*/

class Matrix
{
private:
	vector<vector<int>> m_matrix; //  m_matrix[строка].begin() + столбец -1 (А-строка-столбец)
	int m_order{ 0 };
	deque<int> ex_row;

	int CalcDeterminant_Custom()
	{
		int Det{ 0 };
		for (size_t i = 1; i <= m_order; i++)
			Det += GetExpo(-1, (1 + i)) * *(m_matrix[0].begin() + i - 1) * CalcMinor((m_order - 1), 1, i-1);
		return Det;
	}

	int CalcMinor(int _order, int _column_offset, int _ex_row)
	{
		ex_row.push_back(_ex_row);
		if (_order == 3)
			return CalcMinor_3x3(_column_offset);
		else
			return CalcMinor_Custom(_order, _column_offset);
	}

	int CalcMinor_Custom(int _order, int _column_offset)
	{
		int Minor{ 0 };
		int temp_i{1};
		int first_valid_row{0};
		for (size_t i = 0; i < m_order; i++) //find first row available for Minor's calculation
		{
			if (find(ex_row.begin(), ex_row.end(), i) != ex_row.end())
				continue;
			else
				{
					first_valid_row = i;
					break;
				}
		}

		for (size_t i = 1; i <= _order; i++)	//i - прогоны Minor. i-1 - rows
		{
			if (find(ex_row.begin(), ex_row.end(), i-1) != ex_row.end())
				continue;
			else
			{
				Minor += GetExpo(-1, (1 + temp_i)) * *(m_matrix[first_valid_row].begin() + (_column_offset + i - 1)) * CalcMinor((_order - 1), _column_offset + 1, i - 1);
				temp_i++;
			}
		}
		ex_row.pop_back();
		return Minor;
	}

	int CalcMinor_3x3(int _column_offset)
	{
		int elemA{ 0 }, elemB{ 0 }, elemC{ 0 }, k{0}; // return a * (11*22 - 12*21) - b * (10*22 - 12*20) + c * (10*21 - 11*20)
		vector<vector<int>> _matrix;
		_matrix.reserve(3);
		for (size_t i = 0; i < 3; i++)
		{
			_matrix.push_back(*(new vector<int>));
		}
		for (auto& elem : _matrix)
			elem.reserve(3);

		for (size_t i = 0; i < m_order; i++)
		{
			if (find(ex_row.begin(), ex_row.end(), i) != ex_row.end())
				continue;
			else
			{
				for (size_t j = _column_offset; j < m_order; j++)
				{
					_matrix[k].push_back(*(m_matrix[i].begin() + j));
				}
				k++;
			}
		}

		elemB = *(_matrix[0].begin() + 1) * ((*(_matrix[1].begin() + 0) * *(_matrix[2].begin() + 2)) - (*(_matrix[1].begin() + 2) * *(_matrix[2].begin() + 0)));
		elemA = *(_matrix[0].begin() + 0) * ((*(_matrix[1].begin() + 1) * *(_matrix[2].begin() + 2)) - (*(_matrix[1].begin() + 2) * *(_matrix[2].begin() + 1)));
		elemC = *(_matrix[0].begin() + 2) * ((*(_matrix[1].begin() + 0) * *(_matrix[2].begin() + 1)) - (*(_matrix[1].begin() + 1) * *(_matrix[2].begin() + 0)));
		ex_row.pop_back();
		return (elemA - elemB + elemC);
	}

	int CalcDeterminant_3x3()
	{
		int elemA{0}, elemB{0}, elemC{0}; // return a * (11*22 - 12*21) - b * (10*22 - 12*20) + c * (10*21 - 11*20)
		elemA = *(m_matrix[0].begin() + 0) * ((*(m_matrix[1].begin() + 1)** (m_matrix[2].begin() + 2)) - (*(m_matrix[1].begin() + 2) * *(m_matrix[2].begin() + 1)));
		elemB = *(m_matrix[0].begin() + 1) * ((*(m_matrix[1].begin() + 0) * *(m_matrix[2].begin() + 2)) - (*(m_matrix[1].begin() + 2) * *(m_matrix[2].begin() + 0)));
		elemC = *(m_matrix[0].begin() + 2) * ((*(m_matrix[1].begin() + 0) * *(m_matrix[2].begin() + 1)) - (*(m_matrix[1].begin() + 1) * *(m_matrix[2].begin() + 0)));
		return (elemA - elemB + elemC);
	}

	int CalcDeterminant_2x2()
	{
		return ( (*(m_matrix[1].begin()) * *(m_matrix[2].end() - 1)) - (*(m_matrix[2].begin()) * *(m_matrix[1].end() - 1)));
	}

	int CalcDeterminant_1x1()
	{
		return *(m_matrix[1].begin());
	}

public:
	Matrix(int _order)
	{
		m_matrix.reserve(_order);
		for (size_t i = 0; i < _order; i++)
		{
			m_matrix.push_back(*(new vector<int>));
		}
		for (auto& elem : m_matrix)
			elem.reserve(_order);
		m_order = _order;
	}

	void AddMatrixValue(int row, int _value)
	{
		if (m_matrix[row - 1].size() != m_matrix[row - 1].capacity())
			m_matrix[row-1].push_back(_value);
		else
			cout << "Row already full!" << endl;
	}

	void ForceAddMatrixValue(int row, int _value)
	{
		m_matrix[row - 1].push_back(_value);
		if (row == 1)
			if (m_matrix[row].capacity() != m_matrix[row - 1].capacity())
			{
				for (auto& elem : m_matrix)
					m_matrix.resize(m_matrix[row].capacity());
				return;
			}
			else
				do {} while (false) ;
		else if(row != 1)
			if (m_matrix[row - 2].capacity() != m_matrix[row - 1].capacity())
			{
				for (auto& elem : m_matrix)
					m_matrix.resize(m_matrix[row].capacity());
				return;
			}
	}

	int CalcDeterminant()
	{
		if (m_order == 1)
			return CalcDeterminant_1x1();
		if (m_order == 2)
			return CalcDeterminant_2x2();
		if (m_order == 3)
			return CalcDeterminant_3x3();
		else
			return CalcDeterminant_Custom();
	}

	void print() const
	{
		for (auto const& elem1 : m_matrix)
		{
			cout << endl;
			for (auto const& elem2 : elem1)
				cout << elem2 << " ";
		}
	}
};

//========================================================================================================================================
//Task 3. 
//========================================================================================================================================
/*
Реализовать собственный класс итератора, с помощью которого можно будет проитерироваться по диапазону целых чисел в цикле for-range-based.
*/



int main()
{
	system("chcp 1251");
	
	//========================================================================================================================================
	//Task 1. Add average of list members to list
	//========================================================================================================================================


	{
		list<double> DoubleList{ 3.14, 5.23, 2.43, 3.15 };
		AddAverageDouble(DoubleList);
		for (auto const& elem : DoubleList)
			cout << elem << " ";
		cout << endl; 
	}

	//========================================================================================================================================
	//Task 2. Matrix determinant
	//========================================================================================================================================
	cout << endl;

	{
		Matrix M1(3);
		M1.AddMatrixValue(1, 1);
		M1.AddMatrixValue(1, 2);
		M1.AddMatrixValue(1, 3);
		M1.AddMatrixValue(2, 4);
		M1.AddMatrixValue(2, 5);
		M1.AddMatrixValue(2, 6);
		M1.AddMatrixValue(3, 7);
		M1.AddMatrixValue(3, 8);
		M1.AddMatrixValue(3, 9);
		M1.print();
		cout << endl << "M1 determinant is: " << M1.CalcDeterminant() << endl;

		Matrix M2(4);
		for (size_t i = 1; i <= 4; i++)
		{
			for (size_t j = 0; j < 4; j++)
			{
				M2.AddMatrixValue(i, rand() % 9);
			}
		}
		M2.print();
		cout << endl << "M2 determinant is: " << M2.CalcDeterminant() << endl;
	}

	//========================================================================================================================================
	//Task 3. 
	//========================================================================================================================================
	cout << endl;
	
	
	return 0;
}
