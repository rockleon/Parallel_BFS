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


## Execution time 

| Vertices      | Edges         | Serial Execution(ms)   | Parallel Execution(ms) |
| ------------- |:-------------:|:------------------:|:------------------:|
| 500           | 124954        | 3.38600            | 2.50220            |
| 1000          | 500048        | 10.34400           | 9.48770            |
| 2000          | 1999187       | 42.66100           | 38.94060           |
| 5000          | 12498813      | 233.63800          | 229.53920          |
| 10,000        | 49996977      | 1025.71700          | 959.95050          |
| 20,000        | 199980707     |  |    |