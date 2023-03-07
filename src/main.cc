#include "s21_graph_algorithms.h"
// #include "s21_graph.h"

// extern void s21::exitError(std::string);

void printResult(std::vector<int> testGraph)
{
	for (std::vector<int>::iterator it = testGraph.begin(); it != testGraph.end(); it++) {
		std::cout << *it + 1 << "->";
	}
  std::cout << std::endl;
}


int main(int ac, char **av) {
  if (ac == 2) {
    Graph graph;
    std::vector<int> testGraph;

    if (graph.loadGraphFromFile(std::string(av[1])) != 0) {
      s21::exitError("Error: cannot read file with graph");
    }
    // if (graph.exportGraphToDot("exportFile.dot") != 0) {
    //   s21::exitError("Error: cannot write graph to file");
    // }
  //   // graphAlgorithms
    GraphAlgorithms graphAlgDepth;
//    testGraph = graphAlgDepth.depthFirstSearch(graph, 1);

// std::cout << "обход в глубину in main: " << std::endl;
// printResult(testGraph);

	testGraph.clear();
	testGraph = graphAlgDepth.breadthFirstSearch(graph, 5);
std::cout << "обход в ширину in main: " << std::endl;
printResult(testGraph);


    int minDex = graphAlgDepth.getShortestPathBetweenVertices(graph, 1, 4);
std::cout << "minDex in main: " << minDex << std::endl;

  //   std::string fileExport;
  //   if (graph.exportGraphToDot(fileExport) != 0)
  //     s21::exitError("Error: cannot write graph to *.dot file");
  // } else {
  //   s21::exitError("Error: invalid count of arguments");
  }
  return (0);
}