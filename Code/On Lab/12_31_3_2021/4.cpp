///  NHO DOI TEN BIEN
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

string removeDuplicates(string S)
{
    //aab
    stack<char> str;
    for (int i = 0; i < (int)(S.length()); i++)
    {
        char c = S[i];
        if (!str.empty() && c == str.top())
        {
            str.pop();
        }
        else
        {
            str.push(c);
        }
    }
    
    string reverse = "";
    while (!str.empty())
    {
        reverse += str.top();
        str.pop();
    }
    for (int i = 0; i <(int)( reverse.length()); i++)
    {
        str.push(reverse[i]);
    }
    string result = "";
    while (!str.empty())
    {
        result += str.top();
        str.pop();
    }
    return result;
}