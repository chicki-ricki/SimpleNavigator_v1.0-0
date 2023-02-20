#include "s21_graph.h"

Graph::Graph() : size_(0) {}

Graph &Graph::operator=(const Graph &rhs) {
  size_ = rhs.size_;
  for (int i = 0; i < size_; i++) {
    for (int j = 0; j < size_; j++) {
      graph_[i][j] = rhs.graph_[i][j];
    }
  }
  return (*this);
}

Graph::Graph(const Graph &src) : Graph() {
  *this = src;
}

Graph &Graph::operator=(Graph &&gg) {
  if (graph_.size() > 0) {
    graph_.clear();
  }
  for (int i = 0; i < size_; i++) {
    for (int j = 0; j < size_; j++) {
      graph_[i][j] = gg.graph_[i][j];
    }
  }
  size_ = gg.size_;
  gg.graph_.clear();
  gg.size_ = 0;
}

Graph::Graph(Graph &&gg) : Graph() {
  *this = gg;
}

// Graph::Graph(std::initializer_list<std::vector<std::vector<int> > > &init) {
//   for (int i = 0; i < size_; i++) {
//     for (int j = 0; j < size_; j++) {
//       graph_[i][j] = init[i][j];
//     }
//   }
// }

Graph::~Graph() {
  if (graph_.size() > 0) {
    graph_.clear();
  }
}

int Graph::loadGraphFromFile(std::string filename) {}

int Graph::exportGraphToDot(std::string filename) {}