#include "s21_graph_algorithms.h"

#include <gtest/gtest.h>

TEST(depthFirstSearch, RightData) {
  int rez[5]{1, 2, 4, 3, 5};
  Graph graph;
  GraphAlgorithms graphAlg;
  int start = 1;
  int *exp = new int[5];

  graph.loadGraphFromFile("graph_files/good/graph_5.txt");
  exp = graphAlg.depthFirstSearch(graph, start);
  for (size_t i = 0; i < graph.getSizeGraph(); i++) {
    EXPECT_EQ(rez[2], exp[2]);
  }
}

TEST(depthFirstSearch, StartVertexOutOfRange) {
  int start = 6;
  Graph graph;
  GraphAlgorithms graphAlg;

  graph.loadGraphFromFile("graph_files/good/graph_5.txt");
  EXPECT_EQ(graphAlg.depthFirstSearch(graph, start), nullptr);
  start = -1;
  EXPECT_EQ(graphAlg.depthFirstSearch(graph, start), nullptr);
}

TEST(depthFirstSearch, invalidVertices) {
  Graph graph;
  GraphAlgorithms graphAlg;

  graph.loadGraphFromFile("graph_files/good/graph_11.txt");
  EXPECT_TRUE(NULL == graphAlg.depthFirstSearch(graph, 0));
  EXPECT_TRUE(NULL == graphAlg.depthFirstSearch(graph, 12));
  EXPECT_TRUE(NULL == graphAlg.depthFirstSearch(graph, 3500));

  EXPECT_TRUE(NULL != graphAlg.depthFirstSearch(graph, 1));
  EXPECT_TRUE(NULL != graphAlg.depthFirstSearch(graph, 11));
  EXPECT_TRUE(NULL != graphAlg.depthFirstSearch(graph, 5));
}

TEST(depthFirstSearch, allInclude) {
  Graph graph;
  GraphAlgorithms graphAlg;
  int *rez;

  graph.loadGraphFromFile("graph_files/good/graph_11.txt");
  rez = graphAlg.depthFirstSearch(graph, 1);
  int countVertices = 0, sizeVertices = graph.getSizeGraph();
  for (int i = 1; i <= sizeVertices; i++) {
    for (int j = 0; j < sizeVertices; j++) {
      if (i == rez[j]) {
        countVertices += 1;
        break;
      }
    }
  }
  EXPECT_TRUE(countVertices == sizeVertices);
}

TEST(depthFirstSearch, notRepeat) {
  Graph graph;
  GraphAlgorithms graphAlg;
  int *rez;

  graph.loadGraphFromFile("graph_files/good/graph_11.txt");
  rez = graphAlg.depthFirstSearch(graph, 1);
  int countVertices = 0, sizeVertices = graph.getSizeGraph();
  for (int i = 1; i <= sizeVertices; i++) {
    for (int j = 0; j < sizeVertices; j++) {
      if (i == rez[j]) countVertices += 1;
    }
    if (countVertices > 1)
      break;
    else
      countVertices = 0;
  }
  EXPECT_TRUE(countVertices == 0);
}

TEST(breadthFirstSearch, RightData) {
  int rez[5]{1, 2, 3, 4, 5};
  Graph graph;
  GraphAlgorithms graphAlg;
  int start = 1;
  int *exp = new int[5];

  graph.loadGraphFromFile("graph_files/good/graph_5.txt");
  exp = graphAlg.breadthFirstSearch(graph, start);
  for (size_t i = 0; i < graph.getSizeGraph(); i++) {
    EXPECT_EQ(rez[i], exp[i]);
  }
}

TEST(breadthFirstSearch, StartVertexOutOfRange) {
  int start = 6;
  Graph graph;
  GraphAlgorithms graphAlg;

  graph.loadGraphFromFile("graph_files/good/graph_5.txt");
  EXPECT_EQ(graphAlg.breadthFirstSearch(graph, start), nullptr);
  start = -1;
  EXPECT_EQ(graphAlg.breadthFirstSearch(graph, start), nullptr);
}

TEST(breadthFirstSearch, invalidVertices) {
  Graph graph;
  GraphAlgorithms graphAlg;

  graph.loadGraphFromFile("graph_files/good/graph_11.txt");
  EXPECT_TRUE(NULL == graphAlg.breadthFirstSearch(graph, 0));
  EXPECT_TRUE(NULL == graphAlg.breadthFirstSearch(graph, 12));
  EXPECT_TRUE(NULL == graphAlg.breadthFirstSearch(graph, 3500));
}

TEST(breadthFirstSearch, allInclude) {
  Graph graph;
  GraphAlgorithms graphAlg;
  int *rez;

  graph.loadGraphFromFile("graph_files/good/graph_11.txt");
  rez = graphAlg.breadthFirstSearch(graph, 1);
  int countVertices = 0, sizeVertices = graph.getSizeGraph();
  for (int i = 1; i <= sizeVertices; i++) {
    for (int j = 0; j < sizeVertices; j++) {
      if (i == rez[j]) {
        countVertices += 1;
        break;
      }
    }
  }
  EXPECT_TRUE(countVertices == sizeVertices);
}

TEST(breadthFirstSearch, notRepeat) {
  Graph graph;
  GraphAlgorithms graphAlg;
  int *rez;

  graph.loadGraphFromFile("graph_files/good/graph_11.txt");
  rez = graphAlg.breadthFirstSearch(graph, 1);
  int countVertices = 0, sizeVertices = graph.getSizeGraph();
  for (int i = 1; i <= sizeVertices; i++) {
    for (int j = 0; j < sizeVertices; j++) {
      if (i == rez[j]) countVertices += 1;
    }
    if (countVertices > 1)
      break;
    else
      countVertices = 0;
  }
  EXPECT_TRUE(countVertices == 0);
}

TEST(getShortestPathBetweenVertices, RightData) {
  int rez = 20;
  Graph graph;
  GraphAlgorithms graphAlg;
  int start = 2;
  int finish = 5;

  graph.loadGraphFromFile("graph_files/good/graph_5.txt");
  int exp = graphAlg.getShortestPathBetweenVertices(graph, start, finish);
  EXPECT_EQ(rez, exp);

  rez = 130;
  graph.loadGraphFromFile("graph_files/good/graph_5_or.txt");
  exp = graphAlg.getShortestPathBetweenVertices(graph, start, finish);
  EXPECT_EQ(rez, exp);
}

TEST(getShortestPathBetweenVertices, EnterVertexesOutOfGraph) {
  int start = -1;
  int finish = 5;
  Graph graph;
  GraphAlgorithms graphAlg;

  graph.loadGraphFromFile("graph_files/good/graph_5.txt");
  EXPECT_EQ(graphAlg.getShortestPathBetweenVertices(graph, start, finish), -1);
  start = 3;
  finish = 6;
  EXPECT_EQ(graphAlg.getShortestPathBetweenVertices(graph, start, finish), -1);
  start = 0;
  finish = 5;
  EXPECT_EQ(graphAlg.getShortestPathBetweenVertices(graph, start, finish), -1);
  start = 3;
  finish = 0;
  EXPECT_EQ(graphAlg.getShortestPathBetweenVertices(graph, start, finish), -1);
  start = 3;
  finish = -1;
  EXPECT_EQ(graphAlg.getShortestPathBetweenVertices(graph, start, finish), -1);
}

TEST(getShortestPathBetweenVertices, invalidVertices) {
  Graph graph;
  GraphAlgorithms graphAlg;

  graph.loadGraphFromFile("graph_files/good/graph_11.txt");
  EXPECT_TRUE(0 > graphAlg.getShortestPathBetweenVertices(graph, 0, 5));
  EXPECT_TRUE(0 > graphAlg.getShortestPathBetweenVertices(graph, 5, 13));
  EXPECT_TRUE(0 > graphAlg.getShortestPathBetweenVertices(graph, 12, 11));
  EXPECT_TRUE(0 > graphAlg.getShortestPathBetweenVertices(graph, 11, 0));

  EXPECT_TRUE(0 < graphAlg.getShortestPathBetweenVertices(graph, 3, 11));
  EXPECT_TRUE(0 < graphAlg.getShortestPathBetweenVertices(graph, 11, 5));
}

TEST(getShortestPathBetweenVertices, minByFloyd_Warshall) {
  Graph graph;
  GraphAlgorithms graphAlg;
  int **rez;

  graph.loadGraphFromFile("graph_files/good/graph_11.txt");
  rez = graphAlg.getShortestPathsBetweenAllVertices(graph);

  EXPECT_TRUE(rez[0][4] ==
              graphAlg.getShortestPathBetweenVertices(graph, 1, 5));
  EXPECT_TRUE(rez[4][9] ==
              graphAlg.getShortestPathBetweenVertices(graph, 5, 10));
  EXPECT_TRUE(rez[1][10] ==
              graphAlg.getShortestPathBetweenVertices(graph, 2, 11));
  EXPECT_TRUE(rez[10][7] ==
              graphAlg.getShortestPathBetweenVertices(graph, 11, 8));
}

TEST(getShortestPathsBetweenAllVertices, minByDeixtra) {
  Graph graph;
  GraphAlgorithms graphAlg;
  int **rez;

  graph.loadGraphFromFile("graph_files/good/graph_11.txt");
  rez = graphAlg.getShortestPathsBetweenAllVertices(graph);

  EXPECT_TRUE(rez[0][4] ==
              graphAlg.getShortestPathBetweenVertices(graph, 1, 5));
  EXPECT_TRUE(rez[4][9] ==
              graphAlg.getShortestPathBetweenVertices(graph, 5, 10));
  EXPECT_TRUE(rez[1][10] ==
              graphAlg.getShortestPathBetweenVertices(graph, 2, 11));
  EXPECT_TRUE(rez[10][7] ==
              graphAlg.getShortestPathBetweenVertices(graph, 11, 8));
}

TEST(getLeastSpanningTree, countEdges) {
  Graph graph;
  GraphAlgorithms graphAlg;
  int **rez;

  graph.loadGraphFromFile("graph_files/good/graph_11.txt");
  rez = graphAlg.getLeastSpanningTree(graph);
  int countEdges = 0, sizeVertices = graph.getSizeGraph();
  for (int i = 0; i < sizeVertices; i++) {
    for (int j = 0; j < sizeVertices; j++) {
      if (rez[i][j] != 0) countEdges += 1;
    }
  }
  EXPECT_TRUE(countEdges == sizeVertices - 1);
}

TEST(getLeastSpanningTree, allVerticesInclude) {
  Graph graph;
  GraphAlgorithms graphAlg;
  int **rez;

  graph.loadGraphFromFile("graph_files/good/graph_11.txt");
  rez = graphAlg.getLeastSpanningTree(graph);
  int countEdges, sizeVertices = graph.getSizeGraph();
  for (int i = 0; i < sizeVertices; i++) {
    countEdges = 0;
    for (int j = 0; j < sizeVertices; j++) {
      if (rez[i][j] != 0 || rez[j][i] != 0) countEdges += 1;
    }
    if (countEdges == 0) break;
  }
  EXPECT_TRUE(countEdges != 0);
}

TEST(getLeastSpanningTree, withoutLoop) {
  Graph graph;
  GraphAlgorithms graphAlg;
  int **rez;

  graph.loadGraphFromFile("graph_files/good/graph_11.txt");
  rez = graphAlg.getLeastSpanningTree(graph);
  int loopFlag = 0, sizeVertices = graph.getSizeGraph();
  for (int i = 0; i < sizeVertices; i++) {
    int k = 0;
    for (int j = 0; j < sizeVertices; j++) {
      if (rez[i][j] != 0 && rez[j][i] != 0) loopFlag = 1;
      if (rez[j][i] != 0) {
        k += 1;
        if (k == 2) loopFlag = 1;
      }
    }
  }
  EXPECT_TRUE(loopFlag == 0);
}

TEST(solveTravelingSalesmanProblem, allVerticesInclude) {
  Graph graph;
  GraphAlgorithms graphAlg;
  TsmResult rez;
  

  graph.loadGraphFromFile("graph_files/good/graph_5.txt");
  rez = graphAlg.solveTravelingSalesmanProblem(graph);
  int countVertices = 0, sizeVertices = rez.vertices.size();
  int graph_size = graph.getSizeGraph();
  for (int i = 1; i <= graph_size; i++) {
    for (int j = 0; j < sizeVertices; j++) {
      if (i == rez.vertices[j]) {
        countVertices += 1;
        break;
      }
    }
  }
  EXPECT_TRUE(countVertices == graph_size);
}

TEST(solveTravelingSalesmanProblem, Circled) {
  Graph graph;
  GraphAlgorithms graphAlg;
  TsmResult rez;

  graph.loadGraphFromFile("graph_files/good/graph_5.txt");
  rez = graphAlg.solveTravelingSalesmanProblem(graph);

  EXPECT_TRUE(*(rez.vertices.begin()) == *(rez.vertices.end() - 1));
}

TEST(solveTravelingSalesmanProblem, outOfSubOptimalRange) {
  Graph graph;
  GraphAlgorithms graphAlg;
  TsmResult rez;

  graph.loadGraphFromFile("graph_files/good/graph_11.txt");
  rez = graphAlg.solveTravelingSalesmanProblem(graph);
  EXPECT_TRUE(rez.distance < 290);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
