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
  for (int i = 0; i < graph.getSizeGraph(); i++) {
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

TEST(breadthFirstSearch, RightData) {
  int rez[5]{1, 2, 3, 4, 5};
  Graph graph;
  GraphAlgorithms graphAlg;
  int start = 1;
  int *exp = new int[5];

  graph.loadGraphFromFile("graph_files/good/graph_5.txt");
  exp = graphAlg.breadthFirstSearch(graph, start);
  for (int i = 0; i < graph.getSizeGraph(); i++) {
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
  EXPECT_EQ(graphAlg.getShortestPathBetweenVertices(graph, start, finish), 1);
  start = 3;
  finish = 6;
  EXPECT_EQ(graphAlg.getShortestPathBetweenVertices(graph, start, finish), 1);
  start = 0;
  finish = 5;
  EXPECT_EQ(graphAlg.getShortestPathBetweenVertices(graph, start, finish), 1);
  start = 3;
  finish = 0;
  EXPECT_EQ(graphAlg.getShortestPathBetweenVertices(graph, start, finish), 1);
  start = 3;
  finish = -1;
  EXPECT_EQ(graphAlg.getShortestPathBetweenVertices(graph, start, finish), 1);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
