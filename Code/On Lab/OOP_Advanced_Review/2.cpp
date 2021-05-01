#include <iostream>
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
        this->title = nullptr;
        this->authors = nullptr;
        this->publishingYear = 0;
    }

    Book(const char *title, const char *authors, int publishingYear)
    {
        memcpy(this->title,title,sizeof(title));
        this->authors = const_cast<char *>(authors);
        this->publishingYear = publishingYear;
    }

    Book(const Book &book)
    {
        this->title = book.title;
        this->authors = book.authors;
        this->publishingYear = book.publishingYear;
    }

    void setTitle(const char *title)
    {
        this->title = const_cast<char *>(title);
    }

    void setAuthors(const char *authors)
    {
        this->authors = const_cast<char *>(authors);
    }

    void setPublishingYear(int publishingYear)
    {
        this->publishingYear = publishingYear;
    }

    char *getTitle() const
    {
        return this->title;
    }

    char *getAuthors() const
    {
        return this->authors;
    }

    int getPublishingYear() const
    {
        return this->publishingYear;
    }

    ~Book()
    {
    }

    void printBook()
    {
        printf("%s\n%s\n%d", this->title, this->authors, this->publishingYear);
    }
};
int main()
{

    Book book1("Giai tich 1", "Nguyen Dinh Huy", 2000);
    book1.printBook();

    return 0;
}