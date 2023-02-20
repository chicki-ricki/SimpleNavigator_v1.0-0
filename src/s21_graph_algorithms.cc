#include "s21_graph_algorithms.h"

GraphAlgorithms::GraphAlgorithms() {}

GraphAlgorithms &GraphAlgorithms::operator=(const GraphAlgorithms &rhs) {
  (void) rhs;
  return (*this);
}

GraphAlgorithms::GraphAlgorithms(const GraphAlgorithms &src) : GraphAlgorithms() {
  *this = src;
}

GraphAlgorithms &GraphAlgorithms::operator=(GraphAlgorithms &&gg) {
  (void) gg;
  return (*this);
}

GraphAlgorithms::GraphAlgorithms(GraphAlgorithms &&gg) : GraphAlgorithms() {
  *this = gg;
}

std::vector<int> GraphAlgorithms::depthFirstSearch(Graph &graph, int startVertex) {
  s21::Stack<int> s;
  std::vector<int> rez;
  std::vector<std::vector<int> > graphVector = graph.getGraph();

std::cout << "Обход графа в глубину: " << std::endl;
  for (size_t i = startVertex - 1; i < graph.getSizeGraph(); i++) {
    s.push(graphVector[i][i]);
    size_t j = i + 1;
    while (s.getSize() > 0) {
      if (j < graph.getSizeGraph()) {
        s.push(graphVector[i][j]);
std::cout << graphVector[i][j] << " ";
        rez.push_back(j);
      } else {
        s.pop();
      }
      j++;
    }
  }
std::cout << std::endl;
  return (rez);
}

// int	*GraphAlgorithms::breadthFirstSearch(Graph &graph, int startVertex) {
//   (void) graph;
//   (void) startVertex;
//   return (0);
// }
