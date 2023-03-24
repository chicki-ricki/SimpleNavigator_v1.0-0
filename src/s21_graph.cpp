#include "s21_graph.h"

Graph::Graph() : size_(0) {}

Graph &Graph::operator=(const Graph &rhs) {
  if (this != &rhs) {
    if (graph_.size() > 0) {
      graph_.clear();
    }
    size_ = rhs.size_;
    for (size_t i = 0; i < size_; i++) {
        graph_.push_back(rhs.graph_[i]);
    }
  }
  return (*this);
}

Graph::Graph(const Graph &src) { *this = src; }

Graph &Graph::operator=(Graph &&gg) {
  if (this != &gg) {
    if (graph_.size() > 0) {
      graph_.clear();
    }
    size_ = gg.size_;
    graph_ = std::move(gg.graph_);
    matrix_ = gg.matrix_;
    gg.graph_.clear();
    gg.size_ = 0;
  }
  return (*this);
}

Graph::Graph(Graph &&gg) { *this = std::move(gg); }

Graph::~Graph() {
  if (graph_.size() > 0) {
    graph_.clear();	
  }
  size_ = 0;
}

int Graph::checkGraph() {
  size_t countColumn;
  if (size_ < 2) {
    return (2);  // empty file or matrix without edges
  }
  if (graph_.size() != size_) {
    return (3);  // graph has strings no equal size_
  }
  for (std::vector<std::vector<int> >::iterator it = graph_.begin(); it != graph_.end(); it++) {
    countColumn = 0;
    for (std::vector<int>::iterator it2 = it->begin(); it2 != it->end(); it2++) {
      countColumn++;
    }
    if (countColumn != size_) {
      return (4);  // graph has column no equal size_
    }
  }
  return (0);
}

int Graph::loadGraphFromFile(std::string filename) {
  std::ifstream inFile(filename);
  std::string line;
  size_t i = 0;
  int check = 0;

  if (inFile.is_open() != true) {
    return (1);
  }
  inFile >> size_;
  getline(inFile, line);
  getline(inFile, line);
  while (line != "") {
    graph_.push_back(makeVector(line, ' '));
    i++;
    line = "";
    getline(inFile, line);
  }
  inFile.close();
  if ((check = checkGraph()) != 0) {
    return (check);
  }
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
  std::string rez = "graph {\n";
  size_t i = 0;
  size_t j;

  while (i < size_) {
    rez = rez + "\t" + std::to_string(i + 1) + ";\n";
    i++;
  }
  i = 0;
  while (i < size_) {
    j = i + 1;
    while (j < size_) {
      if (graph_[i][j] != 0) {
        rez = rez + "\t" + std::to_string(i + 1) + delim + std::to_string(j + 1) +
              " [weight=" + std::to_string(graph_[i][j]) + "];\n";
      }
      j++;
    }
    i++;
  }
  return (rez);
}

std::string Graph::unsimmetricGraph(std::string delim) {
  std::string rez = "digraph {\n";
  size_t i = 0;
  size_t j;

  while (i < size_) {
    rez = rez + "\t" + std::to_string(i + 1) + ";\n";
    i++;
  }
  i = 0;
  while (i < size_) {
    j = 0;
    while (j < size_) {
      if (graph_[i][j] != 0 && (graph_[i][j] != graph_[j][i] || i < j)) {
        rez = rez + "\t" + std::to_string(i + 1) + delim + std::to_string(j + 1) +
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

  if (graphSimmetric() == 0) {
    rez += simmetricGraph(" -- ");
  } else {
    rez += unsimmetricGraph(" -> ");
  }
  rez += "}";
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

int	Graph::checkStringIsDigit(std::string str) {
	for(char c : str) {
		if (std::isdigit(c) == 0) {
			return (1);
		}
	}
	return (0);
}

std::vector<int> Graph::makeVector(std::string const &str, char c) {
  std::stringstream ss(str);
  std::string s;
  std::vector<int> rez;

  while (getline(ss, s, c)) {
    if (s != "" && checkStringIsDigit(s) == 0) {
		rez.push_back(std::stoi(s));
    }
  }
  return (rez);
}
