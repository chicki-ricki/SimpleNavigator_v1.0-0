# В операционных системах GNU/Linux имена файлов библиотек должны иметь префикс "lib", статические библиотеки - расширение *.a, динамические - *.so.

NAME			=	graph

SRC				=	main.cpp

OBJS			=	${SRC:%.cpp=%.o}



NAME_GRAPH		=	s21_graph.a

SRC_GRAPH		=	s21_graph.cpp

HEADERS_GRAPH	=	s21_graph.h

OBJS_GRAPH	=	${SRC_GRAPH:%.cpp=%.o}



NAME_ALG	=	s21_graph_algorithms.a

SRC_ALG		=	s21_graph_algorithms.cpp

HEADERS_ALG	=	s21_graph_algorithms.h

OBJS_ALG	=	${SRC_ALG:%.cpp=%.o}

FLAGS	=	-g -Wall -Wextra -Werror -std=c++17

CC		=	g++

RM		=	rm -f

.PHONY	:	all clean fclean re test s21_graph.a s21_graph_algorithms.a

${OBJS_GRAPH}:	%.o:	%.cpp ${HEADERS_GRAPH}
	${CC} ${FLAGS} -I. -c $< -o $@

${OBJS_ALG}:	%.o:	%.cpp ${HEADERS_ALG}
	${CC} ${FLAGS} -I. -c $< -o $@

${NAME}:
	${MAKE} ${NAME_ALG}
	${CC} ${FLAGS} ${SRC} ${SRC_GRAPH} ${SRC_ALG} -I. s21_containers/s21_containers.a -o $@
#	${CC} ${FLAGS} ${SRC} -I. -Is21_containers/ s21_graph.a s21_graph_algorithms.a s21_containers/s21_containers.a -o $@

all		:	${NAME} test

${NAME_GRAPH}	:	${OBJS_GRAPH}
			cd ./s21_containers && ${MAKE}
			ar rcs ${NAME_GRAPH} $?

${NAME_ALG}	:	${OBJS_ALG}
			${MAKE} ${NAME_GRAPH}
			ar rcs ${NAME_ALG} $?

clean	:
	${RM} ${OBJS_GRAPH} ${OBJS_ALG} ${OBJS}
	cd ./s21_containers && ${MAKE} clean

fclean	:	clean
	${RM} ${NAME} ${NAME_GRAPH} ${NAME_ALG} test
	cd ./s21_containers && ${MAKE} fclean

re		:	fclean all

test	:
	${CC} s21_graph.cpp s21_graph_algorithms.cpp s21_graph_algorithms_test.cpp s21_containers/s21_containers.a -o test -pthread -std=c++17 -lgtest -lgmock

google-style	:
	@cp ../materials/linters/.clang-format ./
	@clang-format -i *.cpp *.h ./s21_containers/*.cpp ./s21_containers/*.h
	clang-format -n *.cpp *.h ./s21_containers/*.cpp ./s21_containers/*.h

leak	:
	CK_FORK=no leaks -atExit -- ./${NAME}

install_gtest	:
#	brew install web-eid/gtest/gtest
	brew install googletest
