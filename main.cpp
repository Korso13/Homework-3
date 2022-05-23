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
  
  virtual int area() = 0;
};

class Circle final : virtual public Figure 
{
private:
int radius;

public:
Circle(int rad) : radius(rad) {}

int area() override {return (radius * radius * PI);}
};

class Parallelogram : virtual public Figure
{
protected:
Coord a{0,0}, b, c, d;  //ab - верхняя грань, bc - правая грань и т.д.

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

int area() override {return ((a.y - d.y) * sqrt((c.x - d.x) + (c.y - d.y)));} //высота параллелограмма * на нижнюю грань. Верно для так же для ромба.
};

class Rectangle final : virtual public Parallelogram
{
public:
Rectangle(int ax, int ay, int bx, int by, int cx, int cy, int dx, int dy) : Parallelogram(a.x, a.y, b.x, b.y, c.x, c.y, d.x, d.y) {};

int area() override {return ((a.y - d.y) * (c.x - d.x));}
};

class Rhombus final : virtual public Parallelogram
{
public:
Rhombus(int ax, int ay, int bx, int by, int cx, int cy, int dx, int dy) : Parallelogram(a.x, a.y, b.x, b.y, c.x, c.y, d.x, d.y) {};
};

class Square final : virtual public Parallelogram
{
public:
Square(int ax, int ay, int bx, int by, int cx, int cy, int dx, int dy) : Parallelogram(a.x, a.y, b.x, b.y, c.x, c.y, d.x, d.y) {};

int area() override {return ((b.x-a.x) * (b.x-a.x));}
};

//========================================================================================================================================
//Task 2.
//========================================================================================================================================

int main()
{
  
  
  return 0;
}
