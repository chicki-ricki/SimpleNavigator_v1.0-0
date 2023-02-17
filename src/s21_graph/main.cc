#include "s21_graph.h"

int main(int ac, char **av) {
  if (ac == 2) {
    Graph graph;
	if (graph.loadGraphFromFile(std::string(av[1])) != 0)
	  s21::exitError("Error: cannot read file with graph");
	//graphAlgorithms
	if (graph.exportGraphToDot(fileExport) != 0)
	  s21::exitError("Error: cannot write graph to *.dot file");
  }
  else
    s21::exitError("Error: invalid count of arguments");
  return (0);
}