#ifndef S21_GRAPH_ALGORITHMS_H
# define S21_GRAPH_ALGORITHMS_H

# include "s21_graph.h"

typedef struct TsmResult {
	int*	vertices;// массив с искомым маршрутом (с порядком обхода вершин). Вместо int* можно использовать std::vector<int>
	double	distance;// длина этого маршрута
};

class Greaph;

class GraphAlgorithms
{
public:
	int			*depthFirstSearch(Graph &, int);// - нерекурентный поиск в глубину в графе от заданной вершины. Функция должна возвращать массив, содержащий в себе обойдённые вершины в порядке их обхода. При реализации этой функции обязательно использовать самописную структуру данных стек, которую предварительно стоит оформить в виде отдельной статической библиотеки
	int			*breadthFirstSearch(Graph &, int);// - поиск в ширину в графе от заданной вершины. Функция должна возвращать массив, содержащий в себе обойдённые вершины в порядке их обхода. При реализации этой функции обязательно использовать самописную структуру данных очередь, которую предварительно стоит оформить в виде отдельной статической библиотеки
	int			getShortestPathBetweenVertices(Graph &graph, int vertex1, int vertex2);// - поиск кратчайшего пути между двумя вершинами в графе с использованием алгоритма Дейкстры. Функция принимает на вход номера двух вершин и возвращает численный результат, равный наименьшему расстоянию между ними
	int			*getShortestPathsBetweenAllVertices(Graph &graph);// - поиск кратчайших путей между всеми парами вершин в графе с использованием алгоритма Флойда-Уоршелла. В качестве результата функция возвращает матрицу кратчайших путей между всеми вершинами графа
	int			*getLeastSpanningTree(Graph &graph);// - поиск наименьшего остовного дерева в графе с помощью алгоритма Прима. В качестве результата функция должна возвращать матрицу смежности для минимального остовного дерева
	TsmResult	solveTravelingSalesmanProblem(Graph &graph);// - решение задачи коммивояжера с помощью муравьиного алгоритма. Необходимо найти самый выгодный (короткий) маршрут, проходящий через все вершины графа хотя бы по одному разу с последующим возвратом в исходную вершину. В качестве результата функция должна возвращать структуру TsmResult
	// Необходимо выбрать дополнительные два алгоритма для решения задачи коммивояжера и реализовать их в виде методов класса GraphAlgorithms
};

#endif