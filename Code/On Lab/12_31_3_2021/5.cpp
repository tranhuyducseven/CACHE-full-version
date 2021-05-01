///  NHO DOI TEN BIEN
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool isValidParentheses(string s)
{
    stack<char> str;
    char x;

    // Traversing the session
    for (int i = 0; i < (int)(s.length()); i++)
    {
        if (s[i] == '(' || s[i] == '[' || s[i] == '{')
        {

            str.push(s[i]);
            continue;
        }

        if (str.empty())
            return false;

        switch (s[i])
        {
        case ')':

            x = str.top();
            str.pop();
            if (x == '{' || x == '[')
                return false;
            break;

        case '}':

            x = str.top();
            str.pop();
            if (x == '(' || x == '[')
                return false;
            break;

        case ']':

            x = str.top();
            str.pop();
            if (x == '(' || x == '{')
                return false;
            break;
        }
    }

    return (str.empty());
}