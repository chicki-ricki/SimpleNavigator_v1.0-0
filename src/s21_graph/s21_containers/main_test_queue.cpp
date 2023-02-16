#include "s21_queue.h"
#include <iostream>

 #include <queue>

int	main()
{
	s21::Queue<int>	s;

	s.init();
	//sega:
	// std::cout << "s.peek() after init: " << s.peek() << std::endl;
	s.push(42);
	std::cout << "s.peek() 42: " << s.peek() << std::endl;
	s.push(21);
	std::cout << "s.peek() 42: " << s.peek() << std::endl;
	s.push(12);
	std::cout << "s.peek() 42: " << s.peek() << std::endl;
	s.pop();
	std::cout << "s.peek() after pop (21): " << s.peek() << std::endl;
	s.pop();
	std::cout << "s.peek() after pop (12): " << s.peek() << std::endl;
	
	//sega:
	s.pop();
	std::cout << "s.peek() after pop (0): " << s.peek() << std::endl;
	s.pop();
	std::cout << "s.peek() after pop (0): " << s.peek() << std::endl;


	// std::queue<int>	st;

	// std::cout << "st.size(): " << st.size() << std::endl;
	// st.push(55);
	// std::cout << "st.front(): " << st.front() << std::endl;
	// st.pop();
	// //sega:
	// //std::cout << "st.front(): " << st.front() << std::endl;
}