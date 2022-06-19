#include "cub3d.h"

int main(int argc, char **argv)
{
	t_global global;
	int index_map;
	int nb_lines;

	init_global(&global);
	if (argc != 2)
		close_program("invalid number of arguments", &global);
	if (ft_strlen(argv[1]) <= 4 ||
			ft_strcmp(".cub", argv[1] + ft_strlen(argv[1]) - 4, 4))
		close_program("invalid filename", &global);
	nb_lines = file_nb_lines(argv[1]) + 1;
	if (nb_lines == -1)
		close_program("unable to get file's number of lines", &global);
	global.lines = ft_calloc(nb_lines, sizeof(char *));
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

void my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char *dst;

	dst = img->address + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int exit_cross_game(t_global *global)
{
	close_program(NULL, global);
	return (0);
}
