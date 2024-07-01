#include <vector>
#include <queue>
#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <random>

using namespace std;
using namespace std::chrono;

class Graph
{
private:
    int V;
    vector<vector<int>> incidenceMatrix;

public:
    Graph(int vertices) : V(vertices)
    {
        incidenceMatrix.resize(V, vector<int>(V, 0));
    }

    void addEdge(int u, int v, int weight)
    {
        incidenceMatrix[u][v] = weight;
    }

    vector<int> topoSort()
    {
        vector<int> inDegree(V, 0);
        vector<int> result;
        queue<int> q;

        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                if (incidenceMatrix[i][j] != 0)
                {
                    inDegree[j]++;
                }
            }
        }

        for (int i = 0; i < V; i++)
        {
            if (inDegree[i] == 0)
            {
                q.push(i);
            }
        }

        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            result.push_back(u);

            for (int v = 0; v < V; v++)
            {
                if (incidenceMatrix[u][v] != 0)
                {
                    if (--inDegree[v] == 0)
                    {
                        q.push(v);
                    }
                }
            }
        }

        if (result.size() != V)
        {
            cout << "Graph contains a cycle." << endl;
            return {};
        }

        return result;
    }

    void DFS(int v, vector<bool> &visited)
    {
        visited[v] = true;
        cout << v << " ";

        for (int i = 0; i < V; i++)
        {
            if (incidenceMatrix[v][i] != 0 && !visited[i])
            {
                DFS(i, visited);
            }
        }
    }

    void DFSTraversal()
    {
        vector<bool> visited(V, false);

        for (int i = 0; i < V; i++)
        {
            if (!visited[i])
            {
                DFS(i, visited);
            }
        }
        cout << endl;
    }
};

Graph generateRandomGraph(int V)
{
    Graph g(V);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 99);

    for (int i = 0; i < V; i++)
    {
        for (int j = i + 1; j < V; j++)
        {
            if (dis(gen) < 30)
            {
                g.addEdge(i, j, 1);
            }
        }
    }
    return g;
}

Graph generateGraphWithCycle(int V)
{
    Graph g = generateRandomGraph(V);
    g.addEdge(V - 1, 0, 1);
    return g;
}

int main()
{
    Graph g10 = generateRandomGraph(10);
    Graph g20 = generateRandomGraph(20);

    Graph g10c = generateGraphWithCycle(10);
    Graph g20c = generateGraphWithCycle(20);

    int *average = new int[30];

    for (int i = 0; i < 30; i++)
    {

        auto start = high_resolution_clock::now();

        // cout << "Topological Sort: ";

        vector<int> topo = g10c.topoSort();
        // for (int v : topo)
        // {
        //     cout << v << " ";
        // }
        // cout << endl;

        // cout << "DFS Traversal: ";
        // g10.DFSTraversal();

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        average[i] = duration.count();

        cout << "Time taken by function: "
             << duration.count() << " microseconds" << endl;
    }

    int sum = 0;
    for (int i = 0; i < 30; i++)
    {
        sum += average[i];
    }
    double avg = static_cast<double>(sum) / 30;

    cout << "Average time taken by function: "
         << avg << " microseconds" << endl;

    return 0;
}