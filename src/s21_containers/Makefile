NAME			=	s21_containers.a

SRCS			=	s21_utils.cpp

HEADERS_QUEUE	=	s21_queue.h s21_queue.tpp

HEADERS_STACK	=	s21_stack.h s21_stack.tpp

HEADERS			=	${HEADERS_QUEUE} ${HEADERS_STACK} s21_utils.h

OBJS			=	${SRCS:%.cpp=%.o}

CFLAGS			=	-g -Wall -Wextra -Werror -std=c++17# -lstdc++ -Wunused-command-line-argument

CC				=	c++

RM				=	rm -f

.PHONY	:	all clean fclean re

%.o		:	%.cpp ${HEADERS}
			${CC} ${CFLAGS} -c $< -o $@

${NAME}	:	${OBJS}# ${HEADERS}
			ar rcs ${NAME} $?

all		:	${NAME}

clean	:
			${RM} ${OBJS}

fclean	:	clean
			${RM} ${NAME}

re		:	fclean all
