
///  NHO DOI TEN BIEN
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

int trap(vector<int> &height)
{
    if ((int)height.size() == 0)
        return 0;
    vector<int> temp = height;
    for (int i = 0; i < (int)temp.size() - 1; i++)
    {
        for (int j = i + 1; j < (int)temp.size(); j++)
        {
            if (temp[i] < temp[j])
            {
                int x = temp[j];
                temp[j] = temp[i];
                temp[i] = x;
            }
        }
    }
    stack<int> listHeight;
    for (int i = 0; i < (int)temp.size(); i++)
    {
        if (listHeight.empty() && temp[i] > 0)
            listHeight.push(temp[i]);
        else if (!listHeight.empty() && temp[i] < listHeight.top() && temp[i] != 0)
            listHeight.push(temp[i]);
    }
    if ((int)listHeight.size() == 0)
        return 0;
    int sum = 0, begin = -1, k = listHeight.top();
    int sizeInitStack = (int)listHeight.size();
    while (!listHeight.empty())
    {
        begin = -1;
        int u = listHeight.top();
        k = ((int)listHeight.size() == sizeInitStack) ? k : u - k;
        for (int i = 0; i < (int)height.size(); i++)
        {
            if (height[i] >= u && begin == -1)
                begin = i;
            else if (height[i] >= u && begin != -1)
            {
                sum += (k * (i - begin - 1));
                begin = i;
            }
        }
        k = u;
        listHeight.pop();
    }
    return sum;
}