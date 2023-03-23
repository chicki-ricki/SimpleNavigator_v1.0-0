#include <gtest/gtest.h>

#include "s21_graph.h"

TEST(GraphConstructor, DefaultSize) {
  Graph graph;
  EXPECT_EQ(graph.getSizeGraph(), 0);
}

TEST(GraphConstructor, DefaultGraph) {
  Graph graph;
  EXPECT_EQ(graph.getGraph().size(), 0);
}

TEST(GraphConstructor, RightCopy) {
  Graph graph;

  graph.loadGraphFromFile("/Users/eugenia/IT_projects/06_sber21/A2_SimpleNavigator_v1.0-2/src/graph_4.txt");
  EXPECT_EQ(graph.getSizeGraph(), 4);
  Graph copyGraph(graph);

  for (size_t i = 0; i < graph.getSizeGraph(); i++) {
    for (size_t j = 0; j < graph.getSizeGraph(); j++) {
      EXPECT_EQ(graph.getGraph()[i][j], copyGraph.getGraph()[i][j]);
    }
  }
}

TEST(GraphConstructor, ReallocMemory) {
  Graph graph;

  graph.loadGraphFromFile("/Users/eugenia/IT_projects/06_sber21/A2_SimpleNavigator_v1.0-2/src/graph_4.txt");
  Graph copyGraph(graph);

  EXPECT_NE(&graph.getGraph(), &copyGraph.getGraph());
}

TEST(GraphConstructor, RightMove) {
  Graph graph;

  graph.loadGraphFromFile("/Users/eugenia/IT_projects/06_sber21/A2_SimpleNavigator_v1.0-2/src/graph_4.txt");
  Graph test = std::move(graph);

  EXPECT_EQ(graph.getSizeGraph(), 0);
  EXPECT_EQ(test.getSizeGraph(), 4);
}

TEST(GraphConstructor, NoReallocMemory) {
  Graph graph;
  graph.matrix_ = new int *[2] {
    new int [2]{0, 1}, new int [2]{1, 0}
  };

  graph.loadGraphFromFile("/Users/eugenia/IT_projects/06_sber21/A2_SimpleNavigator_v1.0-2/src/graph_4.txt");

  int *old_ptr = graph.matrix_[0];
  std::vector<int> *old_ptr_vec = &graph.getGraph()[0];

  Graph test(std::move(graph));
  int *new_ptr = test.matrix_[0];
  std::vector<int> *new_ptr_vec = &test.getGraph()[0];
  EXPECT_EQ(old_ptr, new_ptr);
  EXPECT_EQ(old_ptr_vec, new_ptr_vec);
  for (int i = 0; i < 2; i++) {
    delete[] test.matrix_[i];
  }
  delete[] test.matrix_;
}

TEST(GraphAssignmentCopy, RightCopy) {
  Graph graph;
  Graph test;

  graph.loadGraphFromFile("/Users/eugenia/IT_projects/06_sber21/A2_SimpleNavigator_v1.0-2/src/graph_4.txt");
  test.loadGraphFromFile("/Users/eugenia/IT_projects/06_sber21/A2_SimpleNavigator_v1.0-2/src/graph_11.txt");
  test = graph;
  EXPECT_EQ(graph.getSizeGraph(), test.getSizeGraph());
  for (int i = 0; i < graph.getSizeGraph(); i++) {
    for (int j = 0; j < graph.getSizeGraph(); j++) {
      EXPECT_EQ(graph.getGraph()[i][j], test.getGraph()[i][j]);
    }
  }
}

TEST(GraphAssignmentCopy, ReallocMemory) {
  Graph graph;
  Graph test;

  graph.loadGraphFromFile("/Users/eugenia/IT_projects/06_sber21/A2_SimpleNavigator_v1.0-2/src/graph_4.txt");
  test.loadGraphFromFile("/Users/eugenia/IT_projects/06_sber21/A2_SimpleNavigator_v1.0-2/src/graph_11.txt");
  test = graph;
  EXPECT_NE(&graph, &test);
  EXPECT_NE(graph.getGraph().begin(), test.getGraph().begin());
}

TEST(GraphAssignmentCopy, SelfAssingmentNotReallocateMemory) {
  Graph graph;
  graph.loadGraphFromFile("/Users/eugenia/IT_projects/06_sber21/A2_SimpleNavigator_v1.0-2/src/graph_4.txt");

  Graph *oldPtr = &graph;
  std::vector<int> *oldPtrVec = &graph.getGraph()[0];
  graph = graph;
  Graph *newPtr = &graph;
  std::vector<int> *newPtrVec = &graph.getGraph()[0];
  EXPECT_EQ(oldPtr, newPtr);
  EXPECT_EQ(oldPtrVec, newPtrVec);
}

TEST(GraphAssignmentMove, RightMove) {
  Graph graph;
  Graph test;

  graph.loadGraphFromFile("/Users/eugenia/IT_projects/06_sber21/A2_SimpleNavigator_v1.0-2/src/graph_4.txt");
  test.loadGraphFromFile("/Users/eugenia/IT_projects/06_sber21/A2_SimpleNavigator_v1.0-2/src/graph_11.txt");
  std::vector<std::vector<int> > check = graph.getGraph();
  test = std::move(graph);
  EXPECT_EQ(test.getSizeGraph(), 4);
  EXPECT_EQ(graph.getSizeGraph(), 0);
  for (int i = 0; i < test.getSizeGraph(); i++) {
    for (int j = 0; j < test.getSizeGraph(); j++) {
      EXPECT_EQ(test.getGraph()[i][j], check[i][j]);
    }
  }
}

TEST(GraphAssignmentMove, NoReallocMemory) {
  Graph graph;
  Graph test;

  graph.loadGraphFromFile("/Users/eugenia/IT_projects/06_sber21/A2_SimpleNavigator_v1.0-2/src/graph_4.txt");
  test.loadGraphFromFile("/Users/eugenia/IT_projects/06_sber21/A2_SimpleNavigator_v1.0-2/src/graph_11.txt");
  std::vector<int> *oldPtrVec = &graph.getGraph()[0];
  test = std::move(graph);
  std::vector<int> *newPtrVec = &test.getGraph()[0];
  EXPECT_EQ(oldPtrVec, newPtrVec);
}

TEST(GraphAssignmentMove, SelfAssingmentNotReallocateMemory) {
  Graph graph;

  graph.loadGraphFromFile("/Users/eugenia/IT_projects/06_sber21/A2_SimpleNavigator_v1.0-2/src/graph_4.txt");
  Graph *oldPtr = &graph;
  std::vector<int> *oldPtrVec = &graph.getGraph()[0];
  graph = std::move(graph);
  Graph *newPtr = &graph;
  std::vector<int> *newPtrVec = &graph.getGraph()[0];
  EXPECT_EQ(oldPtr, newPtr);
  EXPECT_EQ(oldPtrVec, newPtrVec);
}

TEST(GraphDestructor, RightDelete) {
  Graph *graph = new Graph();

  graph->loadGraphFromFile("/Users/eugenia/IT_projects/06_sber21/A2_SimpleNavigator_v1.0-2/src/graph_4.txt");
  EXPECT_EQ(graph->getSizeGraph(), 4);

  Graph *ptr = graph;

  delete graph;
  EXPECT_EQ(ptr->getSizeGraph(), 0);
}

TEST(LoadFromFile, RightLoad) {
  Graph graph;

  graph.loadGraphFromFile("/Users/eugenia/IT_projects/06_sber21/A2_SimpleNavigator_v1.0-2/src/graph_4.txt");
  EXPECT_EQ(graph.getSizeGraph(), 4);
  graph.loadGraphFromFile("/Users/eugenia/IT_projects/06_sber21/A2_SimpleNavigator_v1.0-2/src/graph_5.txt");
  EXPECT_EQ(graph.getSizeGraph(), 5);
}

TEST(LoadFromFile, NoExistFile) {
  Graph graph;

  EXPECT_EQ(graph.loadGraphFromFile("noFile.txt"), 1);
}

TEST(LoadFromFile, EmptyGraph) {
  Graph graph;

  EXPECT_EQ(graph.loadGraphFromFile("/Users/eugenia/IT_projects/06_sber21/A2_SimpleNavigator_v1.0-2/src/graph_0.txt"), 2);
}

TEST(LoadFromFile, ElementaryGraph) {
  Graph graph;

  EXPECT_EQ(graph.loadGraphFromFile("/Users/eugenia/IT_projects/06_sber21/A2_SimpleNavigator_v1.0-2/src/graph_1.txt"), 2);
}



int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return (RUN_ALL_TESTS());
}