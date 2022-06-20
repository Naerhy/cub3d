/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduarte <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 13:56:33 by qduarte           #+#    #+#             */
/*   Updated: 2022/06/20 13:56:59 by qduarte          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_distance(t_global *g, t_raycasting *rct)
{
	if (!rct->side)
		rct->perp_wall_dist = (rct->map_x - g->player.pos_x
				+ (1 - rct->step_x) / 2) / rct->ray_dir_x;
	else
		rct->perp_wall_dist = (rct->map_y - g->player.pos_y
				+ (1 - rct->step_y) / 2) / rct->ray_dir_y;
}

void	calculate_line_height(t_raycasting *rct)
{
	rct->line_height = (int)(HEIGHT / rct->perp_wall_dist);
}

void	calculate_pixels_to_fill(t_raycasting *rct)
{
	rct->draw_start = -rct->line_height / 2 + HEIGHT / 2;
	if (rct->draw_start < 0)
		rct->draw_start = 0;
	rct->draw_end = rct->line_height / 2 + HEIGHT / 2;
	if (rct->draw_end >= HEIGHT)
		rct->draw_end = HEIGHT - 1;
}

void	get_texture_coords(t_global *g, t_raycasting *rct)
{
	double	wall_x;

	if (!rct->side)
		wall_x = g->player.pos_y + rct->perp_wall_dist * rct->ray_dir_y;
	else
		wall_x = g->player.pos_x + rct->perp_wall_dist * rct->ray_dir_x;
	wall_x -= floor(wall_x);
	rct->tex_x = (int)(wall_x * (double)TEX_RES);
	if (!rct->side && rct->ray_dir_x > 0)
		rct->tex_x = TEX_RES - rct->tex_x - 1;
	if (rct->side == 1 && rct->ray_dir_y < 0)
		rct->tex_x = TEX_RES - rct->tex_x - 1;
}
