#include "ConsoleApplication.h"

#define HELLO_MESSAGE                                  \
  "===============================================\n"  \
  "Welcome to Graph Algorithm Library Application! \n" \
  "==============================================="

#define HELLO_MENU_MESSAGE \
  "\n\
Please, choose one of the available commands:\n\
  1. Show the list of available files with adjacency matrices\n\
  2. Load adjacency matrix of graph from file \n\
  3. Exit program \n\n\
Please, choose one and enter command number:  "

#define MAIN_MENU_MESSAGE \
  "\n\
Now you can do the following:\n\
  1. View the list of available files with adjacency matrices\n\
  2. Load adjacency matrix of graph from file \n\
  3. Execute depth-first search algorithm \n\
  4. Execute breadth-first search algorithm \n\
  5. Get shortest path between vertices (Dijkstra's algorithm) \n\
  6. Get shortest path between all vertices (Floyd-Warshall algorithm) \n\
  7. Get least spanning tree (Prim's algorithm) \n\
  8. Solve traveling salesman problem using ant colony algorithm \n\
  9. Save to .dot.\n\
  10. Exit program \n\n\
Please, choose one and enter command number:  "

#define input()                                                                \
  {                                                                            \
    std::cout << D_BLUE                                                        \
              << "Your request does not satisfy the list. Try another one: "   \
              << NONE;                                                         \
    std::cin >> choice;                                                        \
  };
#define CURRENT_GRAPH "\n You're working on graph from the file "

bool ConsoleApplication::isNotChosen_ = true;

void ConsoleApplication::start() {
  system("clear");
  std::cout << D_BLUE << HELLO_MESSAGE << NONE << std::endl;
  while (isNotChosen_ == true) {
    helloMenu();
  }
  while (1) {
    mainMenu();
  }
}

void ConsoleApplication::helloMenu() {
  std::cout << D_BLUE << HELLO_MENU_MESSAGE << NONE;
  std::string choice;
  std::cin >> choice;
  while (checkAndRunStartChoice(choice)) {
		input();
  }
}

void ConsoleApplication::mainMenu() {
  std::cout << D_BLUE << CURRENT_GRAPH << ConsoleApplication::fileName_ << NONE << std::endl;
	std::cout << D_BLUE << MAIN_MENU_MESSAGE << NONE;
  std::string choice;
  std::cin >> choice;
  while (checkAndRunChoice(choice))
    input();
}

int ConsoleApplication::checkAndRunStartChoice(std::string &choice) {
	if (choice.compare("1") == 0) {
		ConsoleApplication::list();
		return (0);
	}
	if (choice.compare("2") == 0) {
		ConsoleApplication::load();
		return (0);
	}
	if (choice.compare("3") == 0) {
		ConsoleApplication::exit();
		return (0);
	}
	return (1);
}

int ConsoleApplication::checkAndRunChoice(std::string &choice) {
	if (choice.compare("1") == 0) {
		ConsoleApplication::list();
		return (0);
	}
	if (choice.compare("2") == 0) {
		ConsoleApplication::load();
		return (0);
	}
	if (choice.compare("3") == 0) {
		ConsoleApplication::makeDepthFirstSearch(*graph_, *graphAlg_);
		return (0);
	}
	if (choice.compare("4") == 0) {
		ConsoleApplication::makeBreadthFirstSearch(*graph_, *graphAlg_);
		return (0);
	}
	if (choice.compare("5") == 0) {
		ConsoleApplication::makeDeyxtraAlg(*graph_, *graphAlg_);
		return (0);
	}
	if (choice.compare("6") == 0) {
		ConsoleApplication::makeFloydWorshelAlg(*graph_, *graphAlg_);
		return (0);
	}
	if (choice.compare("7") == 0) {
		ConsoleApplication::makeAlgOfPrim(*graph_, *graphAlg_);
		return (0);
	}
	if (choice.compare("8") == 0) {
		ConsoleApplication::makeVoyage(*graph_, *graphAlg_);
		return (0);
	}
	if (choice.compare("9") == 0) {
		if (graph_->exportGraphToDot("graph_files/exportFile.dot") != 0) {
      s21::exitError("Error: cannot write graph to file");
    }
		return (0);
	}
	if (choice.compare("10") == 0) {
		ConsoleApplication::exit();
		return (0);
	}
	return (1);
}