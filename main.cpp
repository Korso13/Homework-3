#include <iostream>
#include <cmath>

#define PI 3.14159265358979323846

struct Coord
{
  int x{0};
  int y{0};
}

//========================================================================================================================================
//Task 1. Figures (check overriding type of return value in area methods)
//========================================================================================================================================

class Figure
{
  public:
  Figure() virtual {}
  
  int virtual area() = 0;
};

class Circle : public final Figure
{
private:
int radius;

public:
Circle(int rad) : radius(rad) {}

double area() overrride {return (radius * radius * PI);}
};

class Parallelogram : public Figure
{
protected:
Coord a, b, c, d;  //ab - верхняя грань, bc - правая грань и т.д.

public:
Parallelogram(int ax, ay, bx, by, cx, cy, dx, dy) : a.x(ax), a.y(ay), b.x(bx), b.y(by), c.x(cx), c.y(cy), d.x(dx), d.y(dy) virtual {}

double area() overrride {return ((a.y - d.y) * sqrt((c.x - d.x) + (c.y - d.y)));} //высота параллелограмма * на нижнюю грань. Верно для так же для ромба.
};

class Rectangle : public final Parallelogram
{
public:
Rectangle(int ax, ay, bx, by, cx, cy, dx, dy) : Parallelogram(a.x, a.y, b.x, b.y, c.x, c.y, d.x, d.y) {};

int area() overrride {return ((a.y - d.y) * (c.x - d.x));}
};

class Rhombus : public final Parallelogram
{
public:
Rhombus(int ax, ay, bx, by, cx, cy, dx, dy) : Parallelogram(a.x, a.y, b.x, b.y, c.x, c.y, d.x, d.y) {};
};


class Square : public final Parallelogram
{
public:
Square(int ax, ay, bx, by, cx, cy, dx, dy) : Parallelogram(a.x, a.y, b.x, b.y, c.x, c.y, d.x, d.y) {};

int area() overrride {return ((b.x-a.x) * (b.x-a.x));}
};

//========================================================================================================================================
//Task 2.
//========================================================================================================================================

int main()
{
  
  
  return 0;
}
