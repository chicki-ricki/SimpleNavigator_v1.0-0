#ifndef CONSOLE_APPLICATION
#define CONSOLE_APPLICATION

#include <iostream>
#include <string>

#include "s21_graph_algorithms.h"

class ConsoleApplication {

private:
	ConsoleApplication &operator=(const ConsoleApplication &) = delete;
  ConsoleApplication(const ConsoleApplication &) = delete;;
  ConsoleApplication &operator=(ConsoleApplication &&) = delete;;
  ConsoleApplication(ConsoleApplication &&) = delete;;
  ~ConsoleApplication() = delete;
	
public:
	static void start();
};


#endif