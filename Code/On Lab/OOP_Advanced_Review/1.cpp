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
        this->title = const_cast<char *>(title);
        this->authors = const_cast<char *>(authors);
        this->publishingYear = publishingYear;
    }

    ~Book() {}

 
};

bool exactPattern(char *text, const char *pattern)
{

    {
        //pattern has more character => return false;
        if (*text == '\0' && *pattern != '\0')
            return false;
        //pattern is null
        if (*pattern == '\0')
            return true;
        if (*text == *pattern)
            //Test while got last character.
            return exactPattern(text + 1, pattern + 1);
        return false;
    }
}
bool containsPattern(char *text, const char *pattern)
{
    if (*text == '\0')
        return false;
    if (*text == *pattern)
    {
        if (exactPattern(text, pattern))
            return true;
        else
            return containsPattern(text + 1, pattern);
            
    }
      return containsPattern(text+1, pattern);       
}
int main()
{
     Book book1("Giai tich 1", "Nguyen Dinh Huy", 2000);
    Printer::printBook(book1);
    
    return 0;
}