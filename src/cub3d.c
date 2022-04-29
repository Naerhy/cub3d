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

	// move all these lines into launch_game function?
	// move all these lines into launch_game function?
	global.mlx = mlx_init();
	if (!global.mlx)
		close_program("unable to initialize MLX library", &global);
	load_textures(&global, global.scene.tex_north, 0, TEX_RES);
	load_textures(&global, global.scene.tex_south, 1, TEX_RES);
	load_textures(&global, global.scene.tex_east, 2, TEX_RES);
	load_textures(&global, global.scene.tex_west, 3, TEX_RES);
	global.window = mlx_new_window(global.mlx, WIDTH, HEIGHT, "cub3d");
	mlx_hook(global.window, 2, 1L<<0, move_player, &global);
	mlx_hook(global.window, 33, 1L << 2, exit_cross_game, &global);
	mlx_loop_hook(global.mlx, raycasting, &global);
	mlx_loop(global.mlx);

	// if no error, program closes succesfully
	close_program(NULL, &global);
	return (0);
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

int raycasting(t_global *global)
{
	void *old_img;

	old_img = NULL;
	if (global->img.img)
		old_img = global->img.img;
	global->img.img = mlx_new_image(global->mlx, WIDTH, HEIGHT);
	// check return error
	global->img.address = mlx_get_data_addr(global->img.img,
			&global->img.bits_per_pixel, &global->img.line_length,
			&global->img.endian);

	///////////////////////////
	
	draw_floor(global);
	draw_ceiling(global);

	int x;

	x = 0;
	while (x < WIDTH)
	{
		double camerax = 2 * x / (double)WIDTH - 1;
		double raydirx = global->player.dir_x + global->player.plane_x * camerax;
		double raydiry = global->player.dir_y + global->player.plane_y * camerax;

		int mapx = (int)global->player.pos_x;
		int mapy = (int)global->player.pos_y;

		double sidedistx;
		double sidedisty;

		double deltadistx = fabs(1 / raydirx);
		double deltadisty = fabs(1 / raydiry);

		double perpwalldist;
		int stepx;
		int stepy;
		int hit = 0;
		int side;

		if (raydirx < 0)
		{
			stepx = -1;
			sidedistx = (global->player.pos_x - mapx) * deltadistx;
		}
		else
		{
			stepx = 1;
			sidedistx = (mapx + 1.0 - global->player.pos_x) * deltadistx;
		}

		if (raydiry < 0)
		{
			stepy = -1;
			sidedisty = (global->player.pos_y - mapy) * deltadisty;
		}
		else
		{
			stepy = 1;
			sidedisty = (mapy + 1.0 - global->player.pos_y) * deltadisty;
		}

		while (hit == 0)
		{
			if (sidedistx < sidedisty)
			{
				sidedistx += deltadistx;
				mapx += stepx;
				side = 0;
			}
			else
			{
				sidedisty += deltadisty;
				mapy += stepy;
				side = 1;
			}

			if (global->scene.map[mapx][mapy] > 0)
				hit = 1;
		}

		if (side == 0)
			perpwalldist = (mapx - global->player.pos_x + (1 - stepx) / 2) / raydirx;
		else
			perpwalldist = (mapy - global->player.pos_y + (1 - stepy) / 2) / raydiry;

		int lineheight = (int)(HEIGHT / perpwalldist);

		int drawstart = -lineheight / 2 + HEIGHT / 2;
		if (drawstart < 0)
			drawstart = 0;
		int drawend = lineheight / 2 + HEIGHT / 2;
		if (drawend >= HEIGHT)
			drawend = HEIGHT - 1;

		double wallx;
		if (side == 0)
			wallx = global->player.pos_y + perpwalldist * raydiry;
		else
			wallx = global->player.pos_x + perpwalldist * raydirx;
		wallx -= floor(wallx);

		int texx = (int)(wallx * (double)TEX_RES);
		if (side == 0 && raydirx > 0)
			texx = TEX_RES - texx - 1;
		if (side == 1 && raydiry < 0)
			texx = TEX_RES - texx - 1;

		double step = 1.0 * TEX_RES / lineheight;
		double texpos = (drawstart - HEIGHT / 2 + lineheight / 2) * step;
		for (int y = drawstart; y < drawend; y++)
		{
			int texy = (int)texpos & (TEX_RES - 1);
			texpos += step;

			int color;
			if (side == 0)
			{
				if (raydirx < 0)
					color = get_pixel_color(&global->textures[0], texx, texy);
				else
					color = get_pixel_color(&global->textures[1], texx, texy);
			}
			else
			{
				if (raydiry < 0)
					color = get_pixel_color(&global->textures[2], texx, texy);
				else
					color = get_pixel_color(&global->textures[3], texx, texy);
			}
			my_mlx_pixel_put(&global->img, x, y, color);
		}

		x++;
	}


	///////////////////////////

	mlx_put_image_to_window(global->mlx, global->window, global->img.img, 0, 0);
	if (old_img)
		mlx_destroy_image(global->mlx, old_img);
	return (0);
}

int move_player(int keycode, t_global *global)
{
	double movespeed = 0.3;
	double rotspeed = 0.2;

	if (keycode == 65361) // LEFT
	{
		double olddirx = global->player.dir_x;
		global->player.dir_x = global->player.dir_x * cos(rotspeed)
			- global->player.dir_y * sin(rotspeed);
		global->player.dir_y = olddirx * sin(rotspeed) + global->player.dir_y
			* cos(rotspeed);
		double oldplanex = global->player.plane_x;
		global->player.plane_x = global->player.plane_x * cos(rotspeed)
			- global->player.plane_y * sin(rotspeed);
		global->player.plane_y = oldplanex * sin(rotspeed)
			+ global->player.plane_y * cos(rotspeed);
	}

	if (keycode == 65363) // RIGHT
	{
		double olddirx = global->player.dir_x;
		global->player.dir_x = global->player.dir_x * cos(-rotspeed)
			- global->player.dir_y * sin(-rotspeed);
		global->player.dir_y = olddirx * sin(-rotspeed) + global->player.dir_y
			* cos(-rotspeed);
		double oldplanex = global->player.plane_x;
		global->player.plane_x = global->player.plane_x * cos(-rotspeed)
			- global->player.plane_y * sin(-rotspeed);
		global->player.plane_y = oldplanex * sin(-rotspeed)
			+ global->player.plane_y * cos(-rotspeed);
	}

	if (keycode == 119) // W
	{
		if (global->scene.map[(int)(global->player.pos_x + global->player.dir_x * movespeed)]
				[(int)global->player.pos_y] == 0)
			global->player.pos_x += global->player.dir_x * movespeed;
		if (global->scene.map[(int)global->player.pos_x]
				[(int)(global->player.pos_y + global->player.dir_y * movespeed)] == 0)
			global->player.pos_y += global->player.dir_y * movespeed;
	}

	if (keycode == 115) // S
	{
		if (global->scene.map[(int)(global->player.pos_x - global->player.dir_x * movespeed)]
				[(int)global->player.pos_y] == 0)
			global->player.pos_x -= global->player.dir_x * movespeed;
		if (global->scene.map[(int)global->player.pos_x]
				[(int)(global->player.pos_y - global->player.dir_y * movespeed)] == 0)
			global->player.pos_y -= global->player.dir_y * movespeed;
	}

	if (keycode == 97) // A
	{
		if (global->scene.map[(int)(global->player.pos_x -global->player.plane_x * movespeed)]
				[(int)global->player.pos_y] == 0)
			global->player.pos_x -= global->player.plane_x * movespeed;
		if (global->scene.map[(int)global->player.pos_x]
				[(int)(global->player.pos_y - global->player.plane_y * movespeed)] == 0)
			global->player.pos_y -= global->player.plane_y * movespeed;
	}

	if (keycode == 100) // D
	{
		if (global->scene.map[(int)(global->player.pos_x + global->player.plane_x * movespeed)]
				[(int)global->player.pos_y] == 0)
			global->player.pos_x += global->player.plane_x * movespeed;
		if  (global->scene.map[(int)global->player.pos_x]
				[(int)(global->player.pos_y + global->player.plane_y * movespeed)] == 0)
			global->player.pos_y += global->player.plane_y * movespeed;
	}

	if (keycode == 65307) // ESC
		close_program(NULL, global);
	return (0);
}

int exit_cross_game(t_global *global)
{
	close_program(NULL, global);
	return (0);
}
