#include "cub3d.h"

int create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int get_pixel_color(t_img *img, int x, int y)
{
	char *color;

	color = img->address + (y * img->line_length + x * (img->bits_per_pixel / 8));
	return (*(int *)color);
}

int get_tex_color(t_global *g, t_raycasting *rct, int tex_y)
{
	int color;

	if (!rct->side)
	{
		if (rct->ray_dir_x < 0)
			color = get_pixel_color(&g->textures[1], rct->tex_x, tex_y);
		else
			color = get_pixel_color(&g->textures[0], rct->tex_x, tex_y);
	}
	else
	{
		if (rct->ray_dir_y < 0)
			color = get_pixel_color(&g->textures[2], rct->tex_x, tex_y);
		else
			color = get_pixel_color(&g->textures[3], rct->tex_x, tex_y);
	}
	return (color);
}
