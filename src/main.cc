#include "s21_graph_algorithms.h"

void freeArr(int **arr, size_t count) {
  for (size_t i = 0; i < count; i++) {
    free(arr[i]);
  }
  free(arr);
}

// void printResult(std::vector<int> testGraph)
void printResult(int *testGraph, size_t count)
{
	// for (std::vector<int>::iterator it = testGraph.begin(); it != testGraph.end(); it++) {
	// 	std::cout << *it + 1 << "->";
	// }
  for (size_t i = 0; i < count; i++) {
    std::cout << testGraph[i] << "->";
  }
  std::cout << std::endl;
}


int main(int ac, char **av) {
  if (ac == 2) {
    Graph graph;
    // std::vector<int> testGraph;
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
    free(testGraph);
// while (1) {};

    // testGraph.clear();
    bzero(testGraph, graph.getSizeGraph());
    testGraph = graphAlg.breadthFirstSearch(graph, 1);
    std::cout << "обход в ширину in main: " << std::endl;
    printResult(testGraph, graph.getSizeGraph());
    free(testGraph);


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
