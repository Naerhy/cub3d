NAME = cub3d

SRC = src/close.c \
	  src/color.c \
	  src/cub3d.c \
	  src/draw.c \
	  src/file.c \
	  src/ft_utils_1.c \
	  src/ft_utils_2.c \
	  src/get_next_line.c \
	  src/get_next_line_utils.c \
	  src/init.c \
	  src/move.c \
	  src/parsing.c \
	  src/parsing_map_1.c \
	  src/parsing_map_2.c \
	  src/parsing_map_3.c \
	  src/raycasting_1.c \
	  src/raycasting_2.c \
	  src/rotate.c \
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
