#include <iostream>
using namespace std;
// Given a non-empty text and a pattern, implement a recursive function

// bool containsPattern(char* text, char* pattern){}
// that returns true if pattern is present in text, otherwise false.

// Note: Please note that you can't using key work for, while, goto (even in variable names, comment).
bool exactPattern(char *text, char *pattern)
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
bool containsPattern(char *text, char *pattern)
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

    cout <<containsPattern((char *)"Dai hoc Bach Khoa", (char *)"Bach Khoa");
    return 0;
}