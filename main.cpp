#include <iostream>
#include <limits.h>
#include <string.h>
#include <queue>
#include <windows.h>
using namespace std;

// Кількість вершин в даному графі
#define V 6

/* Повертає true якщо є шлях від 's' до 't' в
залишковий граф. Також заповнює parent[] щоб зберегти шлях */
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
    int rGraph[V][V]; // Залишковий граф де rGraph[i][j] вказує
    // залишкову ємність ребра від i до j (якщо існує
    // ребро. Якщо rGraph[i][j] дорівнює 0, то немає)
    for (u = 0; u < V; u++)
        for (v = 0; v < V; v++)
            rGraph[u][v] = graph[u][v];

    int parent[V]; // Цей масив заповнюється пошуком в ширину і зберігає шлях

    int max_flow = 0;

    // Збільшити потік поки йде шлях від джерела до приймача
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

        // Оновити залишкові можливості ребер і
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

void run()
{
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
}

void programMenu()
{
    cout << "1) Інформація про курсовий проект" << endl
         << "2) Запустити виконання програми" << endl
         << "3) Вихід" << endl;

    short num;
    cout << "Введіть число: "; cin >> num;

    switch (num) {
        case 1:
            cout << "Алгоритм або метод Форда-Фалкерсона знаходить максимальний потік у транспортній мережі. "
                    "Метод Форда-Фалкерсона - метод, який базується на трьох концепціях: залишкові мережі,"
                    " шляхи що збільшуються і розрізи. Ключову роль у методі Форда-Фалкерсона грають два поняття:"
                    " залишкові мережі і доповнюють шляху.  Дані концепції лежать в основі важливої теореми про"
                    " максимальний потік і мінімальний розріз, яка визначає значення максимального нащадка за допомогою"
                    " розрізів траспортної мережі." << endl << endl;
            programMenu();  // Запуск ще раз меню
            break;
        case 2:
            run();
            break;
        case 3:
            cout << "Вихід" << endl;
            break;
        default:
            cout << "Не вірний ввід, спробуйте ще раз" << endl;
            programMenu();  // Запуск ще раз меню
    }
}

// Запуск функцій вище
int main()
{
    // Українська мова для Visual Studio
    // SetConsoleCP(1251);
    // SetConsoleOutputCP(1251);

    cout << "                                                  _\n"
            "  ___ ___  _   _ _ __ ___  _____      _____  _ __| | __\n"
            " / __/ _ \\| | | | '__/ __|/ _ \\ \\ /\\ / / _ \\| '__| |/ /\n"
            "| (_| (_) | |_| | |  \\__ \\  __/\\ V  V / (_) | |  |   <\n"
            " \\___\\___/ \\__,_|_|  |___/\\___| \\_/\\_/ \\___/|_|  |_|\\_\\"
         << endl ;
    cout << string(47, ' ') + "@vovawed" << endl << endl;

    programMenu();

    // ("pause"); Для Visual Studio

    return 0;
}