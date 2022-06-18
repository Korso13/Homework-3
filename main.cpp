#include <iostream>
#include <string>
#include <optional>
#include <tuple>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <iomanip>

//========================================================================================================================================
//Task 1. Person structure
//========================================================================================================================================
struct Person
{
	std::string name;
	std::string surname;
	std::optional<std::string> middle_name;

	Person(std::tuple<std::string, std::string, std::optional<std::string>> _person) : surname(std::get<0>(_person)), name(std::get<1>(_person)), middle_name(std::get<2>(_person)) {}
	Person(std::string _surname, std::string _name, std::optional<std::string> _middle_name) : surname(_surname), name(_name), middle_name(_middle_name) {}
	Person(std::string _surname, std::string _name) : surname(_surname), name(_name), middle_name(std::nullopt) {}
	Person() { middle_name = std::nullopt;}
};

std::ostream& operator<<(std::ostream& out, const Person& p1)
{
	out << p1.surname << std::setw(20 - p1.surname.length());
	out << p1.name << std::setw(15);
	if (p1.middle_name.has_value())
		out << *(p1.middle_name);
	return out;
}

bool operator==(const Person& p1, const Person& p2)
{
	if (p1.middle_name.has_value() && p2.middle_name.has_value())
	{
		if (std::tie(p1.name, p1.surname, *p1.middle_name) == std::tie(p2.name, p2.surname, *p2.middle_name))
			return true;
		else
			return false;
	}
	else
	{
		if (std::tie(p1.name, p1.surname) == std::tie(p2.name, p2.surname))
			return true;
		else
			return false;
	}
}

bool operator<(const Person& p1, const Person& p2)
{
	if (p1.middle_name.has_value() && p2.middle_name.has_value())
	{
		if (std::tie(p1.surname, p1.name, *p1.middle_name) < std::tie(p2.surname, p2.name, *p2.middle_name))
			return true;
		else
			return false;
	}
	else
	{
		if (std::tie(p1.surname, p1.name ) < std::tie(p2.surname, p2.name))
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
	int country_code;
	int city_code;
	std::string number;
	std::optional<int> extension;
	
	PhoneNumber(std::tuple<int, int, std::string, std::optional<int>> _number) : country_code(std::get<0>(_number)), city_code(std::get<1>(_number)), number(std::get<2>(_number)), extension(std::get<3>(_number))	{}
	PhoneNumber(int _country_code, int _city_code, std::string _number, std::optional<int> _extension) : country_code(_country_code), city_code(_city_code), number(_number), extension(_extension) {}
	PhoneNumber() { extension = std::nullopt; }
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
		if (std::tie(phone1.country_code, phone1.city_code, phone1.number, *phone1.extension) == std::tie(phone2.country_code, phone2.city_code, phone2.number, *phone2.extension))
			return true;
		else
			return false;
	}
	else
	{
		if (std::tie(phone1.country_code, phone1.city_code, phone1.number) == std::tie(phone2.country_code, phone2.city_code, phone2.number))
			return true;
		else
			return false;
	}
}

bool operator<(const PhoneNumber& phone1, const PhoneNumber& phone2)
{
	if (phone1.extension.has_value() && phone2.extension.has_value())
	{
		if (std::tie(phone1.country_code, phone1.city_code, phone1.number, *phone1.extension) < std::tie(phone2.country_code, phone2.city_code, phone2.number, *phone2.extension))
			return true;
		else
			return false;
	}
	else
	{
		if (std::tie(phone1.country_code, phone1.city_code, phone1.number) < std::tie(phone2.country_code, phone2.city_code, phone2.number))
			return true;
		else
			return false;
	}
}

//========================================================================================================================================
//Task 3. Phonebook class
//========================================================================================================================================

bool compareName(const std::pair<Person, PhoneNumber>& _person1, const std::pair<Person, PhoneNumber>& _person2)
{
	return _person1.first < _person2.first;
}

bool compareNumbers(const std::pair<Person, PhoneNumber>& _number1, const std::pair<Person, PhoneNumber>& _number2)
{
	return _number1.second < _number2.second;
}

class PhoneBook
{
private:
	std::vector<std::pair<Person, PhoneNumber>> Phone_Book;
public:
	PhoneBook(std::ifstream& _PB_File)
	{
		std::string name, surname, middle_name, number, line_dump;
		int city_code, country_code, extention;
		std::optional<std::string> opt_middle_name;
		std::optional<int> opt_extention;
		std::stringstream line_release;
		do 
		{
			std::getline(_PB_File, line_dump);
			line_release.clear();
			line_release << line_dump;
			line_release >> surname;
			line_release >> name;
			line_release >> middle_name;
			if (!(std::stringstream(middle_name) >> country_code))
			{
				opt_middle_name = middle_name;
				line_release >> country_code;
			}
			else
			{
				opt_middle_name = std::nullopt;
				std::stringstream(middle_name) >> country_code;
			}
			
			line_release >> city_code;
			line_release >> number;
			if (!(line_release >> extention))
				opt_extention = std::nullopt;
			else
				opt_extention = extention;

			Phone_Book.push_back(std::make_pair(Person(std::tie(surname, name, opt_middle_name)), PhoneNumber(std::tie(country_code, city_code, number, opt_extention))));
		} while (!_PB_File.eof());
	}

	void SortByName()
	{
		std::sort(Phone_Book.begin(), Phone_Book.end(), compareName); 
	}

	void SortByPhone()
	{
		std::sort(Phone_Book.begin(), Phone_Book.end(), compareNumbers); 
	}

	std::tuple<std::string, PhoneNumber> GetPhoneNumber(const std::string& _surname) const 
	{
		size_t count{ 0 };
		PhoneNumber FoundNumber;

		for (const auto& [person, number] : Phone_Book)
		{
			if (person.surname == _surname)
			{
				count++;
				FoundNumber = number;
			}
		}

		if (count == 1)
			return { "", FoundNumber };
		else if (count > 1)
			return {"Found more than 1", FoundNumber };
		else
			return {"Not found", FoundNumber};
	}

	void ChangePhoneNumber(const Person& _person, const PhoneNumber& _number)
	{
		for (auto& [person, number] : Phone_Book)
		{
			if (person == _person)
			{
				number = _number;
				return;
			}
		}
		return;
	}

	friend std::ostream& operator<<(std::ostream& out, const PhoneBook& book);
};

std::ostream& operator<<(std::ostream& out, const PhoneBook& book)
{
	for (const auto& [person, number] : book.Phone_Book)
	{
		out << person << std::setw(((person.middle_name.has_value()) ? 5 : 20));
		out << number << std::endl;
	}
	return out;
}

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

	std::ifstream file("PhoneBook.txt"); // путь к файлу PhoneBook.txt
	PhoneBook book(file);
	std::cout << book;
	std::cout << "------SortByPhone-------" << std::endl;
	book.SortByPhone();
	std::cout << book;
	std::cout << "------SortByName--------" << std::endl;
	book.SortByName();
	std::cout << book;
	std::cout << "-----GetPhoneNumber-----" << std::endl;
	// лямбда функция, которая принимает фамилию и выводит номер телефона этого человека, либо строку с ошибкой
	auto print_phone_number = [&book](const std::string& surname)
	{
		std::cout << surname << "\t";
		auto answer = book.GetPhoneNumber(surname);
		if (std::get<0>(answer).empty())
			std::cout << std::get<1>(answer);
		else
			std::cout << std::get<0>(answer);
		std::cout << std::endl;
	};
	// вызовы лямбды
	print_phone_number("Ivanov");
	print_phone_number("Petrov");
	std::cout << "----ChangePhoneNumber----" << std::endl;
	book.ChangePhoneNumber(Person{ "Kotov", "Vasilii", "Eliseevich" }, PhoneNumber{ 7, 123, "15344458", std::nullopt });
	book.ChangePhoneNumber(Person{ "Mironova", "Margarita", "Vladimirovna" }, PhoneNumber{ 16, 465, "9155448", 13 });
	std::cout << book;

	return 0;
}
