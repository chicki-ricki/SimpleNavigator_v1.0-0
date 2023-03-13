#include "s21_graph_algorithms.h"

void freeArr(int **arr, size_t count) {
  for (size_t i = 0; i < count; i++) {
    delete [] arr[i];
  }
  delete [] arr;
}

void printResult(int *testGraph, size_t count) {
  for (size_t i = 0; i < count; i++) {
    std::cout << testGraph[i] << "->";
  }
  std::cout << std::endl;
}

void printResult2D(int **matrix, unsigned int count) {
  for (size_t i = 0; i < count; i++) {
    for (size_t j = 0; j < count; j++) {
      std::cout << matrix[i][j] << " |";
    }
    std::cout << std::endl;
    }
}

void  makeDepthFirstSearch(Graph &graph, GraphAlgorithms &graphAlg) {
  int *testGraph;

  testGraph = graphAlg.depthFirstSearch(graph, 1);
  std::cout << "обход в глубину in main: " << std::endl;
  printResult(testGraph, graph.getSizeGraph());
  delete [] testGraph;
}

void makeBreadthFirstSearch(Graph &graph, GraphAlgorithms &graphAlg) {
  int *testGraph;

  testGraph = graphAlg.breadthFirstSearch(graph, 1);
  std::cout << "обход в ширину in main: " << std::endl;
  printResult(testGraph, graph.getSizeGraph());
  delete [] testGraph;
}

void makeDeyxtraAlg(Graph &graph, GraphAlgorithms &graphAlg) {
  int minDex = graphAlg.getShortestPathBetweenVertices(graph, 1, 4);

  std::cout << "minDeyxtra in main: " << minDex << std::endl;
}

void makeFloydWorshelAlg(Graph &graph, GraphAlgorithms &graphAlg) {
  int **matrix;

  matrix = graphAlg.getShortestPathsBetweenAllVertices(graph);
  std::cout << "Floyd-Worshel: " << std::endl;
  printResult2D(matrix, graph.getSizeGraph());
  freeArr(matrix, graph.getSizeGraph());
}

void makeAlgOfPrim(Graph &graph, GraphAlgorithms &graphAlg) {
  int **matrix;

  matrix = graphAlg.getLeastSpanningTree(graph);
  std::cout << "Prim's algorithm: " << std::endl;
  printResult2D(matrix, graph.getSizeGraph());
  freeArr(matrix, graph.getSizeGraph());
}

void makeVoyage(Graph &graph, GraphAlgorithms &graphAlg) {
  TsmResult rez;

  rez = graphAlg.solveTravelingSalesmanProblem(graph);
  std::cout << "Voyage:"<< std::endl;
  for (std::vector<int>::iterator it = rez.vertices.begin(); it != rez.vertices.end(); it++) {
    std::cout << *it << "->";
  }
  std::cout << std::endl;
}

int main(int ac, char **av) {
  if (ac == 2) {
    Graph graph;
    GraphAlgorithms graphAlg;

    if (graph.loadGraphFromFile(std::string(av[1])) != 0) {
      s21::exitError("Error: cannot read file with graph");
    }
    // if (graph.exportGraphToDot("exportFile.dot") != 0) {
    //   s21::exitError("Error: cannot write graph to file");
    // }
    // makeDepthFirstSearch(graph, graphAlg);
    // makeBreadthFirstSearch(graph, graphAlg);
    // makeDeyxtraAlg(graph, graphAlg);
    // makeFloydWorshelAlg(graph, graphAlg);
    // makeAlgOfPrim(graph, graphAlg);
    makeVoyage(graph, graphAlg);
  } else {
    s21::exitError("Error: invalid count of arguments");
  }
//while (1) {};
  return (0);
}
