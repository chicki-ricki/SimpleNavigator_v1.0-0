#include "s21_graph.h"

Graph::Graph() : size_(0) {}

Graph &Graph::operator=(const Graph &rhs) {
  size_ = rhs.size_;
  for (size_t i = 0; i < size_; i++) {
    for (size_t j = 0; j < size_; j++) {
      graph_[i][j] = rhs.graph_[i][j];
    }
  }
  return (*this);
}

Graph::Graph(const Graph &src) : Graph() { *this = src; }

Graph &Graph::operator=(Graph &&gg) {
  if (graph_.size() > 0) {
    graph_.clear();
  }
  for (size_t i = 0; i < size_; i++) {
    for (size_t j = 0; j < size_; j++) {
      graph_[i][j] = gg.graph_[i][j];
    }
  }
  size_ = gg.size_;
  gg.graph_.clear();
  gg.size_ = 0;
  return (*this);
}

Graph::Graph(Graph &&gg) : Graph() { *this = gg; }

Graph::~Graph() {
  if (graph_.size() > 0) {
    graph_.clear();
  }
}

int Graph::loadGraphFromFile(std::string filename) {
  std::ifstream inFile(filename);
  std::string line;
  size_t i = 0;

  if (inFile.is_open() != true) {
    // s21::exitError("Error: file with graph is not open");
    return (1);
  }
  inFile >> size_;
  getline(inFile, line);
  while (i < size_) {
    getline(inFile, line);
    graph_.push_back(makeVector(line, ' '));
    i++;
  }
  inFile.close();
  return (0);
}

int Graph::graphSimmetric() {
  int k = 0;
  for (size_t i = 0; i < size_; i++) {
    for (size_t j = 0; j < size_; j++) {
      if (graph_[i][j] != graph_[j][i]) {
        k++;
      }
    }
  }
  if (k == 0) {
    return (0);
  } else {
    return (1);
  }
}

std::string Graph::simmetricGraph(std::string delim) {
  std::string rez = "";
  size_t i = 0;
  size_t j;

  while (i < size_) {
    j = i + 1;
    while (j < size_) {
      if (graph_[i][j] != 0) {
        rez = rez + std::to_string(i + 1) + delim + std::to_string(j + 1) +
              " [weight=" + std::to_string(graph_[i][j]) + "];\n";
      }
      j++;
    }
    i++;
  }
  return (rez);
}

std::string Graph::unsimmetricGraph(std::string delim) {
  std::string rez = "";
  size_t i = 0;
  size_t j;

  while (i < size_) {
    j = 0;
    while (j < size_) {
      if (graph_[i][j] != 0 && (graph_[i][j] != graph_[j][i] || i < j)) {
        rez = rez + std::to_string(i + 1) + delim + std::to_string(j + 1) +
              " [weight=" + std::to_string(graph_[i][j]) + "];\n";
      }
      j++;
    }
    i++;
  }
  return (rez);
}

std::string Graph::convertGraphToDot() {
  std::string rez = "";
  std::string delim;
  size_t i = 0;
  size_t j;

  while (i < size_) {
    rez = rez + std::to_string(i + 1) + ";\n";
    i++;
  }
  i = 0;
  if (graphSimmetric() == 0) {
    delim = " -- ";
    rez += simmetricGraph(delim);
  } else {
    delim = " -> ";
    rez += unsimmetricGraph(delim);
  }
  // while (i < size_) {
  //   j = i + 1;
  //   while (j < size_) {
  //     if (graph_[i][j] != 0) {
  //       rez = rez + std::to_string(i + 1) + delim + std::to_string(j + 1) +
  //             " [weight=" + std::to_string(graph_[i][j]) + "];\n";
  //     }
  //     j++;
  //   }
  //   i++;
  // }
  return (rez);
}

int Graph::exportGraphToDot(std::string filename) {
  std::ofstream outFile;

  outFile.open(filename);
  if (outFile.is_open() != true) {
    return (1);
  }
  outFile << convertGraphToDot() << std::endl;
  outFile.close();
  return (0);
}

std::vector<std::vector<int> > &Graph::getGraph() { return (graph_); }

unsigned int Graph::getSizeGraph() { return (size_); }

std::vector<int> Graph::makeVector(std::string const &str, char c) {
  std::stringstream ss(str);
  std::string s;
  std::vector<int> rez;

  while (getline(ss, s, c)) {
    if (s != "") {
      rez.push_back(std::stoi(s));
    }
  }
  return (rez);
}
