#include <gtest/gtest.h>
#include <graphviz/cgraph.h>
//#include <graphviz/gvc.h>

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

  graph.loadGraphFromFile("graph_4.txt");
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

  graph.loadGraphFromFile("graph_4.txt");
  Graph copyGraph(graph);

  EXPECT_NE(&graph.getGraph(), &copyGraph.getGraph());
}

TEST(GraphConstructor, RightMove) {
  Graph graph;

  graph.loadGraphFromFile("graph_4.txt");
  Graph test = std::move(graph);

  EXPECT_EQ(graph.getSizeGraph(), 0);
  EXPECT_EQ(test.getSizeGraph(), 4);
}

TEST(GraphConstructor, NoReallocMemory) {
  Graph graph;
  graph.matrix_ = new int *[2] {
    new int [2]{0, 1}, new int [2]{1, 0}
  };

  graph.loadGraphFromFile("graph_4.txt");

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

  graph.loadGraphFromFile("graph_4.txt");
  test.loadGraphFromFile("graph_11.txt");
  test = graph;
  EXPECT_EQ(graph.getSizeGraph(), test.getSizeGraph());
  for (size_t i = 0; i < graph.getSizeGraph(); i++) {
    for (size_t j = 0; j < graph.getSizeGraph(); j++) {
      EXPECT_EQ(graph.getGraph()[i][j], test.getGraph()[i][j]);
    }
  }
}

TEST(GraphAssignmentCopy, ReallocMemory) {
  Graph graph;
  Graph test;

  graph.loadGraphFromFile("graph_4.txt");
  test.loadGraphFromFile("graph_11.txt");
  test = graph;
  EXPECT_NE(&graph, &test);
  EXPECT_NE(graph.getGraph().begin(), test.getGraph().begin());
}

TEST(GraphAssignmentCopy, SelfAssingmentNotReallocateMemory) {
  Graph graph;
  graph.loadGraphFromFile("graph_4.txt");

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

  graph.loadGraphFromFile("graph_4.txt");
  test.loadGraphFromFile("graph_11.txt");
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

  graph.loadGraphFromFile("graph_4.txt");
  test.loadGraphFromFile("graph_11.txt");
  std::vector<int> *oldPtrVec = &graph.getGraph()[0];
  test = std::move(graph);
  std::vector<int> *newPtrVec = &test.getGraph()[0];
  EXPECT_EQ(oldPtrVec, newPtrVec);
}

TEST(GraphAssignmentMove, SelfAssingmentNotReallocateMemory) {
  Graph graph;

  graph.loadGraphFromFile("graph_4.txt");
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

  graph->loadGraphFromFile("graph_4.txt");
  EXPECT_EQ(graph->getSizeGraph(), 4);

  Graph *ptr = graph;

  delete graph;
  EXPECT_EQ(ptr->getSizeGraph(), 0);
}

TEST(LoadFromFile, RightLoad) {
  Graph graph;

  graph.loadGraphFromFile("graph_4.txt");
  EXPECT_EQ(graph.getSizeGraph(), 4);
  graph.loadGraphFromFile("graph_5.txt");
  EXPECT_EQ(graph.getSizeGraph(), 5);
}

TEST(LoadFromFile, NoExistFile) {
  Graph graph;

  EXPECT_EQ(graph.loadGraphFromFile("noFile.txt"), 1);
}

TEST(LoadFromFile, EmptyGraph) {
  Graph graph;

  EXPECT_EQ(graph.loadGraphFromFile("graph_0.txt"), 2);
}

TEST(LoadFromFile, ElementaryGraph) {
  Graph graph;

  EXPECT_EQ(graph.loadGraphFromFile("graph_1.txt"), 2);
}

TEST(LoadFromFile, GraphWrongLine) {
  Graph graph;

  EXPECT_EQ(graph.loadGraphFromFile("graph_wrong_line.txt"), 3);
}

TEST(LoadFromFile, GraphWrongColumn) {
  Graph graph;

  EXPECT_EQ(graph.loadGraphFromFile("graph_wrong_column.txt"), 4);
}

TEST(LoadFromFile, WithoutRowsNumber) {
  Graph graph;

  EXPECT_EQ(graph.loadGraphFromFile("graph_without_size.txt"), 2);
}

TEST(LoadFromFile, NonReadableFile) {
  Graph graph;

  std::system("chmod 000 graph_4.txt");
  EXPECT_EQ(graph.loadGraphFromFile("graph_4.txt"), 1);
  std::system("chmod 777 graph_4.txt");
}

TEST(LoadFromFile, NoDigitsInMatrix) {
  Graph graph;

  EXPECT_EQ(graph.loadGraphFromFile("graph_with_symbols.txt"), 4);
}

TEST(ExportGraphToDot, NonWritableFile) {
  Graph graph;
  std::system("chmod 000 exportFile.dot");
  graph.loadGraphFromFile("graph_4.txt");
  EXPECT_EQ(graph.exportGraphToDot("exportFile.dot"), 1);
  std::system("chmod 777 exportFile.dot");
}

TEST(ExportGraphToDot, StandardGraphDot) {
  Graph graph;
  graph.loadGraphFromFile("graph_4.txt");
  graph.exportGraphToDot("graph_4.dot");
  Agraph_t *g;
  FILE *fp;
  fp = fopen("graph_4.dot", "r");
  g = agread(fp, 0);
  int agraph_size = agnnodes(g);
  agclose(g);
  fclose(fp);
  EXPECT_EQ(graph.getSizeGraph(), agraph_size);
}

TEST(ExportGraphToDot, StandardGraphGv) {
  Graph graph;
  graph.loadGraphFromFile("graph_4.txt");
  graph.exportGraphToDot("graph_4.gv");
  Agraph_t *g;
  FILE *fp;
  fp = fopen("graph_4.gv", "r");
  g = agread(fp, 0);
  int agraph_size = agnnodes(g);
  agclose(g);
  fclose(fp);
  EXPECT_EQ(graph.getSizeGraph(), agraph_size);
}

TEST(ExportGraphToDot, ExistingFile) {
	Graph graph;
  graph.loadGraphFromFile("graph_4.txt");
  graph.exportGraphToDot("exportFile.dot");
  Agraph_t *g;
  FILE *fp;
  fp = fopen("exportFile.dot", "r");
  g = agread(fp, 0);
  int agraph_size = agnnodes(g);
  agclose(g);
  fclose(fp);
  EXPECT_EQ(graph.getSizeGraph(), agraph_size);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
	int t = RUN_ALL_TESTS();
  return (t);
}