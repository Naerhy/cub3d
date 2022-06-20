/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduarte <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 13:58:43 by qduarte           #+#    #+#             */
/*   Updated: 2022/06/20 13:59:38 by qduarte          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_map(t_global *global, int index_map)
{
	int	begin;
	int	nb_lines;
	int	max_line;

	begin = map_exists(global->lines, index_map);
	if (begin == -1 || check_empty_line(global->lines + begin)
		|| !check_map_char(global->lines + begin)
		|| check_start_pos(global, global->lines + begin) != 1)
		close_program("invalid map description", global);
	nb_lines = get_nb_lines(global->lines + begin);
	max_line = get_max_line(global->lines + begin);
	global->scene.map = ft_calloc(nb_lines + 9, sizeof(int *));
	if (!global->scene.map)
		close_program("unable to allocate memory", global);
	if (!alloc_lines(global->scene.map, nb_lines + 8, max_line + 9))
		close_program("unable to allocate memory", global);
	fill_map(global->scene.map, nb_lines + 8, max_line + 8);
	copy_map(global->scene.map, global->lines + begin);
	if (!check_map_closed(global->scene.map, nb_lines + 8, max_line + 8))
		close_program("map is not closed", global);
}

int	map_exists(char **lines, int index_map)
{
	while (lines[index_map])
	{
		if (ft_strlen(lines[index_map]))
			return (index_map);
		index_map++;
	}
	return (-1);
}

int	check_empty_line(char **lines)
{
	int	i;

	i = 0;
	while (lines[i])
	{
		if (!ft_strlen(lines[i]))
			return (1);
		i++;
	}
	return (0);
}

int	check_map_char(char **lines)
{
	int	i;
	int	j;

	i = 0;
	while (lines[i])
	{
		j = 0;
		while (lines[i][j])
		{
			if (lines[i][j] != '1' && lines[i][j] != '0' && lines[i][j] != 'N'
					&& lines[i][j] != 'S' && lines[i][j] != 'E'
					&& lines[i][j] != 'W' && lines[i][j] != ' ')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	check_start_pos(t_global *global, char **lines)
{
	int	nb_start;
	int	i;
	int	j;

	nb_start = 0;
	i = 0;
	while (lines[i])
	{
		j = 0;
		while (lines[i][j])
		{
			if (lines[i][j] == 'N' || lines[i][j] == 'S' || lines[i][j] == 'E'
					|| lines[i][j] == 'W')
			{
				global->player.pos_x = i + 4.5;
				global->player.pos_y = j + 4.5;
				set_player_direction(global, lines[i][j]);
				lines[i][j] = '0';
				nb_start++;
			}
			j++;
		}
		i++;
	}
	return (nb_start);
}
