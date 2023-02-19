#ifndef S21_GRAHP_H
#define S21_GRAHP_H

#include <iostream>
#include <vector>

#include "s21_containers/s21_containers.h"

class Graph {
 public:
  Graph();
  // 5 constructors + destuctor
  // - загрузка графа из файла в формате матрицы смежности:
  int loadGraphFromFile(std::string);
  // - выгрузка графа в файл в формате dot:
  int exportGraphToDot(std::string);
  std::vector<std::vector<int> > &getGraph();

 private:
  std::vector<std::vector<int> > graph_;
};

#endif