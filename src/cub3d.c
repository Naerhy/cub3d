#include "cub3d.h"

int main(int argc, char **argv)
{
	t_global global;
	int index_map;

	init_global(&global);
	if (argc != 2)
		close_program("invalid number of arguments", &global);
	if (ft_strlen(argv[1]) <= 4 ||
			ft_strcmp(".cub", argv[1] + ft_strlen(argv[1]) - 4, 4))
		close_program("invalid filename", &global);
	global.lines = ft_calloc(file_nb_lines(argv[1]) + 1, sizeof(char *));
	if (!global.lines)
		close_program("unable to allocate memory", &global);
	copy_file(argv[1], &global);
	index_map = parse_scene(&global);
	parse_map(&global, index_map);
	launch_game(&global);
	close_program(NULL, &global);
	return (0);
}

void launch_game(t_global *global)
{
	global->mlx = mlx_init();
	if (!global->mlx)
		close_program("unable to initialize MLX library", global);
	load_textures(global, global->scene.tex_north, 0, TEX_RES);
	load_textures(global, global->scene.tex_south, 1, TEX_RES);
	load_textures(global, global->scene.tex_east, 2, TEX_RES);
	load_textures(global, global->scene.tex_west, 3, TEX_RES);
	global->window = mlx_new_window(global->mlx, WIDTH, HEIGHT, "cub3d");
	mlx_hook(global->window, 2, 1L<<0, move_player, global);
	mlx_hook(global->window, 33, 1L << 2, exit_cross_game, global);
	mlx_loop_hook(global->mlx, raycasting, global);
	mlx_loop(global->mlx);
}

void load_textures(t_global *global, char *tex_path, int n, int resolution)
{
	global->textures[n].img = mlx_xpm_file_to_image(global->mlx, tex_path,
			&resolution, &resolution);
	if (!global->textures[n].img)
		close_program("unable to convert xpm file", global);
	global->textures[n].address = mlx_get_data_addr(global->textures[n].img,
			&global->textures[n].bits_per_pixel,
			&global->textures[n].line_length, &global->textures[n].endian);
}

int get_pixel_color(t_img *img, int x, int y)
{
	char *color;

	color = img->address + (y * img->line_length + x * (img->bits_per_pixel / 8));
	return (*(int *)color);
}

void my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char *dst;

	dst = img->address + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void draw_floor(t_global *global)
{
	int x;
	int y;

	x = 0;
	while (x < WIDTH)
	{
		y = HEIGHT / 2;
		while (y < HEIGHT)
		{
			my_mlx_pixel_put(&global->img, x, y, global->scene.color_floor);
			y++;
		}
		x++;
	}
}

void draw_ceiling(t_global *global)
{
	int x;
	int y;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT / 2)
		{
			my_mlx_pixel_put(&global->img, x, y, global->scene.color_ceiling);
			y++;
		}
		x++;
	}
}

void draw_minimap(t_global *g)
{
	int start_x;
	int start_y;
	int i;
	int j;

	start_x = (int)g->player.pos_x - 4;
	start_y = (int)g->player.pos_y - 4;
	i = 0;
	while (i < MINIMAP_SIZE)
	{
		j = 0;
		while (j < MINIMAP_SIZE)
		{
			if (g->scene.map[start_x + i][start_y + j] == 1)
				draw_minimap_rect(g, j * MINIMAP_RES, i * MINIMAP_RES,
						create_trgb(0, 0, 102, 204));
			else if (g->scene.map[start_x + i][start_y + j] == 8)
				draw_minimap_rect(g, j * MINIMAP_RES, i * MINIMAP_RES,
						create_trgb(0, 0, 0, 0));
			else
				draw_minimap_rect(g, j * MINIMAP_RES, i * MINIMAP_RES,
						create_trgb(0, 192, 192, 192));
			j++;
		}
		i++;
	}
	draw_minimap_rect(g, 4 * MINIMAP_RES, 4 * MINIMAP_RES,
			create_trgb(0, 255, 255, 0));
}

void draw_minimap_rect(t_global *g, int start_x, int start_y, int color)
{
	int x;
	int y;

	x = 0;
	while (x < MINIMAP_RES)
	{
		y = 0;
		while (y < MINIMAP_RES)
		{
			my_mlx_pixel_put(&g->img, start_x + x, start_y + y, color);
			y++;
		}
		x++;
	}
}

int move_player(int keycode, t_global *global)
{
	if (keycode == 65361) // LEFT
		rotate_left(global);
	if (keycode == 65363) // RIGHT
		rotate_right(global);
	if (keycode == 119) // W
		move_up(global);
	if (keycode == 115) // S
		move_down(global);
	if (keycode == 97) // A
		move_left(global);
	if (keycode == 100) // D
		move_right(global);
	if (keycode == 65307) // ESC
		close_program(NULL, global);
	return (0);
}

int exit_cross_game(t_global *global)
{
	close_program(NULL, global);
	return (0);
}
