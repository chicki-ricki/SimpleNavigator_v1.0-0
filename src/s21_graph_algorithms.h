#pragma once

#include <math.h>

#include <algorithm>
#include <cstring>
#include <ctime>
#include <random>

#include "s21_graph.h"

#define ALPHA 2     // вес фермента
#define BETA 0.5      // коэффициент эвристики
#define T_MAX 1000  // количество итераций
#define M 20         // количество муравьев в колонии
#define Q 100      // некоторый регулируемый параметр
#define RHO 0.9  // коэффициент испарения феромона
#define RND_MAX 4  // разброс случайности

struct TsmResult {
  std::vector<int>
      vertices;  // массив с искомым маршрутом (с порядком обхода вершин).
                 // Вместо int* можно использовать std::vector<int>
  double distance;  // длина этого маршрута
};

struct Ant {
  TsmResult data;
  int *vizit;
  size_t countVizit;
  int startVertex;
  int exitFlag;
};

class Graph;

class GraphAlgorithms {
 public:
  GraphAlgorithms();
  GraphAlgorithms &operator=(const GraphAlgorithms &);
  GraphAlgorithms(const GraphAlgorithms &);
  GraphAlgorithms &operator=(GraphAlgorithms &&);
  GraphAlgorithms(GraphAlgorithms &&);
  ~GraphAlgorithms();
  /* - нерекурентный поиск в глубину в графе от заданной вершины. Функция должна
  возвращать массив, содержащий в себе обойдённые вершины в порядке их обхода.
  При реализации этой функции обязательно использовать самописную структуру
  данных стек, которую предварительно стоит оформить в виде отдельной
  статической библиотеки:
  */
  int *depthFirstSearch(Graph &, int);
  /* - поиск в ширину в графе от заданной вершины. Функция должна возвращать
  массив, содержащий в себе обойдённые вершины в порядке их обхода. При
  реализации этой функции обязательно использовать самописную структуру данных
  очередь, которую предварительно стоит оформить в виде отдельной статической
  библиотеки:
  */
  int *breadthFirstSearch(Graph &, int);
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
  int **getLeastSpanningTree(Graph &graph);
  /* - решение задачи коммивояжера с помощью муравьиного алгоритма. Необходимо
  найти самый выгодный (короткий) маршрут, проходящий через все вершины графа
  хотя бы по одному разу с последующим возвратом в исходную вершину. В качестве
  результата функция должна возвращать структуру TsmResult:
  */
  TsmResult solveTravelingSalesmanProblem(Graph &graph);
  /* Необходимо выбрать дополнительные два алгоритма для решения задачи
  коммивояжера и реализовать их в виде методов класса GraphAlgorithms
  */
 private:
  int fillStack(s21::Stack<int> &, std::vector<int>, std::vector<int>);
  int fillQueue(s21::Queue<int> &, std::vector<int>, std::vector<int>);
  int checkElem(int, std::vector<int> &);
  void firstFillArray(int **, Graph &);
  int minElem(int, int);
  void convertToArr(int *, std::vector<int> &);
  double probability(size_t, Ant &, double **, double **, size_t);
  static void freeArr(double **, size_t);
  // инициализация муравьев
  void initAnts(Ant *, size_t);
  // инициализация данных о расстоянии и количестве феромона
  void initData(double **, double **, size_t, Graph &);
  // оставляем феромон на пути муравья
  void rangePheromone(Ant &, double **);
  // проверка на лучшее решение
  void checkBestWay(Ant &, TsmResult &);
  // обновление муравья
  void updateAnt(Ant &);
  // обновление феромонов с учетом коэффициента испарения
  void updatePheromone(double **, size_t);
  int ckeckValidGraph(Graph &);
};

// #endif
