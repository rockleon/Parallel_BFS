#include <iostream>
#include <list>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include <time.h>
#include <iomanip>
#include <stdio.h>
#include <omp.h>

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

    // Create graph using user entered data
    int inputGraph();

    // Generate graph using data from dummy file
    int generateDummyGraph();

    // BFS traversal from a given source s
    void BFS(int s);

    // Parallel BFS traversal from given source s
    // using openmp
    void parallel_BFS(int s);
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

void Graph::parallel_BFS(int s)
{
    // Mark all the vertices as not visited
    bool *visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;

    // Two Queues for parallel BFS
    // One queue to loop through pushed vertices
    // Another queue to push vertices for next iteration.
    vector<vector<int>> queue = {{}, {}};
    int turn = 0, next_turn;

    // Mark the current node as visited and enqueue it
    visited[s] = true;
    queue[turn].push_back(s);

    while (!queue[turn].empty())
    {
        // get other queue's index
        next_turn = (turn + 1) % 2;

        // Dequeue a vertex from queue and print it
        // Here we use openmp parallel threading
        // Whatever the number of vertices present in the queue,
        // That many threads will be created and executed parallely
        #pragma omp parallel for
        for (int j = 0; j < queue[turn].size(); j++)
        {
            s = queue[turn][j];
        // cout << s << " ";

        // Get all adjacent vertices of the dequeued
        // vertex s. If a adjacent has not been visited,
        // then mark it visited and enqueue it in the next queue
        #pragma omp parallel num_threads(adj[s].size())
            for (auto i = adj[s].begin(); i != adj[s].end(); ++i)
            {
                // Critical section to avoid race condition
                #pragma omp critical
                if (!visited[*i])
                {
                    visited[*i] = true;
                    queue[next_turn].push_back(*i);
                }
            }
        }

        // Clear the current queue to use it for enqueuing
        // vertices int the next iteration
        queue[turn].clear();
        turn = (turn + 1) % 2;
    }
}

Graph g(10000);

int main()
{
    int option, v, num, edges = 0, i, j, source = 1;
    char ch;

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

    // Display the number of edges in the graph
    cout << "\nNumber of edges: " << edges << endl;

    do
    {
        // Get the starting vertex
        cout << "\nEnter starting vertex: ";
        cin >> source;

        cout << "\nSerial Breadth First Search Traversal started...";

        clock_t start, end;
        double execution_time;

        // Serial BFS function with timed execution
        start = clock();
        g.BFS(source);
        end = clock();

        execution_time = double(end - start) / double(CLOCKS_PER_SEC);

        cout << "\nSerial BFS Completed!\nExecution time: " << fixed << execution_time << setprecision(5) << " seconds.\n\n";

        cout << "Parallel Breadth First Search Traversal started...";

        double stime, ftime;

        // Parallel BFS function with timed execution
        stime = omp_get_wtime();
        g.BFS(source);
        ftime = omp_get_wtime();

        execution_time = ftime - stime;

        cout << "\nParallel BFS Completed!\nExecution time: " << fixed << execution_time << setprecision(5) << " seconds.\n\n";

        cout << "Perform another traversal? (y/n): ";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');

    return 0;
}
