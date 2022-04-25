NAME = cub3d

SRC = src/close.c \
	  src/cub3d.c \
	  src/file.c \
	  src/init.c \
	  src/libft.c \
	  src/parsing.c \
	  src/parsing_map.c \
	  src/split.c

OBJ = ${SRC:.c=.o}

CC = gcc

CFLAGS = -Wall -Werror -Wextra

RM = rm -rf

.c.o:
	${CC} ${CFLAGS} -Iinc -c $< -o ${<:.c=.o}

${NAME}: ${OBJ}
	${CC} -o ${NAME} ${OBJ}

all: ${NAME}

clean:
	${RM} ${OBJ}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
