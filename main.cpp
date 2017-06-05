#include <iostream>
#include <limits.h>
#include <string.h>  // �������� '.h' ��� vs
#include <queue>
#include <windows.h>
using namespace std;

// ʳ������ ������ � ������ �����
#define V 6

/* ������� true ���� � ���� �� 's' �� 't' �
���������� ����. ����� �������� parent[] ��� �������� ���� */
bool bfs(int rGraph[V][V], int s, int t, int parent[])
{
    // �������� ����� �������� � ��������� �� ������� �� �� ������
    bool visited[V];
    memset(visited, 0, sizeof(visited));

    // �������� �����, ���������� � ����� ������� ������� � ���� ������� ������� �� ������
    queue <int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    // ����� � ������
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

// ������� ������������ ���� �� s �� t � ������ �������
int fordFulkerson(int graph[V][V], int s, int t)
{
    int u, v;

    // ��������� ����������� ����� � ��������� ���������� ���� �
    // � ����������� ���������� � ����� ��������� ����� ���������� �����������
    // � ����������� �����
    int rGraph[V][V]; // ���������� ���� �� rGraph[i][j] �����
    // ��������� ������ ����� �� i �� j (���� ����
    // �����. ���� rGraph[i][j] ������� 0, �� ����)
    for (u = 0; u < V; u++)
        for (v = 0; v < V; v++)
            rGraph[u][v] = graph[u][v];

    int parent[V]; // ��� ����� ������������ ������� � ������ � ������ ����

    int max_flow = 0;

    // �������� ���� ���� ��� ���� �� ������� �� ��������
    while (bfs(rGraph, s, t, parent))
    {
        // ������ ������������ ���� ����� ��������� ����
        int path_flow = INT_MAX;
        for (v = t; v != s; v = parent[v])
        {
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }

        // ������� �������� ��������� ����� �
        // ��������� ���� ������ �����
        for (v = t; v != s; v = parent[v])
        {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }

        // ������ ���� ����� �� ���������� ������
        max_flow += path_flow;
    }

    // ������� ��������� ����
    return max_flow;
}

// ������ ������� ����
int main()
{
    // ��������� ���� ��� Visual Studio
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    cout << "                                                  _\n"
            "  ___ ___  _   _ _ __ ___  _____      _____  _ __| | __\n"
            " / __/ _ \\| | | | '__/ __|/ _ \\ \\ /\\ / / _ \\| '__| |/ /\n"
            "| (_| (_) | |_| | |  \\__ \\  __/\\ V  V / (_) | |  |   <\n"
            " \\___\\___/ \\__,_|_|  |___/\\___| \\_/\\_/ \\___/|_|  |_|\\_\\"
         << endl ;
    cout << string(47, ' ') + "@vovawed" << endl << endl;

    cout << "1) ���������� ��� �������� ������" << endl
         << "2) ��������� ��������� ��������" << endl
         << "3) �����" << endl;

    short num;

    do {
        cout << "������ �����: ";
        cin >> num;
        switch (num) {
            case 1:
                cout << "����������� ������������� ������ �� ������� �����-����������" << endl
                     << "ϳ��������: ����� ���������" << endl
                     << "������������� ������ ���" << endl
                     << endl;
            case 2:
                break;
            case 3:
                cout << "�����" << endl;
                return 0;
            default:
                cout << "�� ����� ���, ��������� �� ���" << endl;
        }
    } while (num != 2);

    // �������
    int graph[V][V] = {
            { 0, 16, 13, 0, 0, 0 },
            { 0, 0, 10, 12, 0, 0 },
            { 0, 4, 0, 0, 14, 0 },
            { 0, 0, 9, 0, 0, 20 },
            { 0, 0, 0, 7, 0, 4 },
            { 0, 0, 0, 0, 0, 0 }
    };

    cout << "����������� �������� ����: " << fordFulkerson(graph, 0, 5) << endl;

    system("pause");

    return 0;
}
