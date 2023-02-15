#include "s21_stack.h"
#include <iostream>

int	main()
{
	s21::Stack<int>	s;

	s.init();
	std::cout << "s.peek() after init: " << s.peek() << std::endl;
	s.push(42);
	std::cout << "s.peek() 42: " << s.peek() << std::endl;
	s.push(21);
	std::cout << "s.peek() 21: " << s.peek() << std::endl;
	s.push(12);
	std::cout << "s.peek() 12: " << s.peek() << std::endl;
	s.pop();
	std::cout << "s.peek() after pop (21): " << s.peek() << std::endl;

}