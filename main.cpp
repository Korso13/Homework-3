#include <iostream>
#include <cmath>

#define PI 3.14159265358979323846

struct Coord
{
  int x{0};
  int y{0};
}

class Figure
{
  public:
  Figure() virtual {}
  
  int virtual area() = 0;
};

class Circle : public Figure
{
private:
int radius;

public:
Circle(int rad) : radius(rad) {}

int area() overrride {return (radius * radius * PI);}
};

class Parallelogram : public Figure
{
private:
Coord a, b, c, d;  //ab - верхняя грань, bc - правая грань и т.д.

public:
Parallelogram(int ax, ay, bx, by, cx, cy, dx, dy) : a.x(ax), a.y(ay), b.x(bx), b.y(by), c.x(cx), c.y(cy), d.x(dx), d.y(dy) virtual {}

int area() overrride {return (a.y - d.y) * sqrt((c.x - d.x) + (c.y - d.y));} //высота параллелограмма * на нижнюю грань. Верно для всех дочерних классов кроме квадрата.
};

class Rectangle : public Parallelogram
{
};

class Square : public Parallelogram
{
};

class Rhombus : public Parallelogram
{
};


int main()
{
  
  
  return 0;
}
