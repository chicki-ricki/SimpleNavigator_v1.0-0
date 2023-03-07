// #ifndef S21_GRAPH_ALGORITHMS_H
// #define S21_GRAPH_ALGORITHMS_H
#pragma once

#include <algorithm>

#include "s21_graph.h"

struct TsmResult {
  int *vertices;// массив с искомым маршрутом (с порядком обхода вершин). Вместо int* можно использовать std::vector<int>
  double distance;// длина этого маршрута
};

class Graph;

class GraphAlgorithms {
 public:
  GraphAlgorithms();
  GraphAlgorithms &operator=(const GraphAlgorithms &);
  GraphAlgorithms(const GraphAlgorithms &);
  GraphAlgorithms &operator=(GraphAlgorithms &&);
  GraphAlgorithms(GraphAlgorithms &&);
  // GraphAlgorithms(std::initializer_list<T> const &);
  // ~GraphAlgorithms();
  /* - нерекурентный поиск в глубину в графе от заданной вершины. Функция должна
  возвращать массив, содержащий в себе обойдённые вершины в порядке их обхода. 
  При реализации этой функции обязательно использовать самописную структуру 
  данных стек, которую предварительно стоит оформить в виде отдельной 
  статической библиотеки:
  */
  std::vector<int> depthFirstSearch(Graph &, int);
  /* - поиск в ширину в графе от заданной вершины. Функция должна возвращать 
  массив, содержащий в себе обойдённые вершины в порядке их обхода. При 
  реализации этой функции обязательно использовать самописную структуру данных 
  очередь, которую предварительно стоит оформить в виде отдельной статической 
  библиотеки:
  */
  // int *breadthFirstSearch(Graph &, int);
  /* - поиск кратчайшего пути между двумя вершинами в графе с использованием 
  алгоритма Дейкстры. Функция принимает на вход номера двух вершин и возвращает 
  численный результат, равный наименьшему расстоянию между ними:
  */
  int getShortestPathBetweenVertices(Graph &, int, int);
  /* - поиск кратчайших путей между всеми парами вершин в графе с 
  использованием алгоритма Флойда-Уоршелла. В качестве результата функция 
  возвращает матрицу кратчайших путей между всеми вершинами графа:
  */
  int **getShortestPathsBetweenAllVertices(Graph &graph);
  /* - поиск наименьшего остовного дерева в графе с помощью алгоритма Прима. 
  В качестве результата функция должна возвращать матрицу смежности для 
  минимального остовного дерева:
  */
  // int *getLeastSpanningTree(Graph &graph);
  /* - решение задачи коммивояжера с помощью муравьиного алгоритма. Необходимо 
  найти самый выгодный (короткий) маршрут, проходящий через все вершины графа 
  хотя бы по одному разу с последующим возвратом в исходную вершину. В качестве
  результата функция должна возвращать структуру TsmResult:
  */
  // TsmResult solveTravelingSalesmanProblem(Graph &graph);
  /* Необходимо выбрать дополнительные два алгоритма для решения задачи 
  коммивояжера и реализовать их в виде методов класса GraphAlgorithms
  */
 private:
  int fillStack(s21::Stack<int> &, std::vector<int>, std::vector<int>);
  int checkElem(int, std::vector<int> &);
  void firstFillArray(int **, Graph &);
  int minElem(int, int);
};

// #endif