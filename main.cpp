#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <cstdarg>
#include <algorithm>
#include "Expo.hpp"

using namespace std;

//========================================================================================================================================
//Task 1. Add average of list members to list
//========================================================================================================================================

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

class Matrix
{
private:
	vector<vector<int>> m_matrix; //  m_matrix[row - 1].begin() + column -1
	int m_order{ 0 };
	deque<int> ex_column;

	int CalcDeterminant_Custom()
	{
		int Det{ 0 };
		for (size_t i = 1; i <= m_order; i++)
		{
			Det += GetExpo(-1, (1 + i)) * *(m_matrix[0].begin() + i - 1) * CalcMinor((m_order - 1), 1, i - 1);
			if(ex_column.empty() == false)
				ex_column.pop_back();
		}
		return Det;
	}

	int CalcMinor(int _order, int _row_offset, int _ex_column)
	{
		ex_column.push_back(_ex_column);
		if (_order == 3)
			return CalcMinor_3x3(_row_offset);
		else
			return CalcMinor_Custom(_order, _row_offset);
	}

	int CalcMinor_Custom(int _order, int _row_offset)
	{
		int Minor{ 0 };
		int temp_i{ 1 };

		for (size_t i = 1; i <= m_order; i++)	//i - прогоны Minor. i-1 - columns
		{
			if (find(ex_column.begin(), ex_column.end(), i - 1) != ex_column.end())
				continue;
			else
			{
				Minor += GetExpo(-1, (1 + temp_i)) * *(m_matrix[_row_offset].begin() + (i - 1)) * CalcMinor((_order - 1), _row_offset + 1, i - 1);
				temp_i++;
				ex_column.pop_back();
			}
		}
		ex_column.pop_back();
		return Minor;
	}

	int CalcMinor_3x3(int _row_offset)
	{
		int elemA{ 0 }, elemB{ 0 }, elemC{ 0 }, k{ 0 }; // return a * (11*22 - 12*21) - b * (10*22 - 12*20) + c * (10*21 - 11*20)
		vector<vector<int>> _matrix;
		_matrix.reserve(3);
		for (size_t i = 0; i < 3; i++)
		{
			_matrix.push_back(*(new vector<int>));
		}
		for (auto& elem : _matrix)
			elem.reserve(3);

		for (size_t i = _row_offset; i < m_order; i++)
		{
			{
				for (size_t j = 0; j < m_order; j++)
				{
					if (find(ex_column.begin(), ex_column.end(), j) != ex_column.end()) //if found then
						continue;
					else //if not found
						_matrix[k].push_back(*(m_matrix[i].begin() + j));
				}
				k++;
			}
		}

		elemB = *(_matrix[0].begin() + 1) * ((*(_matrix[1].begin() + 0) * *(_matrix[2].begin() + 2)) - (*(_matrix[1].begin() + 2) * *(_matrix[2].begin() + 0)));
		elemA = *(_matrix[0].begin() + 0) * ((*(_matrix[1].begin() + 1) * *(_matrix[2].begin() + 2)) - (*(_matrix[1].begin() + 2) * *(_matrix[2].begin() + 1)));
		elemC = *(_matrix[0].begin() + 2) * ((*(_matrix[1].begin() + 0) * *(_matrix[2].begin() + 1)) - (*(_matrix[1].begin() + 1) * *(_matrix[2].begin() + 0)));

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
//Task 3. Custom iterator for for-range-based loop
//========================================================================================================================================

class MyArrayIt
{
private:
	int* ptr = nullptr;
	int posShift;
	size_t m_size{ 0 };
public:
	MyArrayIt(int* array, size_t _size, size_t _shift) : ptr(array), m_size(_size) { posShift = _shift; };

	bool operator!=(const MyArrayIt& _second_ptr)
	{
		if ((ptr + posShift) == (_second_ptr.ptr + _second_ptr.posShift))
			return false;
		else
			return true;
	}

	void operator++()
	{
		if(posShift != m_size)
			posShift++;
	}

	int operator*()
	{
		return *(ptr + posShift);
	}
};

template <size_t _size>
class MyIntArrContainer
{
private:
	int* startPTR = nullptr;
	size_t m_size{ 0 };
public:
	MyIntArrContainer(...) : m_size(_size)
	{
		startPTR = new int[m_size];
		va_list intValues;
		va_start(intValues, m_size);
		for (size_t i = 0; i < m_size; i++)
		{
			*(startPTR + i) = va_arg(intValues, int);
		}
		va_end(intValues);
	}

	MyArrayIt begin()
	{
		if(startPTR != nullptr)
			return MyArrayIt(startPTR, m_size, 0);
	}

	MyArrayIt end()
	{
		if (startPTR != nullptr)
			return MyArrayIt(startPTR, m_size, m_size);
	}

	/*
	MyArrayIt at(size_t _shift)
	{
		if (startPTR != nullptr)
			return MyArrayIt(startPTR, m_size, _shift);
	}
	
	void print() const
	{
		cout << endl;
		if (startPTR != nullptr)
		{
			for (size_t i = 0; i < m_size; i++)
			{
				cout << *(startPTR + i) << " ";
			}
			cout << endl;
			return;
		}
		else
			return;
	}
	*/
};


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

		Matrix M2(5);
		for (size_t i = 1; i <= 5; i++)
		{
			for (size_t j = 5; j > 0; j--)
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
	MyIntArrContainer<5> Arr1{ 1,2,3,4,5 };
	for (const auto& elem : Arr1)
		cout << elem << " ";
	cout << endl;

	/*auto it1 = Arr1.at(2);
	cout << *it1 << endl;*/
	return 0;
}
