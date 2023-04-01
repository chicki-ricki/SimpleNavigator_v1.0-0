# В операционных системах GNU/Linux имена файлов библиотек должны иметь префикс "lib", статические библиотеки - расширение *.a, динамические - *.so.

# main program files
NAME			=	graph
SRC				=	main.cpp ConsoleApplicationMenu.cpp ConsoleApplication.cpp
HEADER			=	ConsoleApplication.h
OBJS			=	${SRC:%.cpp=%.o}

# graph library files
LIB_CONT		=	s21_containers.a
LIB_GRAPH		=	s21_graph.a
SRC_GRAPH		=	s21_graph.cpp
HEADERS_GRAPH	=	s21_graph.h
OBJS_GRAPH		=	${SRC_GRAPH:%.cpp=%.o}

# graph_algorithms library files
LIB_GRAPH_ALG	=	s21_graph_algorithms.a
SRC_ALG			=	s21_graph_algorithms.cpp
HEADERS_ALG		=	s21_graph_algorithms.h
OBJS_ALG		=	${SRC_ALG:%.cpp=%.o}

# tests files
NAME_TEST		=	test
SRC_TEST		=	s21_graph_algorithms_test.cpp s21_graph_test.cpp 
OBJS_TEST		=	${SRC_TEST:%.cpp=%.o}

# standart flags &other
FLAGS			=	-g -Wall -Wextra -Werror -std=c++17
CC				=	g++
RM				=	rm -f

%.o			:	%.cpp
			@${CC} ${FLAGS} -I. -c $< -o $@

.PHONY		:	all clean fclean re test s21_graph.a s21_graph_algorithms.a cont

all			:	${LIB_CONT} ${LIB_GRAPH} ${LIB_GRAPH_ALG} ${NAME} test

# building main program
${NAME}		:	${OBJS} ${HEADER}
			${CC} ${FLAGS} ${SRC} -I. *.a -o $@

# building graph library
${LIB_GRAPH}:	${OBJS_GRAPH}
			ar rcs ${LIB_GRAPH} $?
			@ranlib ${LIB_GRAPH}

# building graph_algorithms library
${LIB_GRAPH_ALG}	:	${OBJS_ALG}
			ar rcs ${LIB_GRAPH_ALG} $?
			@ranlib ${LIB_GRAPH_ALG}

# building s21_conteiner library 
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

# building with fclean before and cleaning after
rec			:	fclean all 
			${RM} ${OBJS_GRAPH} ${OBJS_ALG} ${OBJS} ${OBJS_TEST} *.dot *.gv
			cd ./s21_containers && ${MAKE} clean

# building Unit-test
test		: 	${OBJS_TEST}
			${CC} s21_graph_algorithms_test.cpp -L. -I. ${LIB_GRAPH} ${LIB_GRAPH_ALG} ${LIB_CONT} -o test_algorithms -pthread -std=c++17 -lgtest -lgmock
			${CC} s21_graph_test.cpp -L. -I. ${LIB_GRAPH} ${LIB_GRAPH_ALG} ${LIB_CONT} -o test_graph -pthread -std=c++17 -lgtest -lgmock -g -lcgraph -lgvc

# formating & check code with google-syle
google-style:
			@cp ../materials/linters/.clang-format ./
			@clang-format -i *.cpp *.h ./s21_containers/*.cpp ./s21_containers/*.h
			clang-format -n *.cpp *.h ./s21_containers/*.cpp ./s21_containers/*.h

# checking for leaks
leaks		:
			CK_FORK=no leaks -atExit -- ./${NAME}
			CK_FORK=no leaks -atExit -- ./test_graph

install_gtest:
#			brew install web-eid/gtest/gtest
			brew install googletest

install_graphviz:
			brew install graphviz