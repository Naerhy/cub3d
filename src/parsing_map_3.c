/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduarte <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 13:57:14 by qduarte           #+#    #+#             */
/*   Updated: 2022/06/20 13:57:52 by qduarte          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	copy_map(int **map, char **lines)
{
	int	i;
	int	j;

	i = 0;
	while (lines[i])
	{
		j = 0;
		while (lines[i][j])
		{
			if (lines[i][j] == ' ')
				map[i + 4][j + 4] = 8;
			else
				map[i + 4][j + 4] = lines[i][j] - 48;
			j++;
		}
		i++;
	}
}

int	check_map_closed(int **map, int nb_lines, int max_line)
{
	int	i;
	int	j;

	i = 0;
	while (i < nb_lines)
	{
		j = 0;
		while (j < max_line)
		{
			if (!map[i][j] && (map[i + 1][j] == 8 || map[i - 1][j] == 8
						|| map[i][j + 1] == 8 || map[i][j - 1] == 8
						|| map[i + 1][j + 1] == 8 || map[i - 1][j - 1] == 8
						|| map[i + 1][j - 1] == 8 || map[i - 1][j + 1] == 8))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
