// #include "s21_graph_algorithms.h"
#include "s21_graph.h"

// extern void s21::exitError(std::string);

int main(int ac, char **av) {
  if (ac == 2) {
    Graph graph;

    if (graph.loadGraphFromFile(std::string(av[1])) != 0) {
      s21::exitError("Error: cannot read file with graph");
    }
/*
for (std::vector<std::vector<int> >::iterator it = graph.getGraph().begin(); it != graph.getGraph().end(); it++) {
  for (std::vector<int>::iterator it2 = it->begin(); it2 != it->end(); it2++) {
    std::cout << *it2 << " ";
  }
  std::cout << std::endl;
}
std::cout << std::endl;
*/
  //   // graphAlgorithms
  //   GraphAlgorithms graphAlgDepth;
  //   graphAlgDepth.depthFirstSearch(graph, 1);

  //   std::string fileExport;
  //   if (graph.exportGraphToDot(fileExport) != 0)
  //     s21::exitError("Error: cannot write graph to *.dot file");
  // } else {
  //   s21::exitError("Error: invalid count of arguments");
  }
  return (0);
}