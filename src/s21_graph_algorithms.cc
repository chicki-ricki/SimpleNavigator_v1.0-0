#include "s21_graph_algorithms.h"

GraphAlgorithms::GraphAlgorithms() {}

GraphAlgorithms &GraphAlgorithms::operator=(const GraphAlgorithms &rhs) {
  return (*this);
}

GraphAlgorithms::GraphAlgorithms(const GraphAlgorithms &src) : GraphAlgorithms() {
  *this = src;
}

GraphAlgorithms &GraphAlgorithms::operator=(GraphAlgorithms &&gg) {
  return (*this);
}

GraphAlgorithms::GraphAlgorithms(GraphAlgorithms &&gg) : GraphAlgorithms() {
  *this = gg;
}

int	*GraphAlgorithms::depthFirstSearch(Graph &graph, int startVertex) {
  s21::Stack<int> s;
  std::vector<std::vector<int> > graphVector = graph.getGraph();

  std::cout << "Обход графа в глубину: " << std::endl;
  for (size_t i = startVertex - 1; i < graph.getSizeGraph(); i++) {
    s.push(graphVector[i][i]);
    int j = i + 1;
    while (s.getSize() > 0) {
      if (j < graph.getSizeGraph()) {
        s.push(graphVector[i][j]);
        std::cout << graphVector[i][j] << " ";
      } else {
        s.pop();
      }
      j++;
    }
  }
  std::cout << std::endl;
}

int	*GraphAlgorithms::breadthFirstSearch(Graph &graph, int startVertex)
{}