#include <bits/stdc++.h>
using namespace std;
class Point
{
private:
    double x, y;

public:
    Point()
    {
        this->x = 0;
        this->y = 0;
    }

    Point(double x, double y)
    {
        this->x = x;
        this->y = y;
    }

    void setX(double x)
    {
        this->x = x;
    }

    void setY(double y)
    {
        /* 
         * STUDENT ANSWER
         */
        this->y = y;
    }

    double getX() const
    {
        return this->x;
    }

    double getY() const
    {
        return this->y; /*  
         * STUDENT ANSWER
         */
    }

    double distanceToPoint(const Point &pointA)
    {
        return sqrt(pow(this->getX() - pointA.getX(), 2) + pow(this->getY() - pointA.getY(), 2));
    }
};
int main()
{
    Point A(2, 3);
    Point B(1, 1);
    cout << pow(A.distanceToPoint(B), 2);
    return 0;
}