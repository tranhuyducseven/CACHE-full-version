#include <iostream>
#include <queue>
using namespace std;
void bfs(vector<vector<int>> graph, int start)
{
    int N = (int)graph.size();
    int space = 0;
    bool *visited = new bool[N];
    for (int i = 0; i < N; i++)
    {
        visited[i] = false;
    }
    queue<int> queue;
    queue.push(start);

    while (!queue.empty())
    {
        start = queue.front();
        if (!visited[start])
        {
            if (space != 0)
                cout << " ";
            else
                space = 1;
            cout << start ;
            visited[start] = true;
        }
        queue.pop();
        int n = (int)graph[start].size();
        for (int i = 0; i < n; i++)
        {
            if (!visited[graph[start][i]])
                queue.push(graph[start][i]);
        }
    }
}
int main()
{

    int init_graph[10][10] = {{0, 1, 1, 0, 1, 0, 1, 0, 1, 0},
                              {0, 0, 1, 1, 0, 0, 0, 1, 0, 0},
                              {0, 1, 0, 0, 0, 1, 1, 0, 1, 1},
                              {1, 0, 0, 0, 0, 0, 0, 1, 0, 0},
                              {0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
                              {1, 0, 1, 0, 1, 0, 0, 0, 1, 0},
                              {0, 0, 1, 1, 0, 1, 0, 0, 0, 0},
                              {1, 0, 0, 0, 0, 1, 1, 0, 1, 0},
                              {0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
                              {1, 0, 1, 0, 1, 0, 0, 0, 1, 0}};
    int n = 10;
    vector<vector<int>> graph(n, vector<int>());
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (init_graph[i][j])
                graph[i].push_back(j);
        }
    }
    bfs(graph,0);
}