/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduarte <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 13:58:01 by qduarte           #+#    #+#             */
/*   Updated: 2022/06/20 13:58:31 by qduarte          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_player_direction(t_global *global, char direction)
{
	if (direction == 'N')
	{
		global->player.dir_x = -1.0;
		global->player.plane_y = 0.66;
	}
	else if (direction == 'S')
	{
		global->player.dir_x = 1.0;
		global->player.plane_y = -0.66;
	}
	else if (direction == 'E')
	{
		global->player.dir_y = 1.0;
		global->player.plane_x = 0.66;
	}
	else
	{
		global->player.dir_y = -1.0;
		global->player.plane_x = -0.66;
	}
}

int	get_nb_lines(char **lines)
{
	int	i;

	i = 0;
	while (lines[i])
		i++;
	return (i);
}

int	get_max_line(char **lines)
{
	int	max;
	int	i;

	max = 0;
	i = 0;
	while (lines[i])
	{
		if (ft_strlen(lines[i]) > max)
			max = ft_strlen(lines[i]);
		i++;
	}
	return (max);
}

int	alloc_lines(int **map, int nb_lines, int max_line)
{
	int	i;

	i = 0;
	while (i < nb_lines)
	{
		map[i] = ft_calloc(max_line, sizeof(int));
		if (!map[i])
			return (0);
		i++;
	}
	return (1);
}

void	fill_map(int **map, int nb_lines, int max_line)
{
	int	i;
	int	j;

	i = 0;
	while (i < nb_lines)
	{
		j = 0;
		while (j < max_line)
		{
			map[i][j] = 8;
			j++;
		}
		i++;
	}
}
