# Parallel_BFS
Implement BFS using parallel algorithms strategy and compare it with serial BFS.
Parallel execution is done using OpenMP multi-threading.


## Description of files

### generate_graph.cpp
Creates a 2-D matrix representation for a dummy graph in "dummy.txt" file.
Matrix consists of "0's" and "1's". Compile and execute this file to create "dummy.txt" file, which will be used while execution of the main function.

### bfs.cpp
Main function of both Serial and Parallel BFS code as well as the interface code.


## Steps for execution

```sh
g++ -o a.out -fopenmp bfs.cpp
./a.out
```