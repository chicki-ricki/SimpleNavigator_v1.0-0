# # В операционных системах GNU/Linux имена файлов библиотек должны иметь префикс "lib", статические библиотеки - расширение *.a, динамические - *.so.

NAME			=	graph

SRC				=	main.cpp

OBJS			=	${SRC:%.cpp=%.o}



NAME_GRAPH		=	s21_graph.a

SRC_GRAPH		=	s21_graph.cpp

HEADERS_GRAPH	=	s21_graph.h

OBJS_GRAPH	=	${SRC_GRAPH:%.cpp=%.o}



NAME_ALG	=	libs21_graph_algorithms.a

SRC_ALG		=	s21_graph_algorithms.cpp

HEADERS_ALG	=	s21_graph_algorithms.h

OBJS_ALG	=	${SRC_ALG:%.cpp=%.o}

FLAGS	=	-g -Wall -Wextra -lstdc++ -std=c++17 -Wno-unused# -Werror

CC		=	c++

RM		=	rm -f

.PHONY	:	all clean fclean re test s21_graph.a s21_graph_algorithms.a

%.o		:	%.cpp ${HEADERS_GRAPH} ${HEADERS_ALG}
			${CC} ${FLAGS} -c $< -o $@

# %.o		:	%.cpp ${HEADERS_1} ${HEADERS_2}
# 	${CC} ${FLAGS} -c $< -o $@

${NAME}:	${OBJS}
	${MAKE} ${NAME_ALG}
	${CC} ${FLAGS} -I. ${SRC} -L. -ls21_graph_algorithms -o $@

all		:	${NAME}

${NAME_GRAPH}	:	${OBJS_GRAPH} ${HEADERS_GRAPH}
			cd ./s21_containers && ${MAKE}
			ar rcs ${NAME_GRAPH} s21_containers/*.o $?

${NAME_ALG}	:	${OBJS_ALG} ${HEADERS_ALG} ${OBJS_GRAPH} ${HEADERS_GRAPH}
#			${MAKE} ${NAME_GRAPH}
			ar rcs ${NAME_ALG} $?

# ${NAME_2}:	${OBJS_2}
# 	${CC} ${FLAGS} -I ${HEADERS_2} ${SRC_2} -o $@

# all		:	${NAME_1} ${NAME_2}

clean	:
	${RM} ${OBJS_GRAPH} ${OBJS_ALG} ${OBJS}
	cd ./s21_containers && ${MAKE} clean

fclean	:	clean
	${RM} ${NAME} ${NAME_GRAPH} ${NAME_ALG}
	cd ./s21_containers && ${MAKE} fclean

re		:	fclean all

# # test	:




# all:	s21_graph_algorithms.h s21_graph.h s21_containers/s21_containers.h s21_containers/s21_stack.h s21_containers/s21_stack.tpp s21_containers/s21_utils.h
# 	c++ -g -Wall -Werror -Wextra -lstdc++ -std=c++17 -Wno-unused main.cpp s21_graph.cpp s21_containers/s21_utils.cpp s21_graph_algorithms.cpp -o graph
