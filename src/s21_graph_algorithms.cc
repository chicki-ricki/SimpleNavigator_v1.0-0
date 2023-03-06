#include "s21_graph_algorithms.h"

GraphAlgorithms::GraphAlgorithms() {}

GraphAlgorithms &GraphAlgorithms::operator=(const GraphAlgorithms &rhs) {
  (void)rhs;
  return (*this);
}

GraphAlgorithms::GraphAlgorithms(const GraphAlgorithms &src):
    GraphAlgorithms() {
  *this = src;
}

GraphAlgorithms &GraphAlgorithms::operator=(GraphAlgorithms &&gg) {
  (void)gg;
  return (*this);
}

GraphAlgorithms::GraphAlgorithms(GraphAlgorithms &&gg) : GraphAlgorithms() {
  *this = gg;
}

std::vector<int> GraphAlgorithms::depthFirstSearch(Graph &graph, int startVertex) {
  int index = startVertex - 1;
  s21::Stack<int> s;
  std::vector<int> vizit;
  std::vector<std::vector<int> > graphVector = graph.getGraph();

  vizit.push_back(index);
  fillStack(s, graphVector[index], vizit);
  while (s.getSize() > 0) {
    // 0 - непосещенная вершина, 1 - посещенная
    if (checkElem(s.peek(), vizit) == 0) {
      vizit.push_back(s.peek());
      fillStack(s, graphVector[s.peek()], vizit);
    } else {
      s.pop();
    }
  }
  return (vizit);
}

// int	*GraphAlgorithms::breadthFirstSearch(Graph &graph, int startVertex) {
//   (void) graph;
//   (void) startVertex;
//   return (0);
// }

void GraphAlgorithms::handlerDayxtra(std::vector<int> vec, std::vector<int> &distance, std::vector<int> &vizit, int num) {
  for (size_t i = 0; i < vec.size(); i++) {
    if (checkElem(i, vizit) == 0) {
      if ((distance[num] + vec[i]) < distance[i]) {
        distance[i] = distance[num] + vec[i];
      }
    }
  }
}

int GraphAlgorithms::getShortestPathBetweenVertices(Graph &graph, int vertex1, int vertex2) {
  std::vector<int> distance;
  std::vector<int> vizit;
  int index = vertex1 - 1;
  int minindex;
  int min;
  int ret = 1;
  std::vector<std::vector<int> > graphVector = graph.getGraph();
  int tmp;

(void)vertex2;

  // init distance
  for (size_t i = 0; i < graphVector.size(); i++) {
    distance.push_back(10000);
    vizit.push_back(1);
  }
  distance[index] = 0;
  while (ret || minindex < 10000) {
    minindex = 10000;
    min = 10000;
    for (size_t i = 0; i < graphVector.size(); i++) {
      if (vizit[i] == 1 && distance[i] < min) {
        min = distance[i];
        minindex = i;
      }
    }
    if (minindex != 10000) {
      for (size_t i = 0; i < graphVector.size(); i++) {
        if (graphVector[minindex][i] > 0) {
          tmp = min + graphVector[minindex][i];
          if (tmp < distance[i]) {
            distance[i] = tmp;
          }
        }
      }
      vizit[minindex] = 0;
    }
    ret = 0;
  }


// for (std::vector<int>::iterator it = distance.begin(); it != distance.end(); it++) {
//   std::cout << *it << " ";
// }
// std::cout << std::endl;


  // vizit.push_back(index);
  // while (vizit.size() < graph.getSizeGraph()) {
  //   handlerDayxtra(graph.getGraph()[index], distance, vizit, index);

  // }
  return (distance[vertex2 - 1]);
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
  size_t i = vec.size() - 1;

  while (i > 0) {
    if (vec[i] != 0 && checkElem(i, vizit) == 0) {
      rez.push(i);
    }
    i--;
  }
  return (0);
}
