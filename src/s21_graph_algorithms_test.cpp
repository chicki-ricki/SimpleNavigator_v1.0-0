#include "s21_graph_algorithms.h"

#include <gtest/gtest.h>

TEST(depthFirstSearch_test, depthFirstSearch_data) {
  int rez[5]{1, 2, 4, 3, 5};
  Graph graph;
  GraphAlgorithms graphAlg;
  int start = 1;
  int *exp = new int[5];

  graph.loadGraphFromFile("graph_5.txt");
  exp = graphAlg.depthFirstSearch(graph, start);
  EXPECT_EQ(rez[2], exp[2]);
}

TEST(breadthFirstSearch_test, breadthFirstSearch_data) {
  int rez[5]{1, 2, 3, 4, 5};
  Graph graph;
  GraphAlgorithms graphAlg;
  int start = 1;
  int *exp = new int[5];

  graph.loadGraphFromFile("graph_5.txt");
  exp = graphAlg.breadthFirstSearch(graph, start);
  EXPECT_EQ(rez[3], exp[3]);
}

TEST(getShortestPathBetweenVertices_test,
     getShortestPathBetweenVertices_data1) {
  int rez = 20;
  Graph graph;
  GraphAlgorithms graphAlg;
  int start = 2;
  int finish = 5;

  graph.loadGraphFromFile("graph_5.txt");
  int exp = graphAlg.getShortestPathBetweenVertices(graph, start, finish);
  EXPECT_EQ(rez, exp);
}

TEST(getShortestPathBetweenVertices_test,
     getShortestPathBetweenVertices_data2) {
  int rez = 130;
  Graph graph;
  GraphAlgorithms graphAlg;
  int start = 2;
  int finish = 5;

  graph.loadGraphFromFile("graph_5_or.txt");
  int exp = graphAlg.getShortestPathBetweenVertices(graph, start, finish);
  EXPECT_EQ(rez, exp);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
