#include "cub3d.h"

void init_scene(t_scene *scene)
{
	scene->tex_north = NULL;
	scene->tex_south = NULL;
	scene->tex_east = NULL;
	scene->tex_west = NULL;
	scene->color_floor = -1;
	scene->color_ceiling = -1;
}
