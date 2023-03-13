#include "s21_graph_algorithms.h"

GraphAlgorithms::GraphAlgorithms() {}

GraphAlgorithms &GraphAlgorithms::operator=(const GraphAlgorithms &rhs) {
  (void)rhs;
  return (*this);
}

GraphAlgorithms::GraphAlgorithms(const GraphAlgorithms &src) : GraphAlgorithms() {
  *this = src;
}

GraphAlgorithms &GraphAlgorithms::operator=(GraphAlgorithms &&gg) {
  (void)gg;
  return (*this);
}

GraphAlgorithms::GraphAlgorithms(GraphAlgorithms &&gg) : GraphAlgorithms() {
  *this = gg;
}

GraphAlgorithms::~GraphAlgorithms() {}

void GraphAlgorithms::convertToArr(int *rez, std::vector<int> &vec) {
  for (size_t i = 0; i < vec.size(); i++) {
    rez[i] = vec[i] + 1;
  }
}

int *GraphAlgorithms::depthFirstSearch(Graph &graph, int startVertex) {
  int index = startVertex - 1;
  s21::Stack<int> s;
  std::vector<int> vizit;
  std::vector<std::vector<int> > graphVector = graph.getGraph();
  int *arr = new int[graph.getSizeGraph()];

  vizit.push_back(index);
  fillStack(s, graphVector[index], vizit);
  while (s.getSize() > 0) {
    // 0 - непосещенная вершина, 1 - посещенная
    if (checkElem(s.peek(), vizit) == 0) {
      vizit.push_back(s.peek());
      fillStack(s, graphVector[s.peek()], vizit);
    } else {
      s.pop();
    }
  }
  convertToArr(arr, vizit);
  return (arr);
}

int *GraphAlgorithms::breadthFirstSearch(Graph &graph, int startVertex) {
  s21::Queue<int> queue;
  int index = startVertex - 1;
  std::vector<int> visited;
  std::vector<std::vector<int> > graphVector = graph.getGraph();
  int *arr = new int[graph.getSizeGraph()];

  visited.push_back(index);
  fillQueue(queue, graphVector[index], visited);
  while (queue.getSize() > 0) {
    if (checkElem(queue.peek(), visited) == 0) {
      visited.push_back(queue.peek());
      fillQueue(queue, graphVector[queue.peek()], visited);
    }
    else {
      queue.pop();
    }
  }
  convertToArr(arr, visited);
  return (arr);
}

int GraphAlgorithms::getShortestPathBetweenVertices(Graph &graph, int vertex1, int vertex2) {
  std::vector<int> distance;
  std::vector<int> vizit;
  int index = vertex1 - 1;
  int minindex;
  int min;
  int ret = 1;
  std::vector<std::vector<int> > graphVector = graph.getGraph();
  int tmp;

  // init distance
  for (size_t i = 0; i < graphVector.size(); i++) {
    distance.push_back(10000);
    vizit.push_back(1);
  }
  distance[index] = 0;
  while (ret || minindex < 10000) {
    minindex = 10000;
    min = 10000;
    for (size_t i = 0; i < graphVector.size(); i++) {
      if (vizit[i] == 1 && distance[i] < min) {
        min = distance[i];
        minindex = i;
      }
    }
    if (minindex != 10000) {
      for (size_t i = 0; i < graphVector.size(); i++) {
        if (graphVector[minindex][i] > 0) {
          tmp = min + graphVector[minindex][i];
          if (tmp < distance[i]) {
            distance[i] = tmp;
          }
        }
      }
      vizit[minindex] = 0;
    }
    ret = 0;
  }
  return (distance[vertex2 - 1]);
}

int **GraphAlgorithms::getShortestPathsBetweenAllVertices(Graph &graph) {
  int **rez = new int *[graph.getSizeGraph()];
  for (size_t m = 0; m < graph.getSizeGraph(); m++) {
    rez[m] = new int[graph.getSizeGraph()];
  }
  firstFillArray(rez, graph);
  for (size_t k = 0; k < graph.getSizeGraph(); k++) {
    for (size_t i = 0; i < graph.getSizeGraph(); i++) {
      for (size_t j = 0; j < graph.getSizeGraph(); j++) {
        rez[i][j] = minElem(rez[i][j], rez[i][k] + rez[k][j]);
      }
    }
  }
  return (rez);
}

int **GraphAlgorithms::getLeastSpanningTree(Graph &graph) {
  int x;
  int y;
	size_t edgeNum;
	std::vector<std::vector<int>> graph_arr = graph.getGraph();
  size_t graph_size = graph.getSizeGraph();
  int *vizit = new int[graph_size];
	int **res = new int *[graph_size];
  for (size_t i = 0; i < graph_size; i++) {
    res[i] = new int[graph_size];
		memset(res[i], 0, sizeof(int) * graph_size);
  }
  memset(vizit, 0, sizeof(int) * graph_size);
  edgeNum = 0;
  vizit[0] = 1;
  while (edgeNum < graph_size - 1) {
    int min = 10000;
    x = 0;
    y = 0;
    for (size_t i = 0; i < graph_size; i++) {
      if (vizit[i] == 1) {
        for (size_t j = 0; j < graph_size; j++) {
          if (vizit[j] == 0 && graph_arr[i][j]) {
            if (min > graph_arr[i][j]) {
              min = graph_arr[i][j];
              x = i;
              y = j;
            }
          }
        }
      }
    }
		res[x][y] = res[y][x] = min;
    vizit[y] = 1;
    edgeNum++;
  }
  return (res);
}

#define ALPHA 1  // вес фермента
#define BETA 3  // коэффициент эвристики
#define T_MAX 10000  // количество итераций
#define M 20  // количество муравьев в колонии
#define Q 100  // некоторый регулируемый параметр
#define RHO 0.5  // коэффициент испарения феромона

void GraphAlgorithms::fillNotVizit(std::vector<int> &vec, size_t vertex) {
  for (size_t i = 1; i < vertex; i++) {
    vec.push_back(i);
  }
  // vec.push_back(0);
}

double GraphAlgorithms::probability(size_t to, Ant &ant, double **distance, double **pheromone, size_t vertex) {
  double sum = 0.0;
  size_t from = ant.data.vertices[ant.data.vertices.size() - 1];

  for (size_t j = 0; j < vertex; j++) {
    sum += pow(pheromone[from][j], ALPHA) * pow(distance[from][j], BETA);
  }
  for (size_t j = 0; j < vertex; j++) {
    if ((int)to == ant.notVizit[j]) {
      return ((pow(pheromone[from][to], ALPHA) * pow(distance[from][to], BETA)) / sum);
    }
  }
  return (((pow(pheromone[from][to], ALPHA) * pow(distance[from][to], BETA)) / sum) / 2);
}

TsmResult GraphAlgorithms::solveTravelingSalesmanProblem(Graph &graph) {
  TsmResult way;
  way.distance = -1;
  size_t graphSize = graph.getSizeGraph();
  double **distance = new double*[graphSize];
  double **pheromone = new double*[graphSize];
  // std::vector<int> notVizit;

  // инициализация данных о расстоянии и количестве феромона
  for (size_t i = 0; i < graphSize; i++) {
    distance[i] = new double [graphSize];
    pheromone[i] = new double [graphSize];
    for (size_t j = 0; j < graphSize; j++) {
      pheromone[i][j] = 1.0 / graphSize;
      if (graph.getGraph()[i][j] != 0) {
        distance[i][j] = 1.0 / graph.getGraph()[i][j];
      }
    }
  }

  // инициализация муравьев
  // TsmResult ants[M];
  Ant ants[M];
  for (int i = 0; i < M; i++) {
    ants[i].data.distance = 0.0;
    ants[i].data.vertices.push_back(0);
    fillNotVizit(ants[i].notVizit, graphSize);
  }
  // основной цикл
  for (int i = 0; i < T_MAX; i++) {
    // цикл по муравьям
    for (int k = 0; k < M; k++) {
      // поиск маршрута для текущего муравья
      while (ants[k].notVizit.size() > 0) {
        int jMax = -1;
        double pMax = 0.0;
        for (size_t j = 0; j < graphSize; j++) {
          double p = probability(j, ants[k], distance, pheromone, graphSize);
          if (p && p >= pMax) {
            pMax = p;
            jMax = j;
          }
        }

        ants[k].data.distance += graph.getGraph()[ants[k].data.vertices.back()][jMax];
        ants[k].data.vertices.push_back(jMax);
        ants[k].notVizit.erase(ants[i].notVizit.begin());
      }

      // оставляем феромон на пути муравья
      for (size_t m = 0; m < ants[k].data.vertices.size() - 1; m++) {
        size_t from = ants[k].data.vertices[m % ants[k].data.vertices.size()];
        size_t to = ants[k].data.vertices[(m + 1) % ants[k].data.vertices.size()];

        pheromone[from][to] += Q / ants[k].data.distance;
        pheromone[to][from] = pheromone[from][to];
      }
// std::cout << "GraphAlgorithms::solveTravelingSalesmanProblem| ending while" << std::endl;

      // проверка на лучшее решение
      if (ants[k].data.distance < way.distance || way.distance < 0) {
        way.distance = ants[k].data.distance;
        for (size_t x = 0; x < ants[k].data.vertices.size(); x++) {
          way.vertices[x] = ants[i].data.vertices[x];
        }
      }
      // обновление муравья
      ants[k].data.distance = 0;
      ants[k].data.vertices.push_back(0);
      fillNotVizit(ants[k].notVizit, graphSize);
    }
    // цикл по ребрам
    for (size_t i = 0; i < graphSize; i++) {
      for (size_t j =0; j < graphSize; j++) {
        if (i != j) {
          pheromone[i][j] *= (1 - RHO);
        }
      }
    }
  }
  return (way);
}

int GraphAlgorithms::fillStack(s21::Stack<int> &rez, std::vector<int> vec, std::vector<int> vizit) {
  size_t i = vec.size() - 1;

  while (i > 0) {
    if (vec[i] != 0 && checkElem(i, vizit) == 0) {
      rez.push(i);
    }
    i--;
  }
  return (0);
}

int GraphAlgorithms::fillQueue(s21::Queue<int> &rez, std::vector<int> vec, std::vector<int> vizit) {
  size_t i = 0;
  while (i < vec.size()) {
    if (vec[i] != 0 && checkElem(i, vizit) == 0) {
      rez.push(i);
    }
    i++;
  }
  return(0);
}

int GraphAlgorithms::checkElem(int num, std::vector<int> &vizit) {
  for (std::vector<int>::iterator it = vizit.begin(); it != vizit.end(); it++) {
    if (num == *it) {
      return (1);
    }
  }
  return (0);
}

void GraphAlgorithms::firstFillArray(int **arr, Graph &graph) {
  std::vector<std::vector<int> > matrixGraph = graph.getGraph();

  for (size_t i = 0; i < graph.getSizeGraph(); i++) {
    for (size_t j = 0; j < graph.getSizeGraph(); j++) {
      if (i == j) {
        arr[i][j] = 0;
      } else {
        if (matrixGraph[i][j] == 0) {
          arr[i][j] = 10000;
        } else {
          arr[i][j] = matrixGraph[i][j];
        }
      }
    }
  }
}

int GraphAlgorithms::minElem(int elem1, int elem2) {
  if (elem1 < elem2) {
    return (elem1);
  } else {
    return (elem2);
  }
}
