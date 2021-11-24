# Parallel_BFS
Implement BFS using parallel algorithms strategy and compare it with serial bfs


## Description of files

### generate_graph.cpp
Creates a 2-D matrix representation for a dummy graph in "dummy.txt" file.
Matrix consists of "0's" and "1's".

### bfs.cpp
Main function of both Serial and Parallel BFS code as well as the interface code.


## Steps for execution

```sh
g++ -o a.out -fopenmp bfs.cpp
./a.out
```