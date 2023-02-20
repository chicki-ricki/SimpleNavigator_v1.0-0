HEADERS_QUEUE	=	s21_queue.h s21_queue.tpp

HEADERS_STACK	=	s21_stack.h s21_stack.tpp

HEADERS			=	${HEADERS_QUEUE} ${HEADERS_STACK} s21_utils.h

all		:	${HEADERS}
	c++ -g -Wall -Werror -Wextra -lstdc++ -std=c++17 -Wno-unused main_test_queue.cc -o queue
	c++ -g -Wall -Werror -Wextra -lstdc++ -std=c++17 -Wno-unused main_test_stack.cc -o stack
