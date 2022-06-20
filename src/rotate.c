/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduarte <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 13:24:12 by qduarte           #+#    #+#             */
/*   Updated: 2022/06/20 13:24:27 by qduarte          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_left(t_global *global)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = global->player.dir_x;
	old_plane_x = global->player.plane_x;
	global->player.dir_x = global->player.dir_x * cos(ROTSPEED)
		- global->player.dir_y * sin(ROTSPEED);
	global->player.dir_y = old_dir_x * sin(ROTSPEED) + global->player.dir_y
		* cos(ROTSPEED);
	global->player.plane_x = global->player.plane_x * cos(ROTSPEED)
		- global->player.plane_y * sin(ROTSPEED);
	global->player.plane_y = old_plane_x * sin(ROTSPEED)
		+ global->player.plane_y * cos(ROTSPEED);
}

void	rotate_right(t_global *global)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = global->player.dir_x;
	old_plane_x = global->player.plane_x;
	global->player.dir_x = global->player.dir_x * cos(-ROTSPEED)
		- global->player.dir_y * sin(-ROTSPEED);
	global->player.dir_y = old_dir_x * sin(-ROTSPEED) + global->player.dir_y
		* cos(-ROTSPEED);
	global->player.plane_x = global->player.plane_x * cos(-ROTSPEED)
		- global->player.plane_y * sin(-ROTSPEED);
	global->player.plane_y = old_plane_x * sin(-ROTSPEED)
		+ global->player.plane_y * cos(-ROTSPEED);
}
