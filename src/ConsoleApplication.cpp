#include "ConsoleApplication.h"

std::string ConsoleApplication::fileName_ = "";
Graph *ConsoleApplication::graph_ = NULL;
GraphAlgorithms *ConsoleApplication::graphAlg_ = NULL;

#define GRAPH_PATH "graph_files/good/"

void ConsoleApplication::load() {
  std::cout << D_BLUE << "Choose a file to load the graph from: " << NONE;
  std::string enterFileName;
  std::cin >> enterFileName;
  if (isNotChosen_ == true) {
    graph_ = new Graph();
    graphAlg_ = new GraphAlgorithms();
  }
  if (graph_->loadGraphFromFile(GRAPH_PATH + enterFileName) != 0) {
    std::cout << GREY << "Error: cannot read this graph's file  " << NONE
              << std::endl;
    fileName_ = "";
    delete graph_;
    delete graphAlg_;
    isNotChosen_ = true;
  } else {
    isNotChosen_ = false;
    if (fileName_ != enterFileName) {
      fileName_ = enterFileName;
    }
  }
}

void ConsoleApplication::list() {
  std::cout << GREY << "Next files are available:" << NONE << std::endl;
  std::system("ls graph_files/good");
}

void ConsoleApplication::exit() {
  std::cout << GREY << "See you again!" << NONE << std::endl;
  delete graph_;
  graph_ = NULL;
  delete graphAlg_;
  graphAlg_ = NULL;
  std::exit(0);
}

void ConsoleApplication::freeArr(int **arr, size_t count) {
  for (size_t i = 0; i < count; i++) {
    if (arr[i]) {
      delete[] arr[i];
    }
  }
  if (arr) {
    delete[] arr;
  }
}

void ConsoleApplication::printResult(int *testGraph, size_t count) {
  for (size_t i = 0; i < count; i++) {
    std::cout << testGraph[i];
    if (i < count - 1) {
      std::cout << "->";
    }
  }
  std::cout << std::endl;
}

void ConsoleApplication::printResult2D(int **matrix, unsigned int count) {
  for (size_t i = 0; i < count; i++) {
    for (size_t j = 0; j < count; j++) {
      std::cout << matrix[i][j] << " |";
    }
    std::cout << std::endl;
  }
}

void ConsoleApplication::makeDepthFirstSearch(Graph graph,
                                              GraphAlgorithms GraphAlgorithms) {
  int *testGraph;
  int start = 1;

  testGraph = GraphAlgorithms.depthFirstSearch(graph, start);
  std::cout << "***********" << std::endl;
  std::cout << "depth first search: " << std::endl;
  printResult(testGraph, graph.getSizeGraph());
  std::cout << "***********" << std::endl;
  delete[] testGraph;
}

void ConsoleApplication::makeBreadthFirstSearch(
    Graph graph, GraphAlgorithms GraphAlgorithms) {
  int *testGraph;

  testGraph = GraphAlgorithms.breadthFirstSearch(graph, 1);
  std::cout << "***********" << std::endl;
  std::cout << "breadth first search: " << std::endl;
  printResult(testGraph, graph.getSizeGraph());
  std::cout << "***********" << std::endl;
  delete[] testGraph;
}

void ConsoleApplication::makeDeyxtraAlg(Graph graph,
                                        GraphAlgorithms GraphAlgorithms) {
  std::string start;
  std::string finish;
  std::cout << "Enter the first vertex number [1 - " << graph_->getSizeGraph()
            << "]: ";
  std::cin >> start;
  std::cout << "Enter the second vertex number [1 - " << graph_->getSizeGraph()
            << "]: ";
  std::cin >> finish;
  int minDex = GraphAlgorithms.getShortestPathBetweenVertices(
      graph, std::stoi(start), std::stoi(finish));

  std::cout << "***********" << std::endl;
  std::cout << "minDeyxtra from " << start << " to " << finish;
  std::cout << ": " << minDex << std::endl;
  std::cout << "***********" << std::endl;
}

void ConsoleApplication::makeFloydWorshelAlg(Graph graph,
                                             GraphAlgorithms GraphAlgorithms) {
  int **matrix;

  matrix = GraphAlgorithms.getShortestPathsBetweenAllVertices(graph);
  std::cout << "***********" << std::endl;
  std::cout << "Floyd-Worshel: " << std::endl;
  printResult2D(matrix, graph.getSizeGraph());
  std::cout << "***********" << std::endl;
  freeArr(matrix, graph.getSizeGraph());
}

void ConsoleApplication::makeAlgOfPrim(Graph graph,
                                       GraphAlgorithms GraphAlgorithms) {
  int **matrix;

  matrix = GraphAlgorithms.getLeastSpanningTree(graph);
  std::cout << "***********" << std::endl;
  std::cout << "Prim's algorithm: " << std::endl;
  printResult2D(matrix, graph.getSizeGraph());
  std::cout << "***********" << std::endl;
  freeArr(matrix, graph.getSizeGraph());
}

void ConsoleApplication::makeVoyage(Graph graph,
                                    GraphAlgorithms GraphAlgorithms) {
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
  std::cout << "***********" << std::endl;
}
