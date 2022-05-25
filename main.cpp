#include <iostream>
#include <cmath>

#define PI 3.14159265358979323846

struct Coord
{
	int x{ 0 };
	int y{ 0 };
};

//========================================================================================================================================
//Task 1. Figures (check overriding type of return value in area methods)
//========================================================================================================================================

class Figure //base class
{
public:
	Figure() {}

	virtual double const area() = 0;
};

class Circle final : virtual public Figure
{
private:
	int radius;

public:
	Circle(int rad) : radius(rad) {}

	double const area() override { return (radius * radius * PI); }
};

/*
	A _____________B
	 /            /
	/            /
   /            /
D /____________/C
*/

class Parallelogram : virtual public Figure
{
protected:
	Coord a, b, c, d;  //ab - верхняя грань, bc - правая грань и т.д.

public:
	Parallelogram(int ax, int ay, int bx, int by, int cx, int cy, int dx, int dy)
	{
		a.x = ax;
		a.y = ay;
		b.x = bx;
		b.y = by;
		c.x = cx;
		c.y = cy;
		d.x = dx;
		d.y = dy;
	}

	double const area() override { return ((a.y - d.y) * sqrt((c.x - d.x) + (c.y - d.y))); } //высота параллелограмма * на нижнюю грань. Верно для так же для ромба.
};

class Rectangle final : virtual public Parallelogram
{
public:
	Rectangle(int ax, int ay, int bx, int by, int cx, int cy, int dx, int dy) : Parallelogram(a.x, a.y, b.x, b.y, c.x, c.y, d.x, d.y) {};

	double const area() override { return ((a.y - d.y) * (c.x - d.x)); }
};

class Rhombus final : virtual public Parallelogram
{
public:
	Rhombus(int ax, int ay, int bx, int by, int cx, int cy, int dx, int dy) : Parallelogram(a.x, a.y, b.x, b.y, c.x, c.y, d.x, d.y) {};
};

class Square final : virtual public Parallelogram
{
public:
	Square(int ax, int ay, int bx, int by, int cx, int cy, int dx, int dy) : Parallelogram(ax, ay, bx, by, cx, cy, dx, dy) {};

	double const area() override { return ((b.x - a.x) * (b.x - a.x)); }
};

//========================================================================================================================================
//Task 2. Машины и алмаз смерти
//========================================================================================================================================

class Car
{
protected:
	char* company;
	char* model;
public:
	Car(const char* company, const char* model) : company((char*)company), model((char*)model) { std::cout << "Car/" << company << "/" << model << std::endl; }
	virtual ~Car() { std::cout << "~Car" << std::endl; }
};

class PassengerCar : virtual public Car
{
public:
	PassengerCar(const char* company, const char* model) : Car(company, model) { std::cout << "PassengerCar/" << company << "/" << model << std::endl; }
	virtual ~PassengerCar() { std::cout << "~PassengerCar" << std::endl; }
};

class Bus : virtual public Car
{
public:
	Bus(const char* company, const char* model) : Car(company, model) { std::cout << "Bus/" << company << "/" << model << std::endl; }
	virtual ~Bus() { std::cout << "~Bus" << std::endl; }
};

class Minivan final : public Bus, public PassengerCar
{
public:
	Minivan(const char* company, const char* model) : Bus(company, model), Car(company, model), PassengerCar(company, model) { std::cout << "Minivan/" << company << "/" << model << std::endl; }
	~Minivan() { std::cout << "~Minivan" << std::endl; }
};

//========================================================================================================================================
//Task 3. Перегрузка операторов
//========================================================================================================================================

class Fraction
{
private:
	int m_numerator, m_denominator;
public:
	Fraction(int numerator, int denominator) : m_numerator(numerator)
	{
		if (denominator != 0)
			m_denominator = denominator;
		else
		{
			m_denominator = 1;
			std::cout << "Знаменатель не может быть равен 0! Взят знаменатель 1!" << std::endl;
		}
	}

	int getNum() const { return m_numerator; }
	int getDen() const { return m_denominator; }
	void print() const { std::cout << m_numerator << "/" << m_denominator; }

	Fraction operator-() const
	{
		return Fraction(-m_numerator, -m_denominator);
	}
};

int LCM(int a, int b) //функция нахождения наименьшего общего кратного
{
	if (a < 0)
		a = -a;
	if (b < 0)
		b = -b;

	if (a % b == 0)
		return ((a * b) / b);
	if (b % a == 0)
		return ((a * b) / a);
	//если не сработало ->
	int GCD{ 0 }, i{0};
	if (a > b)
		i = b;
	else
		i = a;
	for (; i > 0; i--)
	{
		if ((a % i == 0) && (b % i == 0))
			GCD = i;
	}
	return ((a * b) / GCD);
}

Fraction operator+(const Fraction& f1, const Fraction& f2)
{
	int num1{ f1.getNum() }, num2{ f2.getNum() }, den1{ f1.getDen() }, den2{ f2.getDen() };
	num1 *= LCM(den1, den2) / den1;
	num2 *= LCM(den1, den2) / den2;
	den1 *= LCM(den1, den2) / den1;
	den2 = den1; //общий знаменатель
	return Fraction((num1 + num2), (den1));
}

Fraction operator-(const Fraction& f1, const Fraction& f2)
{
	int num1{ f1.getNum() }, num2{ f2.getNum() }, den1{ f1.getDen() }, den2{ f2.getDen() };
	num1 *= LCM(den1, den2) / den1;
	num2 *= LCM(den1, den2) / den2;
	den1 *= LCM(den1, den2) / den1;
	den2 = den1; //общий знаменатель
	return Fraction((num1 - num2), (den1));
}

Fraction operator*(const Fraction& f1, const Fraction& f2)
{
	return Fraction((f1.getNum() * f2.getNum()), (f1.getDen() * f2.getDen()));
}

Fraction operator/(const Fraction& f1, const Fraction& f2)
{
	return Fraction((f1.getNum() * f2.getDen()), (f2.getNum() * f1.getDen()));
}

bool operator==(const Fraction& f1, const Fraction& f2)
{
	int num1{ f1.getNum() }, num2{ f2.getNum() }, den1{ f1.getDen() }, den2{ f2.getDen() };
	num1 *= LCM(den1, den2) / den1; //приведение к общему знаменателю
	num2 *= LCM(den1, den2) / den2;
	if (num1 == num2)
		return 1;
	else
		return 0;
}

bool operator!=(const Fraction& f1, const Fraction& f2)
{
	int num1{ f1.getNum() }, num2{ f2.getNum() }, den1{ f1.getDen() }, den2{ f2.getDen() };
	num1 *= LCM(den1, den2) / den1; //приведение к общему знаменателю
	num2 *= LCM(den1, den2) / den2;
	if (num1 == num2)
		return 0;
	else
		return 1;
}

bool operator<(const Fraction& f1, const Fraction& f2)
{
	int num1{ f1.getNum() }, num2{ f2.getNum() }, den1{ f1.getDen() }, den2{ f2.getDen() };
	num1 *= LCM(den1, den2) / den1; //приведение к общему знаменателю
	num2 *= LCM(den1, den2) / den2;
	if (num1 < num2)
		return 1;
	else
		return 0;
}

bool operator>=(const Fraction& f1, const Fraction& f2)
{
	return !(f1 < f2);
}

bool operator<=(const Fraction& f1, const Fraction& f2)
{
	int num1{ f1.getNum() }, num2{ f2.getNum() }, den1{ f1.getDen() }, den2{ f2.getDen() };
	num1 *= LCM(den1, den2) / den1; //приведение к общему знаменателю
	num2 *= LCM(den1, den2) / den2;
	if (num1 <= num2)
		return 1;
	else
		return 0;
}

bool operator>(const Fraction& f1, const Fraction& f2)
{
	return !(f1 <= f2);
}

//========================================================================================================================================
//Task 4. Класс Card для игры БлэкДжек
//========================================================================================================================================

enum Ranks {two = 2, three = 3, four = 4, five = 5, six = 6, seven = 7, eight = 8, nine = 9, ten = 10, jack = 10, queen = 10, king = 10, ace = 1};
enum Suits{ spades, clubs, diamonds, hearts };

class Card
{
protected:
	Ranks m_value;
	Suits m_suit;
	bool m_faceUp{ 0 }; //0 - рубашкой кверху, 1 - в открытую
public:
	Card(Ranks value, Suits suit, bool faceUp = 0) : m_value(value), m_suit(suit), m_faceUp(faceUp) {}
	
	void Flip()
	{
		m_faceUp = !m_faceUp;
	}

	int GetValue()
	{
		return (int)m_value;
	}
};

int main()
{
	setlocale(LC_ALL, "Russian");
	{
		Square sq1(1, 3, 3, 3, 3, 1, 1, 1);
		std::cout << sq1.area() << std::endl;
		Parallelogram pg1(1, 3, 4, 3, 3, 1, 0, 1);
		std::cout << pg1.area() << std::endl;
	}

	std::cout << "Task 2" << std::endl;
	//========================================================================================================================================
	//Task 2. Машины и алмаз смерти
	//========================================================================================================================================

	{
		Car car1("Some car", "car1");
		PassengerCar car2("Other car", "car2");
		Bus car3("Another car", "car3");
		Minivan car4("Different car", "car4");
	}

	std::cout << "Task 3" << std::endl;

	//========================================================================================================================================
	//Task 3. Перегрузка операторов
	//========================================================================================================================================

	{
		Fraction f1(1, 4);
		Fraction f2(2, 8);
		Fraction f3(1, 3);
		Fraction f4(3, 12);
		if (f1 == f2)
			printf("f1 и f2 равны \n"); //correct
		else
			printf("f1 и f2 НЕ равны \n");
		if (f3 != f1)
			printf("f3 и f1 НЕ равны \n"); //correct
		else
			printf("f3 и f1 равны \n");
		if (f3 > f4)
			printf("f3 больше f4 \n"); //correct
		else
			printf("f3 меньше или равно f4 \n");
		if (f1 <= f2)
			printf("f1 меньше или равно f2 \n"); //correct
		else
			printf("f1 больше f2 \n");

		Fraction fTest(1, 1);
		fTest = f3 - f1; // 1\12
		fTest.print();
		std::cout << std::endl;
		fTest = fTest + f4; // 4\12
		fTest.print();
		std::cout << std::endl;
		fTest = fTest * f2; // 8\96
		fTest.print();
		std::cout << std::endl;
		fTest = fTest / f3; // 24\96
		fTest.print();
		std::cout << std::endl;

		std::cout << -f2.getNum() << "/" << f2.getDen() << std::endl;
	}

	std::cout << "Task 4" << std::endl;

	{
		Card c1(six, spades, 0);
		Card c2(king, hearts);
		std::cout << c1.GetValue() << std::endl;
		std::cout << c2.GetValue() << std::endl;
	}
	return 0;
}
