#include <iostream>
#include <vector>
#include <queue>
using namespace std;
bool isBipartite(vector<vector<int>> G)
{
    int src = 0;
    int size = G.size();
    int *colorArr = new int[size];
    for (int i = 0; i < size; ++i)
        colorArr[i] = -1;
    colorArr[src] = 1;
    queue<int> q;
    q.push(src);
    while (!q.empty())
    {     
        int u = q.front();
        q.pop();
        if (G[u][u] == 1)
            return false;
        for (int v = 0; v < size; ++v)
        {
            if (G[u][v] && colorArr[v] == -1)
            {       
                colorArr[v] = 1 - colorArr[u];
                q.push(v);
            }
            else if (G[u][v] && colorArr[v] == colorArr[u])
                return false;
        }
    }
    delete[] colorArr;
    return true;
}

int main()
{
    int G[4][4] = {{0, 1, 0, 1}, {1, 0, 1, 0}, {0, 1, 0, 1}, {1, 0, 1, 0}};
    int n = 4;

    vector<vector<int>> graph(4, vector<int>());
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (G[i][j])
                graph[i].push_back(j);
        }
    }

    isBipartite(graph) ? cout << "Yes" : cout << "No";
    return 0;
}