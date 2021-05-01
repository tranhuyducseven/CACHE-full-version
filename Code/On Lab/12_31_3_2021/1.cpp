
///  NHO DOI TEN BIEN
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

int baseballScore(string ops){
stack <int> listPoint;
    int sum = 0;
    for (int i = 0; i < (int) ops.size(); i++)
    {
        if (ops[i] >= '0' && ops[i] <= '9')
            listPoint.push(ops[i] - '0');
        else if (ops[i] == 'C')
            listPoint.pop();
        else if (ops[i] == 'D')
            listPoint.push(2 * listPoint.top());
        else if (ops[i] == '+')
        {
            int firstScore = listPoint.top(); // 1st remove
            listPoint.pop();
            int secondScore = listPoint.top(); // 2nd remove
            int sumScore = firstScore + secondScore;
            // put from 1st -> sumScore
            listPoint.push(firstScore);
            listPoint.push(sumScore);
        }
    }
    while (!listPoint.empty())
    {
        sum += listPoint.top();
        listPoint.pop();
    }
    return sum;

}