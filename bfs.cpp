#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <fstream>
#include <time.h>
#include <iomanip>

using namespace std;

class Graph
{
    int V; // No. of vertices

    // Pointer to an array containing adjacency lists
    list<int> *adj;

public:
    Graph(int V); // Constructor

    // Add an edge to graph
    void addEdge(int v, int w);

    // BFS traversal from a given source s
    void BFS(int s);

    // Create graph using user entered data
    int inputGraph();

    // Generate graph using data from dummy file
    int generateDummyGraph();
};

Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
}

void Graph::BFS(int s)
{
    // Mark all the vertices as not visited
    bool *visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;

    // Queue for BFS
    list<int> queue;

    // Mark the current node as visited and enqueue it
    visited[s] = true;
    queue.push_back(s);

    while (!queue.empty())
    {
        // Dequeue a vertex from queue and print it
        s = queue.front();
        // cout << s << " ";
        queue.pop_front();

        // Get all adjacent vertices of the dequeued
        // vertex s. If a adjacent has not been visited,
        // then mark it visited and enqueue it
        for (auto i = adj[s].begin(); i != adj[s].end(); ++i)
        {
            if (!visited[*i])
            {
                visited[*i] = true;
                queue.push_back(*i);
            }
        }
    }
}

int Graph::inputGraph()
{
    int v, num, edges = 0, i, j;
    cout << "Enter number of vertices: ";
    cin >> v;
    cout << "Enter graph data in matrix format-\n";

    for (i = 0; i < v; i++)
    {
        for (j = 0; j < v; j++)
        {
            cin >> num;
            if (num == 1)
            {
                this->addEdge(i, j);
                edges++;
            }
        }
    }

    return edges;
}

int Graph::generateDummyGraph()
{
    int i, j, num, edges = 0;
    cout << "\nGenerating graph using dummy data...\n";
    ifstream file("dummy.txt");
    string stream, ch;
    i = 0;

    while (getline(file, stream))
    {
        j = 0;
        stringstream line(stream);
        while (getline(line, ch, ','))
        {
            num = stoi(ch);
            if (num == 1)
            {
                this->addEdge(i, j);
                edges++;
            }
            j++;
        }
        i++;
    }

    return edges;
}

Graph g(10000);

int main()
{
    int option, v, num, edges = 0, i, j, source = 1;

    cout << "1) Use dummy data.\n2) Enter data manualy.\n\n";
    cout << "Select your option(1/2): ";
    cin >> option;

    // Generate graph using data entered by the user
    if (option == 2)
        edges = g.inputGraph();
    // Generate graph using dummy data
    else if (option == 1)
        edges = g.generateDummyGraph();
    else
    {
        cout << "\nInvalid option!\nTerminating the program...!\n\n";
        return 0;
    }

    cout << "\nNumber of edges: " << edges << endl;
    cout << "\nEnter starting vertex: ";
    cin >> source;

    cout << "Breadth First Search Traversal started...";

    clock_t start, end;
    start = clock();
    g.BFS(source);
    end = clock();

    double execution_time = double(end - start) / double(CLOCKS_PER_SEC);

    cout << "\n\nBFS Completed!\n\nExecution time: " << fixed << execution_time << setprecision(5) << " seconds.\n\n";

    return 0;
}
