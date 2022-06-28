#include <cstdlib>

int GetExpo(int number, int expo) //функция для возведения в степень
{
    int res{ 1 };
    if (expo == 0)
        return res;
    else if (expo > 0)
    {
        for (int j = 0; j < expo; j++)
        {
            res = res * number;
        }
        return res;
    }
    else if (expo < 0)
    {
        res = 1 / GetExpo(number, std::abs(expo));
        return res;
    }

}