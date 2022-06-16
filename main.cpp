#include <iostream>
#include <string>
#include <optional>
#include <tuple>
#include <vector>
#include <fstream>

//========================================================================================================================================
//Task 1. Person structure
//========================================================================================================================================
struct Person
{
private:
	std::optional<std::string> get_middle_name(const std::string& _middle_name) const
	{
		if (_middle_name.empty())
			return std::nullopt;
		else
			return _middle_name;
	}
public:
	std::string name;
	std::string surname;
	std::optional<std::string> middle_name;

	Person(std::tuple<std::string, std::string, std::string> _person) : surname(get<0>(_person)), name(get<1>(_person))
	{
		middle_name = get_middle_name(get<2>(_person));
	}

	//Person(const std::string& _surname, const std::string& _name, const std::string& _middle_name) : name(_name), surname(_surname)
	//{
	//	middle_name = get_middle_name(_middle_name);
	//}

	//Person(const std::string& _name, const std::string& _surname) : name(_name), surname(_surname)
	//{
	//	middle_name = std::nullopt;
	//}
};

std::ostream& operator<<(std::ostream& out, const Person& p1)
{
	out << p1.name << " " << p1.surname << " ";
	if (p1.middle_name.has_value())
		out << *(p1.middle_name);
	return out;
}

bool operator==(const Person& p1, const Person& p2)
{
	if (p1.middle_name.has_value() && p2.middle_name.has_value())
	{
		if (tie(p1.name, p1.surname, *p1.middle_name) == tie(p2.name, p2.surname, *p2.middle_name))
			return true;
		else
			return false;
	}
	else
	{
		if (tie(p1.name, p1.surname) == tie(p2.name, p2.surname))
			return true;
		else
			return false;
	}
}

bool operator<(const Person& p1, const Person& p2)
{
	if (p1.middle_name.has_value() && p2.middle_name.has_value())
	{
		if (tie(p1.name, p1.surname, *p1.middle_name) < tie(p2.name, p2.surname, *p2.middle_name))
			return true;
		else
			return false;
	}
	else
	{
		if (tie(p1.name, p1.surname) < tie(p2.name, p2.surname))
			return true;
		else
			return false;
	}
}

//========================================================================================================================================
//Task 2. PhoneNumber structure
//========================================================================================================================================

struct PhoneNumber
{
private:
	std::optional<int> get_extension(int _ext) const
	{
		if (_ext == 0)
			return std::nullopt;
		else
			return _ext;
	}
public:
	int country_code;
	int city_code;
	std::string number;
	std::optional<int> extension;
	
	PhoneNumber(std::tuple<int, int, std::string, int> _number) : country_code(get<0>(_number)), city_code(get<1>(_number)), number(get<2>(_number))
	{
		extension = get_extension(get<3>(_number));
	}
	
	//PhoneNumber(const int& _country_code, const int& _city_code, const std::string& _number, const int& _extention) : country_code(_country_code), city_code(_city_code), number(_number)
	//{
	//	extension = get_extension(_extention);
	//}

	//PhoneNumber(const int& _country_code, const int& _city_code, const std::string& _number) : country_code(_country_code), city_code(_city_code), number(_number)
	//{
	//	extension = get_extension(0);
	//}
};

std::ostream& operator<<(std::ostream& out, const PhoneNumber& phone)
{
	out << "+" << phone.country_code << "(" << phone.city_code << ")" << phone.number;
	if (phone.extension.has_value())
		out << " " << * (phone.extension);
	return out;
}

bool operator==(const PhoneNumber& phone1, const PhoneNumber& phone2)
{
	if (phone1.extension.has_value() && phone2.extension.has_value())
	{
		if (tie(phone1.country_code, phone1.city_code, phone1.number, *phone1.extension) == tie(phone2.country_code, phone2.city_code, phone2.number, *phone2.extension))
			return true;
		else
			return false;
	}
	else
	{
		if (tie(phone1.country_code, phone1.city_code, phone1.number) == tie(phone2.country_code, phone2.city_code, phone2.number))
			return true;
		else
			return false;
	}
}

bool operator<(const PhoneNumber& phone1, const PhoneNumber& phone2)
{
	if (phone1.extension.has_value() && phone2.extension.has_value())
	{
		if (tie(phone1.country_code, phone1.city_code, phone1.number, *phone1.extension) < tie(phone2.country_code, phone2.city_code, phone2.number, *phone2.extension))
			return true;
		else
			return false;
	}
	else
	{
		if (tie(phone1.country_code, phone1.city_code, phone1.number) < tie(phone2.country_code, phone2.city_code, phone2.number))
			return true;
		else
			return false;
	}
}

//========================================================================================================================================
//Task 3. Phonebook class
//========================================================================================================================================

class PhoneBook
{
private:
	std::vector<std::pair<Person, PhoneNumber>> Phone_Book;
public:
	PhoneBook(std::ifstream& _PB_File)
	{
		std::tuple<std::string, std::string, std::string> _person;
		std::tuple<int, int, std::string, int> _number;
		std::string name, surname, middle_name, number;
		int city_code, country_code, extention;
		do
		{
			std::getline(_PB_File, surname);
			std::getline(_PB_File, name);
			std::getline(_PB_File, middle_name);
			_PB_File >> country_code;
			_PB_File >> city_code;
			std::getline(_PB_File, number);
			_PB_File >> extention;

			_person = tie(surname, name, middle_name);
			_number = tie(country_code, city_code, number, extention);
			Person person1(_person);
			PhoneNumber phone1(_number);
			Phone_Book.push_back(std::make_pair(person1, phone1));
		} while (_PB_File.eof());
	}

};

//========================================================================================================================================
//Task 4. 
//========================================================================================================================================


//========================================================================================================================================
//Task 5. 
//========================================================================================================================================


int main()
{
	system("chcp 1251");
	
	/*Person p1("John", "Smith", "Vanger");
	Person p2("Smith", "Smith", "Vanger");
	Person p3("Mike", "Smith");
	Person p4("Mike", "Smith", "Vanger");
	if (p1 < p2)
		std::cout << p1 << std::endl;
	else
		std::cout << p2 << std::endl;
	std::cout << p3 << std::endl;

	if(p3 == p4)
		std::cout << p3 << std::endl;*/



	return 0;
}
