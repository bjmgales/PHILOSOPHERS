NAME= philosophers
CC= gcc
CFLAGS= -Wall -Wextra -Werror
RM=rm -f
SRCS= ./philosophers.c \
./ft_atoi.c \
./init.c \
./small_ft.c \


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
