#ifndef S21_GRAHP_H
#define S21_GRAHP_H

#include <iostream>
#include <vector>

# include "s21_containers/s21_containers.h"

class Graph
{
	std::vector< std::vector<int> > graph_;
public:
	Graph();
	//5 constructors + destuctor
	int loadGraphFromFile(std::string);  // - загрузка графа из файла в формате матрицы смежности
	int exportGraphToDot(std::string);  // - выгрузка графа в файл в формате dot
	std::vector< std::vector<int> > &getGraph();
};

#endif