#ifndef S21_GRAHP_H
# define S21_GRAHP_H
# include <iostream>

# include "s21_stack.h"
# include "s21_queue.h"

class Graph
{
public:
	void	loadGraphFromFile(std::string);// - загрузка графа из файла в формате матрицы смежности
	void	exportGraphToDot(std::string);// - выгрузка графа в файл в формате dot
};

#endif