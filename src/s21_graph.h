#ifndef S21_GRAHP_H
#define S21_GRAHP_H

#include <fstream>
#include <sstream>
#include <vector>

#include "s21_containers/s21_containers.h"

class Graph {
 public:
  Graph();
  Graph &operator=(const Graph &);
  Graph(const Graph &);
  Graph &operator=(Graph &&);
  Graph(Graph &&);
  ~Graph();
  int **matrix_;  //для проверки конструктора перемещения

  // загрузка графа из файла в формате матрицы смежности:
  int loadGraphFromFile(std::string);
  // выгрузка графа в файл в формате dot:
  int exportGraphToDot(std::string);
  std::vector<std::vector<int> > &getGraph();
  unsigned int getSizeGraph();

 private:
  std::vector<std::vector<int> > graph_;
  unsigned int size_;
  std::vector<int> makeVector(std::string const &, char);
  std::string convertGraphToDot();
  int graphSimmetric();
  std::string simmetricGraph(std::string);
  std::string unsimmetricGraph(std::string);
  int checkGraph();
};

#endif
