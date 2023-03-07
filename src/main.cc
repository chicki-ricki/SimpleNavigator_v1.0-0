#include "s21_graph_algorithms.h"

void freeArr(int **arr, size_t count) {
  for (size_t i = 0; i < count; i++) {
    free(arr[i]);
  }
  free(arr);
}

int main(int ac, char **av) {
  if (ac == 2) {
    Graph graph;
    std::vector<int> graphDepth;

    if (graph.loadGraphFromFile(std::string(av[1])) != 0) {
      s21::exitError("Error: cannot read file with graph");
    }
    if (graph.exportGraphToDot("exportFile.dot") != 0) {
      s21::exitError("Error: cannot write graph to *.dot file");
    }

    // graphAlgorithms
    GraphAlgorithms graphAlg;
    graphDepth = graphAlg.depthFirstSearch(graph, 1);
    std::cout << "обход in main: " << std::endl;
    for (std::vector<int>::iterator it = graphDepth.begin(); it != graphDepth.end(); it++) {
      std::cout << *it + 1 << "->";
    }
    std::cout << std::endl;

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