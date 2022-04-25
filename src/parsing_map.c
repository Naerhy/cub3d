#include "cub3d.h"

void parse_map(t_global *global, int index_map)
{
	int begin;
	int nb_lines;
	int max_line;

	begin = map_exists(global->lines, index_map);
	if (begin == -1 || check_empty_line(global->lines + begin)
			|| !check_map_char(global->lines + begin))
		close_program("invalid map description", global);
	nb_lines = get_nb_lines(global->lines + begin);
	global->scene.map = ft_calloc(nb_lines + 3, sizeof(int *));
	if (!global->scene.map)
		close_program("unable to allocate memory", global);
	max_line = get_max_line(global->lines + begin);
	if (!alloc_lines(global->scene.map, nb_lines + 2, max_line + 3))
		close_program("unable to allocate memory", global);
	// remove letters and set player position in variable
	// => if position already set and letters again = error
	// transform array char into int and add to global->map
	fill_map(global->scene.map, nb_lines + 2, max_line + 2);
	copy_map(global->scene.map, global->lines + begin);
}

int map_exists(char **lines, int index_map)
{
	while (lines[index_map])
	{
		if (ft_strlen(lines[index_map]))
			return (index_map);
		index_map++;
	}
	return (-1);
}

int check_empty_line(char **lines)
{
	int i;

	i = 0;
	while (lines[i])
	{
		if (!ft_strlen(lines[i]))
			return (1);
		i++;
	}
	return (0);
}

int check_map_char(char **lines)
{
	int i;
	int j;

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

int get_nb_lines(char **lines)
{
	int i;

	i = 0;
	while (lines[i])
		i++;
	return (i);
}

int alloc_lines(int **map, int nb_lines, int max_line)
{
	int i;

	i = 0;
	while (i < nb_lines)
	{
		map[i] = ft_calloc(max_line + 3, sizeof(int));
		if (!map[i])
			return (0);
		i++;
	}
	return (1);
}

int get_max_line(char **lines)
{
	int max;
	int i;

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

void fill_map(int **map, int nb_lines, int max_line)
{
	int i;
	int j;

	i = 0;
	while (i < nb_lines)
	{
		j = 0;
		while (j < max_line)
		{
			map[i][j] = 5;
			j++;
		}
		i++;
	}
}

void copy_map(int **map, char **lines)
{
	int i;
	int j;

	i = 0;
	while (lines[i])
	{
		j = 0;
		while (lines[i][j])
		{
			map[i + 1][j + 1] = lines[i][j] - 48;
			j++;
		}
		i++;
	}
}
