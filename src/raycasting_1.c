/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduarte <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 13:55:36 by qduarte           #+#    #+#             */
/*   Updated: 2022/06/20 13:56:25 by qduarte          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	raycasting(t_global *g)
{
	void	*old_img;
	int		x;

	old_img = NULL;
	if (g->img.img)
		old_img = g->img.img;
	g->img.img = mlx_new_image(g->mlx, WIDTH, HEIGHT);
	g->img.address = mlx_get_data_addr(g->img.img, &g->img.bits_per_pixel,
			&g->img.line_length, &g->img.endian);
	draw_floor(g);
	draw_ceiling(g);
	x = 0;
	while (x < WIDTH)
	{
		raycasting_loop(g, x);
		x++;
	}
	draw_minimap(g);
	mlx_put_image_to_window(g->mlx, g->window, g->img.img, 0, 0);
	if (old_img)
		mlx_destroy_image(g->mlx, old_img);
	return (0);
}

void	raycasting_loop(t_global *g, int x)
{
	t_raycasting	rct;

	raycasting_init(g, x, &rct);
	calculate_side_dist(g, &rct);
	check_ray_hit(g, &rct);
	calculate_distance(g, &rct);
	calculate_line_height(&rct);
	calculate_pixels_to_fill(&rct);
	get_texture_coords(g, &rct);
	draw_vertical_stripe(g, &rct, x);
}

void	raycasting_init(t_global *g, int x, t_raycasting *rct)
{
	rct->camera_x = 2 * x / (double)WIDTH - 1;
	rct->ray_dir_x = g->player.dir_x + g->player.plane_x * rct->camera_x;
	rct->ray_dir_y = g->player.dir_y + g->player.plane_y * rct->camera_x;
	rct->map_x = (int)g->player.pos_x;
	rct->map_y = (int)g->player.pos_y;
	rct->delta_dist_x = fabs(1 / rct->ray_dir_x);
	rct->delta_dist_y = fabs(1 / rct->ray_dir_y);
}

void	calculate_side_dist(t_global *g, t_raycasting *rct)
{
	if (rct->ray_dir_x < 0)
	{
		rct->step_x = -1;
		rct->side_dist_x = (g->player.pos_x - rct->map_x) * rct->delta_dist_x;
	}
	else
	{
		rct->step_x = 1;
		rct->side_dist_x = (rct->map_x + 1.0 - g->player.pos_x)
			* rct->delta_dist_x;
	}
	if (rct->ray_dir_y < 0)
	{
		rct->step_y = -1;
		rct->side_dist_y = (g->player.pos_y - rct->map_y) * rct->delta_dist_y;
	}
	else
	{
		rct->step_y = 1;
		rct->side_dist_y = (rct->map_y + 1.0 - g->player.pos_y)
			* rct->delta_dist_y;
	}
}

void	check_ray_hit(t_global *g, t_raycasting *rct)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (rct->side_dist_x < rct->side_dist_y)
		{
			rct->side_dist_x += rct->delta_dist_x;
			rct->map_x += rct->step_x;
			rct->side = 0;
		}
		else
		{
			rct->side_dist_y += rct->delta_dist_y;
			rct->map_y += rct->step_y;
			rct->side = 1;
		}
		if (g->scene.map[rct->map_x][rct->map_y] > 0)
			hit = 1;
	}
}
