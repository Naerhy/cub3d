#ifndef __CUB3D__
#define __CUB3D__

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "mlx.h"

typedef struct s_scene
{
	char *tex_north;
	char *tex_south;
	char *tex_east;
	char *tex_west;
	int color_floor;
	int color_ceiling;
	int **map;
} t_scene;

typedef struct s_player
{
	double pos_x;
	double pos_y;
	double dir_x;
	double dir_y;
	double plane_x;
	double plane_y;
} t_player;

typedef struct s_img
{
	void *img;
	char *address;
	int bits_per_pixel;
	int line_length;
	int endian;
} t_img;

typedef struct s_global
{
	void *mlx;
	void *window;
	t_img img;
	char **lines;
	t_scene scene;
	t_player player;
} t_global;

// close.c
void close_program(char *error_msg, t_global *global);
void free_scene(t_scene *scene);
void free_double_ptr(void **ptr);

// file.c
int file_nb_lines(char *filename);
void copy_file(char *filename, t_global *global);
void replace_nl(char *str);

// init.c
void init_scene(t_scene *scene);

// libft.c
int ft_strlen(char *str);
int ft_strcmp(char *str1, char *str2, int n);
char *ft_strcpy(char *dest, char *src, int length);
char *ft_strdup(char *src, int length);
void *ft_calloc(int nb_elem, int size);
void *ft_memset(void *ptr, int c, int n);
void ft_wrstr(int fd, char *str);
void ft_wrstr_nl(int fd, char *str);
long ft_atoi(char *str);

// parsing.c
int parse_scene(t_global *global);
int get_nb_splits(char **split);
int is_scene_parsed(t_scene *scene);
int str_to_color(char *str);
int is_digits_only(char *str);
int create_trgb(int t, int r, int g, int b);

// parsing_map.c
void parse_map(t_global *global, int index_map);
int map_exists(char **lines, int index_map);
int check_empty_line(char **lines);
int check_map_char(char **lines);
int check_start_pos(t_global *global, char **lines);
void set_player_direction(t_global *global, char direction);
int get_nb_lines(char **lines);
int alloc_lines(int **map, int nb_lines, int max_line);
int get_max_line(char **lines);
void fill_map(int **map, int nb_lines, int max_line);
void copy_map(int **map, char **lines);
int check_map_closed(int **map, int nb_lines, int max_line);

// split.c
char **ft_split(char *str, char delimiter);
int get_nb_words(char *str, char delimiter);
char **split_words(char **slit, char *str, char delimiter);
int get_nb_char(char *str, char delimiter);

#endif
