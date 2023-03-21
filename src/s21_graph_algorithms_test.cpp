#include "googletest/include/gtest/gtest.h"

#include "s21_graph_algorithms.h"

TEST(depthFirstSearch_test, depthFirstSearch_data) {
  int rez[11] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
  Graph graph;
  GraphAlgorithms graphAlg;
  int start = 1;
  int *exp;

  graph.loadGraphFromFile("/Users/eugenia/IT_projects/06_sber21/A2_SimpleNavigator_v1.0-2/src/graph_11.txt");
  exp = graphAlg.depthFirstSearch(graph, start);
  EXPECT_EQ(rez[10], exp[10]);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
