#ifndef S21_GRAHP_H
# define S21_GRAHP_H
# include <iostream>

class Graph
{
public:
	void	loadGraphFromFile(std::string filename);// - загрузка графа из файла в формате матрицы смежности
	void	exportGraphToDot(std::string filename);// - выгрузка графа в файл в формате dot
};

#endif