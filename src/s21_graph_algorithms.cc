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

int GraphAlgorithms::checkElem(int num, std::vector<int> &vizit) {
  for (std::vector<int>::iterator it = vizit.begin(); it != vizit.end(); it++) {
    if (num == *it) {
      return (1);
    }
  }
  return (0);
}

int GraphAlgorithms::fillStack(s21::Stack<int> &rez, std::vector<int> vec, std::vector<int> vizit) {
  size_t i = 0;

  while (i < vec.size()) {
    if (vec[i] != 0 && checkElem(i, vizit) == 0) {
      rez.push(i);
    }
    i++;
  }
  return (0);
}

std::vector<int> GraphAlgorithms::depthFirstSearch(Graph &graph, int startVertex) {
  int index = startVertex - 1;
  s21::Stack<int> s;
  std::vector<int> vizit;
  std::vector<std::vector<int> > graphVector = graph.getGraph();

  vizit.push_back(index);
  fillStack(s, graphVector[index], vizit);
  while (s.getSize() > 0) {
    if (checkElem(s.peek(), vizit) == 0) {  // 0 - непосещенная вершина, 1 - посещенная
      vizit.push_back(s.peek());
      fillStack(s, graphVector[s.peek()], vizit);//?
      // s.pop();//?
    } else {
      s.pop();//?
    }
  }


// std::cout << "Обход графа в глубину: " << std::endl;
//   for (size_t i = startVertex - 1; i < graph.getSizeGraph(); i++) {
//     s.push(graphVector[i][i]);
//     rez.push_back(i + 1);
//     size_t j = i + 1;
//     while (s.getSize() > 0) {
//       if (j < graph.getSizeGraph()) {
//         s.push(graphVector[i][j]);
// std::cout << graphVector[i][j] << " ";
//         rez.push_back(j + 1);
//       } else {
//         s.pop();
//       }
//       j++;
//     }
//   }
// std::cout << std::endl;
  return (vizit);
}

// int	*GraphAlgorithms::breadthFirstSearch(Graph &graph, int startVertex) {
//   (void) graph;
//   (void) startVertex;
//   return (0);
// }
