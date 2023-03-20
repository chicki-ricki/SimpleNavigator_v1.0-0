#include "s21_graph_algorithms.h"

void freeArr(int **arr, size_t count) {
  for (size_t i = 0; i < count; i++) {
    if (arr[i]) {
      delete[] arr[i];
    }
  }
  if (arr) {
    delete[] arr;
  }
}

void printResult(int *testGraph, size_t count) {
  for (size_t i = 0; i < count; i++) {
    std::cout << testGraph[i];
    if (i < count - 1) {
      std::cout << "->";
    }
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

void makeDepthFirstSearch(Graph &graph, GraphAlgorithms &GraphAlgorithms) {
  int *testGraph;

  testGraph = GraphAlgorithms.depthFirstSearch(graph, 1);
  std::cout << "***********" << std::endl;
  std::cout << "обход в глубину: " << std::endl;
  printResult(testGraph, graph.getSizeGraph());
  delete[] testGraph;
}

void makeBreadthFirstSearch(Graph &graph, GraphAlgorithms &GraphAlgorithms) {
  int *testGraph;

  testGraph = GraphAlgorithms.breadthFirstSearch(graph, 1);
  std::cout << "***********" << std::endl;
  std::cout << "обход в ширину: " << std::endl;
  printResult(testGraph, graph.getSizeGraph());
  delete[] testGraph;
}

void makeDeyxtraAlg(Graph &graph, GraphAlgorithms &GraphAlgorithms) {
  int start = 1;
  int finish = 4;
  int minDex =
      GraphAlgorithms.getShortestPathBetweenVertices(graph, start, finish);

  std::cout << "***********" << std::endl;
  std::cout << "minDeyxtra from " << start << " to " << finish;
  std::cout << ": " << minDex << std::endl;
}

void makeFloydWorshelAlg(Graph &graph, GraphAlgorithms &GraphAlgorithms) {
  int **matrix;

  matrix = GraphAlgorithms.getShortestPathsBetweenAllVertices(graph);
  std::cout << "***********" << std::endl;
  std::cout << "Floyd-Worshel: " << std::endl;
  printResult2D(matrix, graph.getSizeGraph());
  freeArr(matrix, graph.getSizeGraph());
}

void makeAlgOfPrim(Graph &graph, GraphAlgorithms &GraphAlgorithms) {
  int **matrix;

  matrix = GraphAlgorithms.getLeastSpanningTree(graph);
  std::cout << "***********" << std::endl;
  std::cout << "Prim's algorithm: " << std::endl;
  printResult2D(matrix, graph.getSizeGraph());
  freeArr(matrix, graph.getSizeGraph());
}

void makeVoyage(Graph &graph, GraphAlgorithms &GraphAlgorithms) {
  TsmResult rez;

  rez = GraphAlgorithms.solveTravelingSalesmanProblem(graph);
  std::cout << "***********" << std::endl;
  std::cout << "The shortest voyage by ant's algorithm:" << std::endl;
  if (*(rez.vertices.begin()) != 1) {
    std::vector<int> temp_v;
    int k = -1;
    while (rez.vertices[++k] != 1)
      ;
    for (int i = k; i < (int)rez.vertices.size(); i++) {
      temp_v.push_back(rez.vertices[i]);
    }
    for (int i = 1; i < k; i++) {
      temp_v.push_back(rez.vertices[i]);
    }
    temp_v.push_back(1);
    std::vector<int>::iterator itTemp = temp_v.begin();
    for (; itTemp != temp_v.end(); itTemp++) {
      std::cout << *itTemp;
      if (itTemp != temp_v.end() - 1) {
        std::cout << "->";
      }
    }
  } else {
    std::vector<int>::iterator it = rez.vertices.begin();
    for (; it != rez.vertices.end(); it++) {
      std::cout << *it;
      if (it != rez.vertices.end() - 1) {
        std::cout << "->";
      }
    }
  }
  std::cout << std::endl;
  std::cout << "Voyage distance: " << rez.distance << std::endl;
}

int main(int ac, char **av) {
  if (ac == 2) {
    Graph graph;
    GraphAlgorithms GraphAlgorithms;
    time_t bg, nd_time;

    if (graph.loadGraphFromFile(std::string(av[1])) != 0) {
      s21::exitError("Error: cannot read file with graph");
    }
    if (graph.exportGraphToDot("exportFile.dot") != 0) {
      s21::exitError("Error: cannot write graph to file");
    }
    makeDepthFirstSearch(graph, GraphAlgorithms);
    makeBreadthFirstSearch(graph, GraphAlgorithms);
    makeDeyxtraAlg(graph, GraphAlgorithms);
    makeFloydWorshelAlg(graph, GraphAlgorithms);
    makeAlgOfPrim(graph, GraphAlgorithms);
    time(&bg);
    makeVoyage(graph, GraphAlgorithms);
    time(&nd_time);
    std::cout << "Calculating time: " << difftime(nd_time, bg) << " seconds\n";
  } else {
    s21::exitError("Error: invalid count of arguments");
  }
  // while (1) {};
  return (0);
}
