#include "s21_graph_algorithms.h"

void freeArr(int **arr, size_t count) {
  for (size_t i = 0; i < count; i++) {
    delete [] arr[i];
  }
  delete [] arr;
}

void printResult(int *testGraph, size_t count)
{
  for (size_t i = 0; i < count; i++) {
    std::cout << testGraph[i] << "->";
  }
  std::cout << std::endl;
}


int main(int ac, char **av) {
  if (ac == 2) {
    Graph graph;
    int *testGraph;

    if (graph.loadGraphFromFile(std::string(av[1])) != 0) {
      s21::exitError("Error: cannot read file with graph");
    }
     if (graph.exportGraphToDot("exportFile.dot") != 0) {
       s21::exitError("Error: cannot write graph to file");
     }
     // graphAlgorithms
    GraphAlgorithms graphAlg;
    testGraph = graphAlg.depthFirstSearch(graph, 1);

    std::cout << "обход в глубину in main: " << std::endl;
    printResult(testGraph, graph.getSizeGraph());
    delete [] testGraph;

    bzero(testGraph, graph.getSizeGraph());
    testGraph = graphAlg.breadthFirstSearch(graph, 1);
    std::cout << "обход в ширину in main: " << std::endl;
    printResult(testGraph, graph.getSizeGraph());
    delete [] testGraph;


    // graphAlgDeyxtra;
    int minDex = graphAlg.getShortestPathBetweenVertices(graph, 1, 4);
    std::cout << "minDeyxtra in main: " << minDex << std::endl;
 
    // graphAlgFloyd;
    int **matrix = graphAlg.getShortestPathsBetweenAllVertices(graph);
    
    std::cout << "Floyd-Worshel: " << std::endl;
    for (size_t i = 0; i < graph.getSizeGraph(); i++) {
      for (size_t j = 0; j < graph.getSizeGraph(); j++) {
        std::cout << matrix[i][j] << " |";
      }
      std::cout << std::endl;
    }
    freeArr(matrix, graph.getSizeGraph());
  } else {
    s21::exitError("Error: invalid count of arguments");
  }
while (1) {};
  return (0);
}
