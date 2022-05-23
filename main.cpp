#include <iostream>

class Figure
{
  public:
  Figure() virtual {}
  
  int virtual area() = 0;
};

class Circle : public Figure
{
private:
double radius;

public:
Circle() : {}

int area() overrride {}
};

class Parallelogram : public Figure
{
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
