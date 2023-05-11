
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Структура данных для хранения ребра графа
struct Edge 
{
    int src, dest;
};

// Класс для представления графа
class Graph
{
public:

    // вектор векторов для представления списка смежности
    vector<vector<int>> adjList;

    // Конструктор Graph
    Graph(vector<Edge> const& edges, int n)
    {
        // изменить размер вектора, чтобы он содержал n элементов
        adjList.resize(n);

        // добавляем ребра в неориентированный graph
        for (auto& edge : edges)
        {
            adjList[edge.src].push_back(edge.dest);
            adjList[edge.dest].push_back(edge.src);
        }
    }
};

// Функция для обхода DFS на графе
void DFS(Graph const& graph, int v, vector<bool>& visited)
{
    // отметить текущий узел как посещенный
    visited[v] = true;

    // делаем для каждого ребра (v, u)
    for (int u : graph.adjList[v])
    {
        if (!visited[u]) 
            DFS(graph, u, visited);
    }
}

// Функция для проверки, все ли вершины с ненулевой степенью в графе
// принадлежат одному связанному компоненту
bool isConnected(Graph const& graph, int n)
{
    // чтобы отслеживать, посещена ли вершина или нет
    vector<bool> visited(n);

    // запускаем поиск в глубину с первой вершины с ненулевой степенью
    for (int i = 0; i < n; i++)
    {
        if (graph.adjList[i].size())
        {
            DFS(graph, i, visited);
            break;
        }
    }

    // если один вызов DFS не может посетить все вершины с ненулевой степенью,
    // graph содержит более одной компоненты связности
    for (int i = 0; i < n; i++)
    {
        if (!visited[i] && graph.adjList[i].size() > 0) {
            return false;
        }
    }

    return true;
}

// Вспомогательная функция для возврата общего количества вершин с нечетной степенью
// на графе
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

    // общее количество узлов в графе
    int n = 5;

    // создаем неориентированный граф из заданных ребер
    Graph graph(edges, n);

    // проверяем, принадлежат ли все вершины с ненулевой степенью одному
    // подключенный компонент
    bool is_connected = isConnected(graph, n);

    // находим общее количество вершин с нечетной степенью
    int odd = countOddVertices(graph);

    // Эйлеров путь существует, если все вершины не нулевой степени соединены,
    // и ноль или две вершины имеют нечетную степень

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