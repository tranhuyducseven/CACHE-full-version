#include <iostream>
#include <math.h>
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
        return this->y;
    }
};

class Circle
{
private:
    Point center;
    double radius;

public:
    Circle()
    {
        this->center = Point(0, 0);
        this->radius = 0;
    }

    Circle(Point center, double radius)
    {
        this->center = center;
        this->radius = radius;
    }
    double distanceToPoint(const Point &pointA)
    {
        return sqrt(pow(this->center.getX() - pointA.getX(), 2) + pow(this->center.getY() - pointA.getY(), 2));
    }

    bool containsPoint(const Point point)
    {
        if (this->distanceToPoint(point) < this->radius)
        {
            return true;
        }
        else
            return false;
    }

    bool containsTriangle(const Point pointA, const Point pointB, const Point pointC)
    {
        if ((this->distanceToPoint(pointA) < this->radius) && (this->distanceToPoint(pointB) < this->radius) && (this->distanceToPoint(pointC) < this->radius))
            return true;
        else
            return false;
    }
};
int main()
{
    Point pointO(0, 0);
    Point point1(1, 0), point2(-1, 0), point3(0, 3);
    Circle A = Circle(pointO, 3);
    cout << A.containsTriangle(point1, point2, point3);
}