#include "s21_graph_algorithms.h"

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
    GraphAlgorithms graphAlgDepth;
    graphDepth = graphAlgDepth.depthFirstSearch(graph, 1);

std::cout << "обход in main: " << std::endl;
for (std::vector<int>::iterator it = graphDepth.begin(); it != graphDepth.end(); it++) {
  std::cout << *it + 1 << "->";
}
std::cout << std::endl;

    GraphAlgorithms graphAlgDeyxtra;
    int minDex = graphAlgDeyxtra.getShortestPathBetweenVertices(graph, 1, 4);
std::cout << "minDex in main: " << minDex << std::endl;

    GraphAlgorithms graphAlgFloyd;
    int **matrix = graphAlgFloyd.getShortestPathsBetweenAllVertices(graph);
std::cout << "Floyd-Worshel: " << std::endl;
for (size_t i = 0; i < graph.getSizeGraph(); i++) {
  for (size_t j = 0; j < graph.getSizeGraph(); j++) {
    std::cout << matrix[i][j] << " |";
  }
  std::cout << std::endl;
}
    //free(matrix);

  } else {
    s21::exitError("Error: invalid count of arguments");
  }
  return (0);
}