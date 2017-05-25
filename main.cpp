#include <iostream>
#include <limits.h>
#include <string.h>
#include <queue>
#include <windows.h>
using namespace std;

// Кількість вершин в даному графі
#define V 6

/* Повертає true якщо є шлях від 's' до 't' в
залишковий граф. Nакож заповнює parent[] щоб зберегти шлях */
bool bfs(int rGraph[V][V], int s, int t, int parent[])
{
    // Створити масив відвіданих і позначити всі вершини які не відвідані
    bool visited[V];
    memset(visited, 0, sizeof(visited));

    // Створити чергу, поставлене в чергу джерело вершини і мітки джерела вершини як відвідані
    queue <int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    // Пошук в ширину
    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (int v = 0; v<V; v++)
        {
            if (!visited[v] && rGraph[u][v] > 0)
            {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }

    return visited[t];
}

// Повертає максимальний потік від s до t в даному графіку
int fordFulkerson(int graph[V][V], int s, int t)
{
    int u, v;

    // Створення залишкового графа і заповнити залишковий граф з
    // з урахуванням потенціалу в якості вихідного графа залишкових потужностей
    // в залишковому графі
    int rGraph[V][V]; // Residual graph where rGraph[i][j] indicates
    // residual capacity of edge from i to j (if there
    // is an edge. If rGraph[i][j] is 0, then there is not)
    for (u = 0; u < V; u++)
        for (v = 0; v < V; v++)
            rGraph[u][v] = graph[u][v];

    int parent[V]; // Цей масив заповнюється пошуком в ширину і зберігає шлях

    int max_flow = 0;

    // Augment the flow while tere is path from source to sink
    while (bfs(rGraph, s, t, parent))
    {
        // Find minimum residual capacity of the edges along the
        // path filled by BFS. Or we can say find the maximum flow
        // through the path found.
        int path_flow = INT_MAX;
        for (v = t; v != s; v = parent[v])
        {
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }

        // Оновити залишкові можливості країв і
        // зворотний край уздовж шляху
        for (v = t; v != s; v = parent[v])
        {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }

        // Додати потік шляху до загального потоку
        max_flow += path_flow;
    }

    // Повертає загальний потік
    return max_flow;
}

// Запуск функцій вище
int main()
{
    // Українська мова для Visual Studio
    // SetConsoleCP(1251);
    // SetConsoleOutputCP(1251);

    cout << "// Знаходження максимального потоку за методом Форда-Фалкерсона" << endl;
    cout << "// Автор: Пицюк Володимир (vovawed.github.io)" << endl;
    cout << endl;

    // Матриця
    int graph[V][V] = {
            { 0, 16, 13, 0, 0, 0 },
            { 0, 0, 10, 12, 0, 0 },
            { 0, 4, 0, 0, 14, 0 },
            { 0, 0, 9, 0, 0, 20 },
            { 0, 0, 0, 7, 0, 4 },
            { 0, 0, 0, 0, 0, 0 }
    };

    cout << "Максимально можливий потік: " << fordFulkerson(graph, 0, 5) << endl;

    // ("pause"); Для Visual Studio

    return 0;
}