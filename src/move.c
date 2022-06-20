/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduarte <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 13:00:19 by qduarte           #+#    #+#             */
/*   Updated: 2022/06/20 13:02:25 by qduarte          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	move_player(int keycode, t_global *global)
{
	if (keycode == 65361)
		rotate_left(global);
	if (keycode == 65363)
		rotate_right(global);
	if (keycode == 119)
		move_up(global);
	if (keycode == 115)
		move_down(global);
	if (keycode == 97)
		move_left(global);
	if (keycode == 100)
		move_right(global);
	if (keycode == 65307)
		close_program(NULL, global);
	return (0);
}

void	move_up(t_global *global)
{
	int	ipos_x;
	int	ipos_y;

	ipos_x = (int)(global->player.pos_x + global->player.dir_x * MOVESPEED);
	ipos_y = (int)(global->player.pos_y + global->player.dir_y * MOVESPEED);
	if (!global->scene.map[ipos_x][(int)global->player.pos_y])
		global->player.pos_x += global->player.dir_x * MOVESPEED;
	if (!global->scene.map[(int)global->player.pos_x][ipos_y])
		global->player.pos_y += global->player.dir_y * MOVESPEED;
}

void	move_down(t_global *global)
{
	int	ipos_x;
	int	ipos_y;

	ipos_x = (int)global->player.pos_x - global->player.dir_x * MOVESPEED;
	ipos_y = (int)global->player.pos_y - global->player.dir_y * MOVESPEED;
	if (!global->scene.map[ipos_x][(int)global->player.pos_y])
		global->player.pos_x -= global->player.dir_x * MOVESPEED;
	if (!global->scene.map[(int)global->player.pos_x][ipos_y])
		global->player.pos_y -= global->player.dir_y * MOVESPEED;
}

void	move_left(t_global *global)
{
	int	ipos_x;
	int	ipos_y;

	ipos_x = (int)(global->player.pos_x - global->player.plane_x * MOVESPEED);
	ipos_y = (int)(global->player.pos_y - global->player.plane_y * MOVESPEED);
	if (!global->scene.map[ipos_x][(int)global->player.pos_y])
		global->player.pos_x -= global->player.plane_x * MOVESPEED;
	if (!global->scene.map[(int)global->player.pos_x][ipos_y])
		global->player.pos_y -= global->player.plane_y * MOVESPEED;
}

void	move_right(t_global *global)
{
	int	ipos_x;
	int	ipos_y;

	ipos_x = (int)(global->player.pos_x + global->player.plane_x * MOVESPEED);
	ipos_y = (int)(global->player.pos_y + global->player.plane_y * MOVESPEED);
	if (!global->scene.map[ipos_x][(int)global->player.pos_y])
		global->player.pos_x += global->player.plane_x * MOVESPEED;
	if (!global->scene.map[(int)global->player.pos_x][ipos_y])
		global->player.pos_y += global->player.plane_y * MOVESPEED;
}
