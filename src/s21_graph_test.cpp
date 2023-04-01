#include "s21_graph.h"

#include <graphviz/cgraph.h>
#include <gtest/gtest.h>

#include "s21_graph_algorithms.h"

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

  graph.loadGraphFromFile("graph_files/good/graph_4.txt");
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

  graph.loadGraphFromFile("graph_files/good/graph_4.txt");
  Graph copyGraph(graph);

  EXPECT_NE(&graph.getGraph(), &copyGraph.getGraph());
}

TEST(GraphConstructor, RightMove) {
  Graph graph;

  graph.loadGraphFromFile("graph_files/good/graph_4.txt");
  Graph test = std::move(graph);

  EXPECT_EQ(graph.getSizeGraph(), 0);
  EXPECT_EQ(test.getSizeGraph(), 4);
}

TEST(GraphConstructor, NoReallocMemory) {
  Graph graph;
  graph.matrix_ = new int *[2] {
    new int[2]{0, 1}, new int[2] { 1, 0 }
  };

  graph.loadGraphFromFile("graph_files/good/graph_4.txt");

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

  graph.loadGraphFromFile("graph_files/good/graph_4.txt");
  test.loadGraphFromFile("graph_files/good/graph_11.txt");
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

  graph.loadGraphFromFile("graph_files/good/graph_4.txt");
  test.loadGraphFromFile("graph_files/good/graph_11.txt");
  test = graph;
  EXPECT_NE(&graph, &test);
  EXPECT_NE(graph.getGraph().begin(), test.getGraph().begin());
}

TEST(GraphAssignmentCopy, SelfAssingmentNotReallocateMemory) {
  Graph graph;
  graph.loadGraphFromFile("graph_files/good/graph_4.txt");

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

  graph.loadGraphFromFile("graph_files/good/graph_4.txt");
  test.loadGraphFromFile("graph_files/good/graph_11.txt");
  std::vector<std::vector<int> > check = graph.getGraph();
  test = std::move(graph);
  EXPECT_EQ(test.getSizeGraph(), 4);
  EXPECT_EQ(graph.getSizeGraph(), 0);
  for (size_t i = 0; i < test.getSizeGraph(); i++) {
    for (size_t j = 0; j < test.getSizeGraph(); j++) {
      EXPECT_EQ(test.getGraph()[i][j], check[i][j]);
    }
  }
}

TEST(GraphAssignmentMove, NoReallocMemory) {
  Graph graph;
  Graph test;

  graph.loadGraphFromFile("graph_files/good/graph_4.txt");
  test.loadGraphFromFile("graph_files/good/graph_11.txt");
  std::vector<int> *oldPtrVec = &graph.getGraph()[0];
  test = std::move(graph);
  std::vector<int> *newPtrVec = &test.getGraph()[0];
  EXPECT_EQ(oldPtrVec, newPtrVec);
}

TEST(GraphAssignmentMove, SelfAssingmentNotReallocateMemory) {
  Graph graph;

  graph.loadGraphFromFile("graph_files/good/graph_4.txt");
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

  graph->loadGraphFromFile("graph_files/good/graph_4.txt");
  EXPECT_EQ(graph->getSizeGraph(), 4);

  Graph *ptr = graph;

  delete graph;
  EXPECT_EQ(ptr->getSizeGraph(), 0);
}

TEST(LoadFromFile, RightLoad) {
  Graph graph;

  graph.loadGraphFromFile("graph_files/good/graph_4.txt");
  EXPECT_EQ(graph.getSizeGraph(), 4);
  graph.loadGraphFromFile("graph_files/good/graph_5.txt");
  EXPECT_EQ(graph.getSizeGraph(), 5);
}

TEST(LoadFromFile, NoExistFile) {
  Graph graph;

  EXPECT_EQ(graph.loadGraphFromFile("noFile.txt"), 1);
}

TEST(LoadFromFile, EmptyGraph) {
  Graph graph;

  EXPECT_EQ(graph.loadGraphFromFile("graph_files/bad/graph_0.txt"), 2);
}

TEST(LoadFromFile, ElementaryGraph) {
  Graph graph;

  EXPECT_EQ(graph.loadGraphFromFile("graph_files/bad/graph_1.txt"), 2);
}

TEST(LoadFromFile, GraphWrongLine) {
  Graph graph;

  EXPECT_EQ(graph.loadGraphFromFile("graph_files/bad/graph_wrong_line.txt"), 3);
}

TEST(LoadFromFile, GraphWrongColumn) {
  Graph graph;

  EXPECT_EQ(graph.loadGraphFromFile("graph_files/bad/graph_wrong_column.txt"),
            4);
}

TEST(LoadFromFile, WithoutRowsNumber) {
  Graph graph;

  EXPECT_EQ(graph.loadGraphFromFile("graph_files/bad/graph_without_size.txt"),
            2);
}

TEST(LoadFromFile, NonReadableFile) {
  Graph graph;

  std::system("chmod 000 graph_files/good/graph_4.txt");
  EXPECT_EQ(graph.loadGraphFromFile("graph_files/good/graph_4.txt"), 1);
  std::system("chmod 777 graph_files/good/graph_4.txt");
}

TEST(LoadFromFile, OnlyRowNumber) {
  Graph graph;

  EXPECT_EQ(graph.loadGraphFromFile("graph_files/bad/graph_without_matrix.txt"),
            3);
}

TEST(LoadFromFile, EmptyFile) {
  Graph graph;

  EXPECT_EQ(graph.loadGraphFromFile("graph_files/bad/graph_empty_file.txt"), 2);
}

TEST(ExportGraphToDot, RightExtention) {
  Graph graph;

  EXPECT_EQ(graph.exportGraphToDot("graph_files/check.dot"), 0);
  EXPECT_EQ(graph.exportGraphToDot("graph_files/check.gv"), 0);
}

TEST(ExportGraphToDot, WrongExtention) {
  Graph graph;

  EXPECT_EQ(graph.exportGraphToDot("check.tor"), 3);
  EXPECT_EQ(graph.exportGraphToDot("check.avtor"), 3);
  EXPECT_EQ(graph.exportGraphToDot("check.dotavtor"), 3);
  EXPECT_EQ(graph.exportGraphToDot("check.gw"), 3);
  EXPECT_EQ(graph.exportGraphToDot("check.gvbob"), 3);
}

TEST(ExportGraphToDot, WithoutExtention) {
  Graph graph;

  EXPECT_EQ(graph.exportGraphToDot("graph_files/check"), 2);
}

TEST(LoadFromFile, NoDigitsInMatrix) {
  Graph graph;

  EXPECT_EQ(graph.loadGraphFromFile("graph_files/bad/graph_with_symbols.txt"),
            4);
}

TEST(ExportGraphToDot, NonWritableFile) {
  Graph graph;
  std::system("chmod 000 graph_files/exportFile.dot");
  graph.loadGraphFromFile("graph_files/good/graph_4.txt");
  EXPECT_EQ(graph.exportGraphToDot("graph_files/exportFile.dot"), 1);
  std::system("chmod 777 graph_files/exportFile.dot");
}

TEST(ExportGraphToDot, StandardGraphDot) {
  Graph graph;
  graph.loadGraphFromFile("graph_files/good/graph_4.txt");
  graph.exportGraphToDot("graph_files/graph_4.dot");
  Agraph_t *g;
  FILE *fp;
  fp = fopen("graph_files/graph_4.dot", "r");
  g = agread(fp, 0);
  int agraph_size = agnnodes(g);
  agclose(g);
  fclose(fp);
  EXPECT_EQ(graph.getSizeGraph(), agraph_size);
}

TEST(ExportGraphToDot, StandardGraphGv) {
  Graph graph;
  graph.loadGraphFromFile("graph_files/good/graph_4.txt");
  graph.exportGraphToDot("graph_files/graph_4.gv");
  Agraph_t *g;
  FILE *fp;
  fp = fopen("graph_files/graph_4.gv", "r");
  g = agread(fp, 0);
  int agraph_size = agnnodes(g);
  agclose(g);
  fclose(fp);
  EXPECT_EQ(graph.getSizeGraph(), agraph_size);
}

TEST(ExportGraphToDot, ExistingFile) {
  Graph graph;
  graph.loadGraphFromFile("graph_files/good/graph_4.txt");
  graph.exportGraphToDot("graph_files/exportFile.dot");
  Agraph_t *g;
  FILE *fp;
  fp = fopen("graph_files/exportFile.dot", "r");
  g = agread(fp, 0);
  int agraph_size = agnnodes(g);
  agclose(g);
  fclose(fp);
  EXPECT_EQ(graph.getSizeGraph(), agraph_size);
}
/*
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
  for (int i = 1; i <= graph.getSizeGraph(); i++) {
    for (int j = 0; j < sizeVertices; j++) {
      if (i == rez.vertices[j]) {
        countVertices += 1;
        break;
      }
    }
  }
  EXPECT_TRUE(countVertices == graph.getSizeGraph());
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
*/
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  int t = RUN_ALL_TESTS();
  return (t);
}