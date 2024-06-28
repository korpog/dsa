#include <iostream>
#include <vector>
#include <queue>

class Graph {
private:
    int V; // number of vertices
    std::vector<std::vector<int>> incidenceMatrix;

public:
    Graph(int vertices) : V(vertices) {
        incidenceMatrix.resize(V, std::vector<int>(V, 0));
    }

    void addEdge(int u, int v, int weight) {
        incidenceMatrix[u][v] = weight;
    }

    std::vector<int> topoSort() {
        std::vector<int> inDegree(V, 0);
        std::vector<int> result;
        std::queue<int> q;

        // Calculate in-degree for each vertex
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (incidenceMatrix[i][j] != 0) {
                    inDegree[j]++;
                }
            }
        }

        // Enqueue vertices with in-degree 0
        for (int i = 0; i < V; i++) {
            if (inDegree[i] == 0) {
                q.push(i);
            }
        }

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            result.push_back(u);

            // Reduce in-degree of adjacent vertices
            for (int v = 0; v < V; v++) {
                if (incidenceMatrix[u][v] != 0) {
                    if (--inDegree[v] == 0) {
                        q.push(v);
                    }
                }
            }
        }

        if (result.size() != V) {
            std::cout << "Graph contains a cycle." << std::endl;
            return {};
        }

        return result;
    }

    void DFS(int v, std::vector<bool>& visited) {
        visited[v] = true;
        std::cout << v << " ";

        for (int i = 0; i < V; i++) {
            if (incidenceMatrix[v][i] != 0 && !visited[i]) {
                DFS(i, visited);
            }
        }
    }

    void DFSTraversal() {
        std::vector<bool> visited(V, false);

        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                DFS(i, visited);
            }
        }
        std::cout << std::endl;
    }
};

int main() {
    Graph g(6);
    g.addEdge(5, 2, 1);
    g.addEdge(5, 0, 1);
    g.addEdge(4, 0, 1);
    g.addEdge(4, 1, 1);
    g.addEdge(2, 3, 1);
    g.addEdge(3, 1, 1);

    std::cout << "Topological Sort: ";
    std::vector<int> topo = g.topoSort();
    for (int v : topo) {
        std::cout << v << " ";
    }
    std::cout << std::endl;

    std::cout << "DFS Traversal: ";
    g.DFSTraversal();

    return 0;
}