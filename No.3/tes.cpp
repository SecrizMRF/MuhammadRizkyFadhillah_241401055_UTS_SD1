#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Graph {
private:
    int numVertices;
    vector<vector<int>> adjMatrix;

public:
    Graph(int V) {
        numVertices = V;
        adjMatrix.resize(V, vector<int>(V, 0));
    }

    void addEdge(int i, int j, int w) {
        i--;
        j--;
        adjMatrix[i][j] = w;
        adjMatrix[j][i] = w;
    }

    void printAdjMatrix() {
        cout << "Adjacency Matrix (berisi jarak antar kota):\n";
        for (int i = 0; i < numVertices; i++) {
            for (int j = 0; j < numVertices; j++)
                cout << adjMatrix[i][j] << " ";
            cout << endl;
        }
    }

    // ---------- DFS dengan prioritas jarak terkecil ----------
    void dfsUtil(int current, vector<bool>& visited, string kota[]) {
        visited[current] = true;
        cout << kota[current];

        // Simpan semua tetangga yang terhubung
        vector<pair<int, int>> tetangga; // (jarak, index kota)
        for (int i = 0; i < numVertices; i++) {
            if (adjMatrix[current][i] != 0 && !visited[i]) {
                tetangga.push_back({adjMatrix[current][i], i});
            }
        }

        // Urutkan manual berdasarkan bobot (jarak) terkecil
        for (int i = 0; i < (int)tetangga.size(); i++) {
            for (int j = i + 1; j < (int)tetangga.size(); j++) {
                if (tetangga[j].first < tetangga[i].first) {
                    auto temp = tetangga[i];
                    tetangga[i] = tetangga[j];
                    tetangga[j] = temp;
                }
            }
        }

        // Rekursif ke kota berikutnya (berdasarkan jarak kecil)
        for (int k = 0; k < (int)tetangga.size(); k++) {
            cout << " -> ";
            dfsUtil(tetangga[k].second, visited, kota);
        }
    }

    void dfs(int startVertex, string kota[]) {
        vector<bool> visited(numVertices, false);
        cout << "PENJELAJAHAN PARUL (DFS dari " << kota[startVertex] << "):\n";
        dfsUtil(startVertex, visited, kota);
        cout << endl << endl;
    }

    // ---------- Fungsi bantu: reverse manual ----------
    void reverseVector(vector<int>& vec) {
        int left = 0, right = vec.size() - 1;
        while (left < right) {
            int temp = vec[left];
            vec[left] = vec[right];
            vec[right] = temp;
            left++;
            right--;
        }
    }

    // ---------- BFS berbobot ----------
    void bfsWeighted(int startVertex, int endVertex, string kota[]) {
        vector<int> jarak(numVertices, 9999);
        vector<int> parent(numVertices, -1);
        queue<int> q;

        jarak[startVertex] = 0;
        q.push(startVertex);

        while (!q.empty()) {
            int u = q.front(); q.pop();

            for (int v = 0; v < numVertices; v++) {
                if (adjMatrix[u][v] != 0) {
                    int newDist = jarak[u] + adjMatrix[u][v];
                    if (newDist < jarak[v]) {
                        jarak[v] = newDist;
                        parent[v] = u;
                        q.push(v);
                    }
                }
            }
        }

        // --- Rekonstruksi jalur ---
        vector<int> path;
        for (int v = endVertex; v != -1; v = parent[v])
            path.push_back(v);
        reverseVector(path);

        // --- Output utama ---
        cout << "JALUR TERCEPAT PARUL (BFS):\n";
        int totalJarak = 0;
        for (int i = 0; i < (int)path.size(); i++) {
            cout << kota[path[i]];
            if (i < (int)path.size() - 1) {
                int segmen = adjMatrix[path[i]][path[i + 1]];
                totalJarak += segmen;
                cout << " (" << segmen << "m)\n";
            }
        }

        cout << "\n\nJalur terpendek: ";
        for (int i = 0; i < (int)path.size(); i++) {
            cout << kota[path[i]];
            if (i < (int)path.size() - 1) cout << " -> ";
        }
        cout << "\nTotal langkah: " << path.size() - 1 << " edge";
        cout << "\nTotal jarak: " << totalJarak << " meter\n";
    }
};

// ---------- MAIN ----------
int main() {
    Graph g(5);
    string kota[5] = {"A", "B", "C", "D", "E"};

    g.addEdge(1, 2, 5); // A-B (5)
    g.addEdge(1, 3, 2); // A-C (2)
    g.addEdge(2, 4, 4); // B-D (4)
    g.addEdge(3, 4, 1); // C-D (1)
    g.addEdge(4, 5, 3); // D-E (3)

    cout << "=== DATA GRAF PARUL ===\n";
    g.printAdjMatrix();
    cout << endl;

    // DFS
    g.dfs(0, kota);

    // BFS berbobot
    g.bfsWeighted(0, 4, kota);

    return 0;
}
