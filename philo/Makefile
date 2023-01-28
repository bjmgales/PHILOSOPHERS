NAME= philo
CC= gcc
CFLAGS= -Wall -Wextra -Werror
RM=rm -f
SRCS= ./main.c \
./parsing.c \
./init.c \
./routine.c \
./side_ft.c \
./death_check.c \


OBJS=${SRCS:.c=.o}

all:	${NAME}

${NAME}:	${OBJS}
	${CC} ${CFLAGS} -o ${NAME} ${OBJS}

clean:
	${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
