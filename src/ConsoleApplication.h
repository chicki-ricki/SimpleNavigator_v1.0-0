#ifndef CONSOLE_APPLICATION
#define CONSOLE_APPLICATION

#include <iostream>
#include <string>

#include "s21_graph_algorithms.h"

#define D_BLUE "\033[1;34m"
#define GREY "\033[1;37m"
#define NONE "\033[0m"

class ConsoleApplication {
 private:
  ConsoleApplication &operator=(const ConsoleApplication &) = delete;
  ConsoleApplication(const ConsoleApplication &) = delete;
  ConsoleApplication &operator=(ConsoleApplication &&) = delete;
  ConsoleApplication(ConsoleApplication &&) = delete;
  ~ConsoleApplication() = delete;

  static bool isNotChosen_;
  static std::string fileName_;
  static Graph *graph_;
  static GraphAlgorithms *graphAlg_;

  static void freeArr(int **, size_t);
  static void printResult(int *, size_t);
  static void printResult2D(int **, unsigned int);

 public:
  ConsoleApplication(std::string fileName);

  static void start();
  static void helloMenu();
  static void mainMenu();
  static void load();
  static void list();
  static void exit();
  static void save();

  static int checkAndRunStartChoice(std::string &);
  static int checkAndRunChoice(std::string &);

  static void makeDepthFirstSearch(Graph, GraphAlgorithms);
  static void makeBreadthFirstSearch(Graph, GraphAlgorithms);
  static void makeDeyxtraAlg(Graph, GraphAlgorithms);
  static void makeFloydWorshelAlg(Graph, GraphAlgorithms);
  static void makeAlgOfPrim(Graph, GraphAlgorithms);
  static void makeVoyage(Graph, GraphAlgorithms);
};

#endif