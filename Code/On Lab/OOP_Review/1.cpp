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
    double getX()
    const
    {
        return this->x;
    }
    double getY()
    const
    {
        return this->y;
    }
  
    Point operator=(const Point &p)
    {
        Point temp;
        temp.x = p.x;
        temp.y = p.y;
        return temp;
    }
   

    ~Point(){};
};


class Circle
{
private:
    Point center;
    double radius;

public:
    Circle()
    {
       this->center=Point(0,0);
       this->radius=0;
    }

    Circle(Point center, double radius)
    {
        this->center = center;
        this->radius = radius;
    }

    void operator=(const Circle &circle)
    {
        this->center = circle.center;
        this->radius = circle.radius;
    }

    bool operator==(const Circle &circle)
    {
        return this->center.getX()==circle.center.getX()&&this->center.getY()==circle.center.getY()&&this->radius==circle.radius;
      
    }

    friend istream &operator>>(istream &in, Circle &circle)
    {
        double x,y;
        in>>x>>y;
        circle.center = Point(x,y);
        in>>circle.radius;
        return in;
    }

    void printCircle()
    {
        printf("Center: {%.2f, %.2f} and Radius %.2f\n", this->center.getX(), this->center.getY(), this->radius);
    }
    ~Circle(){};
   
};
int main()
{
    Point pointO(0, 0);
    Circle A = Circle(pointO, 3);
    Circle B;
    B = A;
    cout << (B == A) << endl;
    cin >> A;
    A.printCircle();
    return 0;
}