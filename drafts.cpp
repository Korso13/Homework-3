#include <iostream>
#include <algorythm>

//========================================================================================================================================
//Task 1. 
//========================================================================================================================================


//========================================================================================================================================
//Task 2. 
//========================================================================================================================================


//========================================================================================================================================
//Task 3. 
//========================================================================================================================================


//========================================================================================================================================
//Task 4. 
//========================================================================================================================================
void SortByName()
{
	sort(Phone_Book->first.begin(), Phone_Book->first.end()); //change order in overloaded < function!!
}

void SortByPhone()
{
	sort(Phone_Book->second.begin(), Phone_Book->second.end());
}

tuple<std::string, PhoneNumber> GetPhoneNumber (const Person.surname& _surname) const
{
	size_t count{0};
	
	for(const auto& person : Phone_Book->first)
	{
		if(person.surname == _surname)
		{
			count++;
			Person FoundPerson = person; //Mb add default constructor?
		}
	}
	
	if(count == 1)
		return tuple<std::string, Person> = tie(, FoundPerson);
	else if (count > 1)
		return tuple<std::string, Person> = tie("Found more than 1", );
	else 
		return tuple<std::string, Person> = tie("Not found", );
}

void ChangePhoneNumber (Person& _person, PhoneNumber& _number)
{
	for(const auto& [person, number] : Phone_Book)
	{
		if(person == _person)
		{
			number = _number;
			return;
		}
	}
	return;
}

//========================================================================================================================================
//Task 5.
//========================================================================================================================================


int main1()
{

	return 0;
}
