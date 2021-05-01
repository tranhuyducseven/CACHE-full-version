#include <iostream>
#include <string>
#include <string.h>
using namespace std;

class Book
{
private:
    char *title;
    char *authors;
    int publishingYear;

public:
    Book()
    {
        char a[] = "     ";
        (this->title) = a;
        this->authors = a;
        this->publishingYear = 0;
    }

    Book(const char *title, const char *authors, int publishingYear)
    {
        this->title = const_cast<char *>(title);
        this->authors = const_cast<char *>(authors);
        this->publishingYear = publishingYear;
    }
    char *getAuthors()
    {
        return this->authors;
    }
    friend bool checkAuthor(Book book, const char *author)
    {
        bool check = false;

        int a = strlen(book.getAuthors());
        int b = strlen(author);

        for (int i = 0; i < a; i++)
        {

            if (book.getAuthors()[i] == author[0])
            {
                if ((i == 0) || (i > 2 && book.getAuthors()[i - 1] == ' ' && book.getAuthors()[i - 2] == ','))
                {
                    bool check = true;
                    for (int j = 0; j < b; j++)
                    {

                        if (book.getAuthors()[i + j] != author[j])
                        {
                            check = false;
                            break;
                        }
                    }
                    if (check == true)
                    {
                        if (book.getAuthors()[i + b] == '\0' || book.getAuthors()[i + b] == ',')
                            return check;
                        else
                            check = false;
                        return check;
                    }
                }
            }
        }
        return check;
    }
    ~Book() {}
};

int main()
{

    Book book1("Giai tich 1", "Nguyen Dinh Huy, Nguyen Thi Xuan Anh", 2000);
    cout << checkAuthor(book1, "uyen Thi Xuan Anh");
    return 0;
}