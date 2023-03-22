#include "s21_graph_algorithms.h"

GraphAlgorithms::GraphAlgorithms() {}

GraphAlgorithms &GraphAlgorithms::operator=(const GraphAlgorithms &rhs) {
  (void)rhs;
  return (*this);
}

GraphAlgorithms::GraphAlgorithms(const GraphAlgorithms &src) { *this = src; }

GraphAlgorithms &GraphAlgorithms::operator=(GraphAlgorithms &&gg) {
  (void)gg;
  return (*this);
}

GraphAlgorithms::GraphAlgorithms(GraphAlgorithms &&gg) { *this = gg; }

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
    } else {
      queue.pop();
    }
  }
  convertToArr(arr, visited);
  return (arr);
}

int GraphAlgorithms::getShortestPathBetweenVertices(Graph &graph, int v1,
                                                    int v2) {
  std::vector<int> distance;
  std::vector<int> vizit;
  int index = v1 - 1;
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
  return (distance[v2 - 1]);
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
  std::vector<std::vector<int> > graph_arr = graph.getGraph();
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
    if (graph_arr[x][y] == graph_arr[y][x]) {
      res[x][y] = res[y][x] = min;
    } else {
      res[x][y] = min;
    }
    vizit[y] = 1;
    edgeNum++;
  }
  delete[] vizit;
  return (res);
}

double GraphAlgorithms::probability(size_t to, Ant &ant, double **distance,
                                    double **pheromone, size_t vertex) {
  int ratio = 1;
  for (size_t i = 0; i < ant.data.vertices.size(); i++) {
    if ((int)to == ant.data.vertices[i]) {
      ratio = 10000;
    }
    if (ant.data.vertices.size() > 1 &&
        ant.data.vertices[ant.data.vertices.size() - 2] == (int)to) {
      ratio = 100000;
    }
  }
  std::random_device rd;   // non-deterministic generator
  std::mt19937 gen(rd());  // to seed mersenne twister.
  std::uniform_int_distribution<> rNumberInt(
      1, RND_MAX);  // distribute results between 1 and RND_MAX inclusive.

  double sum = 0.0;
  double ret;
  size_t from = ant.data.vertices[ant.data.vertices.size() - 1];
  for (size_t j = 0; j < vertex; j++) {
    int flag = 1;
    for (size_t i = 0; i < ant.data.vertices.size(); i++) {
      if ((int)j == ant.data.vertices[i]) {
        flag = 0;
      }
      if (flag == 1) {
        sum += pow(pheromone[from][j], ALPHA) * pow(distance[from][j], BETA);
      }
    }
  }
  if (ant.exitFlag == 1 && ant.countVizit == vertex - 1 &&
      distance[from][to] != 0.0) {
    distance[from][to] = 1;
  }
  ret = (pow(pheromone[from][to], ALPHA) * pow((distance[from][to]), BETA)) *
        rNumberInt(gen) / ((sum + 1) * ratio);
  return (ret);
}

void GraphAlgorithms::freeArr(double **arr, size_t count) {
  for (size_t i = 0; i < count; i++) {
    if (arr[i]) {
      delete[] arr[i];
    }
  }
  if (arr) {
    delete[] arr;
  }
}

void GraphAlgorithms::initAnts(Ant *ants, size_t graphSize) {
  size_t start = 0;
  for (int i = 0; i < ANT; i++) {
    start += 1;
    ants[i].data.distance = 0.0;
    ants[i].data.vertices.clear();
    ants[i].data.vertices.push_back(start);
    ants[i].vizit = new int[graphSize];
    for (int k = 0; k < (int)graphSize; k++) {
      ants[i].vizit[k] = 0;
    }
    ants[i].vizit[start] = 1;
    ants[i].countVizit = 1;
    ants[i].exitFlag = 0;
    ants[i].startVertex = start;
    start %= (graphSize - 1);
  }
}

void GraphAlgorithms::initData(double **distance, double **pheromone,
                               size_t graphSize, Graph &graph) {
  for (size_t i = 0; i < graphSize; i++) {
    distance[i] = new double[graphSize];
    pheromone[i] = new double[graphSize];
    for (size_t j = 0; j < graphSize; j++) {
      pheromone[i][j] = 1.0 / graphSize;
      if (graph.getGraph()[i][j] != 0) {
        distance[i][j] = 1.0 / graph.getGraph()[i][j];
      } else {
        distance[i][j] = 0.0;
      }
    }
  }
}

void GraphAlgorithms::rangePheromone(Ant &ant, double **pheromone) {
  for (size_t m = 0; m < ant.data.vertices.size() - 1; m++) {
    size_t from = ant.data.vertices[m % ant.data.vertices.size()];
    size_t to = ant.data.vertices[(m + 1) % ant.data.vertices.size()];

    pheromone[from][to] += Q / ant.data.distance;
  }
}

void GraphAlgorithms::checkBestWay(Ant &ant, TsmResult &way) {
  if (ant.data.distance < way.distance || way.distance < 0) {
    way.distance = ant.data.distance;
    way.vertices.clear();
    for (size_t x = 0; x < ant.data.vertices.size(); x++) {
      way.vertices.push_back(ant.data.vertices[x] + 1);
    }
  }
}

void GraphAlgorithms::updateAnt(Ant &ant, int graphSize) {
  ant.data.distance = 0.0;
  size_t start = ant.data.vertices[0];
  ant.data.vertices.clear();
  ant.data.vertices.push_back(start);
  for (int k = 0; k < (int)graphSize; k++) {
    ant.vizit[k] = 0;
  }
  ant.vizit[start] = 1;
  ant.countVizit = 1;
  ant.exitFlag = 0;
  ant.startVertex = start;
}

void GraphAlgorithms::updatePheromone(double **pheromone, size_t graphSize) {
  for (size_t i = 0; i < graphSize; i++) {
    for (size_t j = 0; j < graphSize; j++) {
      if (i != j) {
        pheromone[i][j] *= (1 - RHO);
      }
    }
  }
}

int GraphAlgorithms::ckeckValidGraph(Graph &graph) {
  int column = 0;
  int str = 0;
  for (size_t i = 0; i < graph.getSizeGraph(); i++) {
    for (size_t j = 0; j < graph.getSizeGraph(); j++) {
      str += graph.getGraph()[i][j];
      column += graph.getGraph()[j][i];
    }
    if (str == 0 || column == 0) {
      return (1);
    } else {
      str = 0;
      column = 0;
    }
  }
  return (0);
}

TsmResult GraphAlgorithms::solveTravelingSalesmanProblem(Graph &graph) {
  TsmResult way;
  way.distance = -1;
  way.vertices.clear();
  size_t graphSize = graph.getSizeGraph();
  double **distance = new double *[graphSize];
  double **pheromone = new double *[graphSize];
  Ant ants[ANT];
  int count_blackAnt = 0, count_whiteAnt = 0;

  if (ckeckValidGraph(graph) == 1) {
    s21::exitError(
        "Error: impossible to solve the salesman's problem with a "
        "giving graph");
  }
  initData(distance, pheromone, graphSize, graph);
  initAnts(ants, graphSize);
  for (int i = 0; i < T_MAX; i++) {  // основной цикл
    // цикл по муравьям
    for (int k = 0; k < ANT; k++) {
      // поиск маршрута для текущего муравья
      while (ants[k].countVizit < graphSize &&
             ants[k].data.vertices.size() < (2 * graphSize)) {
        int jMax = -1;
        double pMax = 0.0;
        for (size_t j = 0; j < graphSize; j++) {
          double p = probability(j, ants[k], distance, pheromone, graphSize);
          if (p && p > pMax) {
            pMax = p;
            jMax = j;
          }
        }
        ants[k].data.distance +=
            graph.getGraph()[ants[k].data.vertices.back()][jMax];
        ants[k].data.vertices.push_back(jMax);
        if (ants[k].vizit[jMax] == 0) {
          ants[k].vizit[jMax] = 1;
          ants[k].countVizit++;
        }
        if (ants[k].countVizit == graphSize && ants[k].exitFlag == 0) {
          ants[k].exitFlag = 1;
          ants[k].vizit[ants[k].startVertex] = 0;
          ants[k].countVizit--;
        }
      }
      rangePheromone(ants[k], pheromone);
      if (ants[k].countVizit == graphSize) {
        checkBestWay(ants[k], way);
        count_whiteAnt++;
      } else
        count_blackAnt++;
      updateAnt(ants[k], (int)graphSize);
    }
    updatePheromone(pheromone, graphSize);
  }
  freeArr(distance, graphSize);
  freeArr(pheromone, graphSize);
  return (way);
}

int GraphAlgorithms::fillStack(s21::Stack<int> &r, std::vector<int> v,
                               std::vector<int> viz) {
  size_t i = v.size() - 1;

  while (i > 0) {
    if (v[i] != 0 && checkElem(i, viz) == 0) {
      r.push(i);
    }
    i--;
  }
  return (0);
}

int GraphAlgorithms::fillQueue(s21::Queue<int> &r, std::vector<int> v,
                               std::vector<int> viz) {
  size_t i = 0;
  while (i < v.size()) {
    if (v[i] != 0 && checkElem(i, viz) == 0) {
      r.push(i);
    }
    i++;
  }
  return (0);
}

int GraphAlgorithms::checkElem(int num, std::vector<int> &viz) {
  for (std::vector<int>::iterator it = viz.begin(); it != viz.end(); it++) {
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
