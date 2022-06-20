/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduarte <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 13:03:26 by qduarte           #+#    #+#             */
/*   Updated: 2022/06/20 13:21:23 by qduarte          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_floor(t_global *global)
{
	int	x;
	int	y;

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

void	draw_ceiling(t_global *global)
{
	int	x;
	int	y;

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

void	draw_minimap(t_global *g)
{
	int	start_x;
	int	start_y;
	int	i;
	int	j;

	start_x = (int)g->player.pos_x - 4;
	start_y = (int)g->player.pos_y - 4;
	i = 0;
	while (i < MINIMAP_SIZE)
	{
		j = 0;
		while (j < MINIMAP_SIZE)
		{
			if (g->scene.map[start_x + i][start_y + j] == 1)
				draw_mm_rect(g, j * MR, i * MR, create_trgb(0, 0, 102, 204));
			else if (g->scene.map[start_x + i][start_y + j] == 8)
				draw_mm_rect(g, j * MR, i * MR, create_trgb(0, 0, 0, 0));
			else
				draw_mm_rect(g, j * MR, i * MR, create_trgb(0, 192, 192, 192));
			j++;
		}
		i++;
	}
	draw_mm_rect(g, 4 * MR, 4 * MR, create_trgb(0, 255, 255, 0));
}

void	draw_mm_rect(t_global *g, int start_x, int start_y, int color)
{
	int	x;
	int	y;

	x = 0;
	while (x < MR)
	{
		y = 0;
		while (y < MR)
		{
			my_mlx_pixel_put(&g->img, start_x + x, start_y + y, color);
			y++;
		}
		x++;
	}
}

void	draw_vertical_stripe(t_global *g, t_raycasting *rct, int x)
{
	double	step;
	double	tex_pos;
	int		tex_y;
	int		y;

	step = 1.0 * TEX_RES / rct->line_height;
	tex_pos = (rct->draw_start - HEIGHT / 2 + rct->line_height / 2) * step;
	y = rct->draw_start;
	while (y < rct->draw_end)
	{
		tex_y = (int)tex_pos & (TEX_RES - 1);
		tex_pos += step;
		my_mlx_pixel_put(&g->img, x, y, get_tex_color(g, rct, tex_y));
		y++;
	}
}
