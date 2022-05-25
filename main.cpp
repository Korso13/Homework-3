#include <iostream>
#include <cmath>

#define PI 3.14159265358979323846

struct Coord
{
  int x{0};
  int y{0};
};

//========================================================================================================================================
//Task 1. Figures (check overriding type of return value in area methods)
//========================================================================================================================================

class Figure //base class
{
  public:
  Figure() {}
  
  virtual double area() = 0;
};

class Circle final : virtual public Figure 
{
private:
int radius;

public:
Circle(int rad) : radius(rad) {}

double area() override {return (radius * radius * PI);}
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

double area() override {return ((a.y - d.y) * sqrt((c.x - d.x) + (c.y - d.y)));} //высота параллелограмма * на нижнюю грань. Верно для так же для ромба.
};

class Rectangle final : virtual public Parallelogram
{
public:
Rectangle(int ax, int ay, int bx, int by, int cx, int cy, int dx, int dy) : Parallelogram(a.x, a.y, b.x, b.y, c.x, c.y, d.x, d.y) {};

double area() override {return ((a.y - d.y) * (c.x - d.x));}
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

double area() override {return ((b.x-a.x) * (b.x-a.x));}
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

/*
- Создать класс: Fraction (дробь). Дробь имеет числитель и знаменатель (например, 3/7 или 9/2). 
- Предусмотреть, чтобы знаменатель не был равен 0. 
Перегрузить:
- математические бинарные операторы (+, -, *, /) для выполнения действий с дробями
- унарный оператор (-)
- логические операторы сравнения двух дробей (==, !=, <, >, <=, >=).
Примечание: Поскольку операторы < и >=, > и <= — это логические противоположности, попробуйте перегрузить один через другой.

- Продемонстрировать использование перегруженных операторов.
*/

int main()
{
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

	//========================================================================================================================================
	//Task 3. Перегрузка операторов
	//========================================================================================================================================
	
	{

	}

  return 0;
}
