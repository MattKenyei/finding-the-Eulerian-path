
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// ��������� ������ ��� �������� ����� �����
struct Edge 
{
    int src, dest;
};

// ����� ��� ������������� �����
class Graph
{
public:

    // ������ �������� ��� ������������� ������ ���������
    vector<vector<int>> adjList;

    // ����������� Graph
    Graph(vector<Edge> const& edges, int n)
    {
        // �������� ������ �������, ����� �� �������� n ���������
        adjList.resize(n);

        // ��������� ����� � ����������������� graph
        for (auto& edge : edges)
        {
            adjList[edge.src].push_back(edge.dest);
            adjList[edge.dest].push_back(edge.src);
        }
    }
};

// ������� ��� ������ DFS �� �����
void DFS(Graph const& graph, int v, vector<bool>& visited)
{
    // �������� ������� ���� ��� ����������
    visited[v] = true;

    // ������ ��� ������� ����� (v, u)
    for (int u : graph.adjList[v])
    {
        if (!visited[u]) 
            DFS(graph, u, visited);
    }
}

// ������� ��� ��������, ��� �� ������� � ��������� �������� � �����
// ����������� ������ ���������� ����������
bool isConnected(Graph const& graph, int n)
{
    // ����� �����������, �������� �� ������� ��� ���
    vector<bool> visited(n);

    // ��������� ����� � ������� � ������ ������� � ��������� ��������
    for (int i = 0; i < n; i++)
    {
        if (graph.adjList[i].size())
        {
            DFS(graph, i, visited);
            break;
        }
    }

    // ���� ���� ����� DFS �� ����� �������� ��� ������� � ��������� ��������,
    // graph �������� ����� ����� ���������� ���������
    for (int i = 0; i < n; i++)
    {
        if (!visited[i] && graph.adjList[i].size() > 0) {
            return false;
        }
    }

    return true;
}

// ��������������� ������� ��� �������� ������ ���������� ������ � �������� ��������
// �� �����
int countOddVertices(Graph const& graph)
{
    int count = 0;
    for (vector<int> list : graph.adjList)
    {
        if (list.size() & 1) {
            count++;
        }
    }
    return count;
}
void printEulerPath(Graph const& graph, int u, vector<bool>& visited)
{
    for (int v : graph.adjList[u])
    {
        if (!visited[v])
        {
            visited[v] = true;
            cout << u << " - " << v << " ";
            printEulerPath(graph, v, visited);
        }
    }
}
int main()
{
    vector<Edge> edges = 
    {
        {{0, 1}, {0, 3}, {1, 2}, {1, 3}, {1, 4}, {2, 3}, {3, 4}}
    };

    // ����� ���������� ����� � �����
    int n = 5;

    // ������� ����������������� ���� �� �������� �����
    Graph graph(edges, n);

    // ���������, ����������� �� ��� ������� � ��������� �������� ������
    // ������������ ���������
    bool is_connected = isConnected(graph, n);

    // ������� ����� ���������� ������ � �������� ��������
    int odd = countOddVertices(graph);

    // ������� ���� ����������, ���� ��� ������� �� ������� ������� ���������,
    // � ���� ��� ��� ������� ����� �������� �������

    if (is_connected && (odd == 0 || odd == 2))
    {
        cout << "The graph has an Eulerian path: ";

        int start_vertex = 0;
        for (int i = 0; i < n; i++)
        {
            if (graph.adjList[i].size() & 1)
            {
                start_vertex = i;
                break;
            }
        }

        vector<bool> visited(n);
        visited[start_vertex] = true;
        printEulerPath(graph, start_vertex, visited);

        cout << endl;
    }
    else {
        cout << "The Graph is not Eulerian" << endl;
    }

    return 0;
}