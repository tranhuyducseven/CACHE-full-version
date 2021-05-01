#include <iostream>
using namespace std;
enum Color
{
    red,
    green,
    blue
};
enum Size
{
    small,
    medium,
    big
};

class Toy
{
protected:
    double price;

public:
    Toy(double price)
    {
        this->price = price;
    }

    virtual void printType() = 0;
    friend class ToyBox;
};

class CarToy : public Toy
{
private:
    Color color;

public:
    CarToy(double price, Color color) : Toy(price)
    {
        this->price = price;
        this->color = color;
    }

    void printType()
    {
        cout << "This is a car toy\n";
    }

    friend class ToyBox;
};

class PuzzleToy : public Toy
{
private:
    Size size;

public:
    PuzzleToy(double price, Size size) : Toy(price)
    {
        this->price = price;
        this->size = size;
    }

    void printType()
    {
        cout << "This is a puzzle toy\n";
    }

    friend class ToyBox;
};

class ToyBox
{
private:
    Toy *toyBox[5];
    int numberOfItems;

public:
    ToyBox()
    {
        for (int i = 0; i < 5; i++)
        {
            this->toyBox[i] = nullptr;
        }
        this->numberOfItems = 0;
    }

    int addItem(const CarToy &carToy)
    {
        if (numberOfItems == 5)
            return -1;
        else if (numberOfItems < 5)
        {
            for (int i = 0; i<5; i++)
            {
                if (toyBox[i] == nullptr)
                {
                toyBox[i] = new CarToy(carToy.price, carToy.color);
                numberOfItems++;
                break;
                }
            }
        }
        return numberOfItems;
    }

    int addItem(const PuzzleToy &puzzleToy)
    {
        if (numberOfItems == 5)
        {
            return -1;
        }
        else if (numberOfItems < 5)
        {
            for (int i = 0; i < 5; i++)
            {
                if (toyBox[i] == nullptr)
                {
                    toyBox[i] = new PuzzleToy(puzzleToy.price, puzzleToy.size);
                    numberOfItems++;
                    break;
                }
            }
        }
        return numberOfItems;
    }

    void printBox()
    {
        for (int i = 0; i < numberOfItems; i++)
            toyBox[i]->printType();
    }
    ~ToyBox()
    {
        for (int i = 0; i < 5; i++)
        {
            delete toyBox[i];
        }
    }
};
int main()
{
    CarToy car(20000, red);
    PuzzleToy puzzle(30000, small);

    ToyBox box;
    box.addItem(car);
    box.addItem(puzzle);
    box.printBox();
    return 0;
}