# В операционных системах GNU/Linux имена файлов библиотек должны иметь префикс "lib", статические библиотеки - расширение *.a, динамические - *.so.

NAME			=	graph

SRC				=	main.cpp ConsoleApplicationMenu.cpp ConsoleApplication.cpp

HEADER		= ConsoleApplication.h

OBJS			=	${SRC:%.cpp=%.o}


LIB_CONT		=	s21_containers.a

LIB_GRAPH		=	s21_graph.a

SRC_GRAPH		=	s21_graph.cpp

HEADERS_GRAPH	=	s21_graph.h

OBJS_GRAPH		=	${SRC_GRAPH:%.cpp=%.o}


LIB_GRAPH_ALG	=	s21_graph_algorithms.a

SRC_ALG			=	s21_graph_algorithms.cpp

HEADERS_ALG		=	s21_graph_algorithms.h

OBJS_ALG		=	${SRC_ALG:%.cpp=%.o}


# NAME_TEST		=	test

SRC_TEST		=	s21_graph_algorithms_test.cpp s21_graph_test.cpp 

OBJS_TEST		=	${SRC_TEST:%.cpp=%.o}


FLAGS			=	-g -Wall -Wextra -Werror -std=c++17

CC				=	g++

RM				=	rm -f

%.o			:	%.cpp
			@${CC} ${FLAGS} -I. -c $< -o $@

.PHONY		:	all clean fclean re test s21_graph.a s21_graph_algorithms.a cont

all			:	${LIB_CONT} ${LIB_GRAPH} ${LIB_GRAPH_ALG} ${NAME} test

${NAME}		:	${OBJS} ${HEADER}
			${CC} ${FLAGS} ${SRC} -I. *.a -o $@

${LIB_GRAPH}:	${OBJS_GRAPH}
			@ar rcs ${LIB_GRAPH} $?
			@ranlib ${LIB_GRAPH}

${LIB_GRAPH_ALG}	:	${OBJS_ALG}
			@ar rcs ${LIB_GRAPH_ALG} $?
			@ranlib ${LIB_GRAPH_ALG}

${LIB_CONT}: 
			@cd ./s21_containers && ${MAKE}
			@cp ./s21_containers/s21_containers.a ./s21_containers.a

clean		:
			${RM} ${OBJS_GRAPH} ${OBJS_ALG} ${OBJS} ${OBJS_TEST} *.dot *.gv
			cd ./s21_containers && ${MAKE} clean 

fclean		:	clean
			${RM} ${NAME} ${LIB_GRAPH} ${LIB_GRAPH_ALG} test_algorithms test_graph ${LIB_CONT}
			cd ./s21_containers && ${MAKE} fclean

re			:	fclean all 

test		: 	#${OBJS_TEST}
#			${CC} s21_graph_algorithms_test.cpp -L. -I. ${LIB_GRAPH} ${LIB_GRAPH_ALG} ${LIB_CONT} -o test_algorithms -pthread -std=c++17 -lgtest -lgmock
			${CC} s21_graph_test.cpp -L. -I. ${LIB_GRAPH} ${LIB_CONT} -o test_graph -pthread -std=c++17 -lgtest -lgmock -g -lcgraph -lgvc

google-style:
			@cp ../materials/linters/.clang-format ./
			@clang-format -i *.cpp *.h ./s21_containers/*.cpp ./s21_containers/*.h
			clang-format -n *.cpp *.h ./s21_containers/*.cpp ./s21_containers/*.h

leaks		:
			CK_FORK=no leaks -atExit -- ./${NAME}
			CK_FORK=no leaks -atExit -- ./test_graph

install_gtest:
#			brew install web-eid/gtest/gtest
			brew install googletest

install_graphviz:
			brew install graphviz