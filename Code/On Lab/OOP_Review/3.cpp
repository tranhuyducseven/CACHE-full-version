#include <iostream>
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

    Circle(const Circle &circle)
    {
        this->center = circle.center;
        this->radius = circle.radius;
    }

    void setCenter(Point point)
    {
        (this->center).setX(point.getX());
        (this->center).setY(point.getY());
    }

    void setRadius(double radius)
    {
        this->radius = radius;
    }

    Point getCenter() const
    {
        return this->center;
    }

    double getRadius() const
    {
        return this->radius;
    }

    void printCircle()
    {
        printf("Center: {%.2f, %.2f} and Radius %.2f\n", this->center.getX(), this->center.getY(), this->radius);
    }
};