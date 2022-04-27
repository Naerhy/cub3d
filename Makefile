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

MLXFLAGS = -Lmlx_linux -lmlx -lXext -lX11 -lm

RM = rm -rf

.c.o:
	${CC} ${CFLAGS} -Iinc -Imlx_linux -c $< -o ${<:.c=.o}

${NAME}: ${OBJ}
	make -C mlx_linux
	${CC} -o ${NAME} ${OBJ} ${MLXFLAGS}

all: ${NAME}

clean:
	make -C mlx_linux clean
	${RM} ${OBJ}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
