#include "cub3d.h"

void init_global(t_global *global)
{
	int i;

	i = 0;
	global->mlx = NULL;
	global->window = NULL;
	global->img.img = NULL;
	while (i < 4)
	{
		global->textures[i].img = NULL;
		i++;
	}
	global->lines = NULL;
	global->scene.tex_north = NULL;
	global->scene.tex_south = NULL;
	global->scene.tex_east = NULL;
	global->scene.tex_west = NULL;
	global->scene.color_floor = -1;
	global->scene.color_ceiling = -1;
	global->scene.map = NULL;
	global->player.dir_x = 0.0;
	global->player.dir_y = 0.0;
	global->player.plane_x = 0.0;
	global->player.plane_y = 0.0;
}
