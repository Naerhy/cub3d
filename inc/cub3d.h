#ifndef __CUB3D__
#define __CUB3D__

#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "mlx.h"

#define WIDTH 1280
#define HEIGHT 720
#define TEX_RES 64
#define MINIMAP_RES 24
#define MINIMAP_SIZE 9
#define MOVESPEED 0.2
#define ROTSPEED 0.2
#define BUFFER_SIZE 64

typedef struct s_raycasting
{
	double camera_x;
	double ray_dir_x;
	double ray_dir_y;
	int map_x;
	int map_y;
	double side_dist_x;
	double side_dist_y;
	double delta_dist_x;
	double delta_dist_y;
	double perp_wall_dist;
	int step_x;
	int step_y;
	int side;
	int line_height;
	int draw_start;
	int draw_end;
	int tex_x;
} t_raycasting;

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
	t_img textures[4];
	char **lines;
	t_scene scene;
	t_player player;
} t_global;

// close.c
void close_program(char *error_msg, t_global *global);
void free_scene(t_scene *scene);
void free_mlx(t_global *global);
void free_double_ptr(void **ptr);

// color.c
int create_trgb(int t, int r, int g, int b);
int get_pixel_color(t_img *img, int x, int y);
int get_tex_color(t_global *g, t_raycasting *rct, int tex_y);

// cub3d.c
void launch_game(t_global *global);
void load_textures(t_global *global, char *texpath, int n, int resolution);
void my_mlx_pixel_put(t_img *img, int x, int y, int color);
int exit_cross_game(t_global *global);

// draw.c
void draw_floor(t_global *global);
void draw_ceiling(t_global *global);
void draw_minimap(t_global *g);
void draw_minimap_rect(t_global *g, int start_x, int start_y, int color);
void draw_vertical_stripe(t_global *g, t_raycasting *rct, int x);

// file.c
int file_nb_lines(char *filename);
void copy_file(char *filename, t_global *global);

// ft_utils_1.c
int ft_strlen(char *str);
int ft_strcmp(char *str1, char *str2, int n);
char *ft_strcpy(char *dest, char *src, int length);
char *ft_strdup(char *src, int length);
void *ft_calloc(int nb_elem, int size);

// ft_utils_2.c
void *ft_memset(void *ptr, int c, int n);
void ft_wrstr(int fd, char *str);
void ft_wrstr_nl(int fd, char *str);
long ft_atoi(char *str);

// get_next_line.c
void clear_buf(char *buffer, int index);
int chk_buf_read(char *buffer, int *p_buf_len, char **line);
int to_return(char **line, int buf_len);
int get_next_line(int fd, char **line);

// get_next_line_utils.c
int cpy_buf(char *buffer, int index, int len);
int nl_index(char *buffer, int len);
char *gnl_strdup(char *src, int len);
char *gnl_strjoin(char *line, char *str2,int len);

// init.c
void init_global(t_global *global);

// move.c
int move_player(int keycode, t_global *global);
void move_up(t_global *global);
void move_down(t_global *global);
void move_left(t_global *global);
void move_right(t_global *global);

// parsing.c
int parse_scene(t_global *global);
int get_nb_splits(char **split);
int is_scene_parsed(t_scene *scene);
int str_to_color(char *str);
int is_digits_only(char *str);

// parsing_map_1.c
void parse_map(t_global *global, int index_map);
int map_exists(char **lines, int index_map);
int check_empty_line(char **lines);
int check_map_char(char **lines);
int check_start_pos(t_global *global, char **lines);

// parsing_map_2.c
void set_player_direction(t_global *global, char direction);
int get_nb_lines(char **lines);
int get_max_line(char **lines);
int alloc_lines(int **map, int nb_lines, int max_line);
void fill_map(int **map, int nb_lines, int max_line);

// parsing_map_3.c
void copy_map(int **map, char **lines);
int check_map_closed(int **map, int nb_lines, int max_line);

// raycasting_1.c
int raycasting(t_global *g);
void raycasting_loop(t_global *g, int x);
void raycasting_init(t_global *g, int x, t_raycasting *rct);
void calculate_side_dist(t_global *g, t_raycasting *rct);
void check_ray_hit(t_global *g, t_raycasting *rct);

// raycasting_2.c
void calculate_distance(t_global *g, t_raycasting *rct);
void calculate_line_height(t_raycasting *rct);
void calculate_pixels_to_fill(t_raycasting *rct);
void get_texture_coords(t_global *g, t_raycasting *rct);

// rotate.c
void rotate_left(t_global *global);
void rotate_right(t_global *global);

// split.c
char **ft_split(char *str, char delimiter);
int get_nb_words(char *str, char delimiter);
char **split_words(char **slit, char *str, char delimiter);
int get_nb_char(char *str, char delimiter);

#endif
