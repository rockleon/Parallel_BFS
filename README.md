# Parallel_BFS
Implement BFS using parallel algorithms strategy in C++ and compare it with serial BFS.
Parallel execution is done using OpenMP multi-threading.


## Description of files

### generate_graph.cpp
Creates a 2-D matrix representation for a dummy graph in "dummy.txt" file. Matrix consists of "0's" and "1's". Compile and execute this file to create "dummy.txt" file, which will be used while execution of the main function.

### bfs.cpp
Main function having both Serial and Parallel BFS code. It has an option to manually enter a graph using matrix representation having space seperated 0's and 1's or, or use the dummy data created using 'generate_graph' code. The code performs both serial and parallel bfs and displays their execution times.

### test_omp.cpp
Code to check Openmp version and maximum num of threads. Compile this file using this command -
```
sh g++ -std=c++11 -fopenmp test_omp.cpp
```


## Steps for execution

```sh
g++ -o a.out -fopenmp bfs.cpp
./a.out
```


## Execution time 

Execution times in miliseconds(ms)

| Vertices      | Edges         | Serial Execution(ms)   | Parallel Execution(ms) |
|:-------------:|:-------------:|:------------------:|:------------------:|
| 10            | 19            | 0.08200            | 0.28360            |
| 50            | 620           | 0.14100            | 0.17090            |
| 500           | 62477         | 3.14500            | 1.34590            |
| 1000          | 250024        | 13.47700           | 4.75420            |
| 2000          | 999593        | 42.37300           | 19.54750           |
| 5000          | 6249406       | 241.56200          | 100.92930          |
| 10,000        | 24998488      | 977.44900          | 380.30280          |
| 20,000        | 99990353      | 33291.78100        | 39769.25280        |