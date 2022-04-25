#include "cub3d.h"

int parse_scene(t_global *global)
{
	char **split;
	int i;

	i = 0;
	while (!is_scene_parsed(&global->scene) && global->lines[i])
	{
		if (ft_strlen(global->lines[i]))
		{
			split = ft_split(global->lines[i], ' ');
			if (!split)
				close_program("invalid split return value", global);
			if (get_nb_splits(split) == 2)
			{
				if (!ft_strcmp(split[0], "NO", ft_strlen(split[0])))
					global->scene.tex_north = ft_strdup(split[1],
							ft_strlen(split[1]));
				else if (!ft_strcmp(split[0], "SO", ft_strlen(split[0])))
					global->scene.tex_south = ft_strdup(split[1],
							ft_strlen(split[1]));
				else if (!ft_strcmp(split[0], "EA", ft_strlen(split[0])))
					global->scene.tex_east = ft_strdup(split[1],
							ft_strlen(split[1]));
				else if (!ft_strcmp(split[0], "WE", ft_strlen(split[0])))
					global->scene.tex_west = ft_strdup(split[1],
							ft_strlen(split[1]));
				else if (!ft_strcmp(split[0], "F", ft_strlen(split[0])))
					global->scene.color_floor = str_to_color(split[1]);
				else if (!ft_strcmp(split[0], "C", ft_strlen(split[0])))
					global->scene.color_ceiling = str_to_color(split[1]);
				else
				{
					free_double_ptr((void **)split);
					close_program("invalid line in scene description", global);
				}
			}
			free_double_ptr((void **)split);
		}
		i++;
	}
	if (!is_scene_parsed(&global->scene))
		close_program("incomplete scene description", global);
	return (i);
}

int get_nb_splits(char **split)
{
	int i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

int is_scene_parsed(t_scene *scene)
{
	if (scene->tex_north && scene->tex_south && scene->tex_east
			&& scene->tex_west && scene->color_floor  != -1
			&& scene->color_ceiling != -1)
		return (1);
	return (0);
}

// optimize this function => better readability
int str_to_color(char *str)
{
	char **split;
	int color;

	split = ft_split(str, ',');
	color = -1;
	if (split && get_nb_splits(split) == 3 && is_digits_only(split[0])
			&& is_digits_only(split[1]) && is_digits_only(split[2]))
		color = create_trgb(0, ft_atoi(split[0]), ft_atoi(split[1]),
				ft_atoi(split[2]));
	free_double_ptr((void **)split);
	return (color);
}

int is_digits_only(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void parse_map(t_global *global, int index_map)
{
	char **map;
	int begin;

	begin = map_exists(&global->lines[index_map]);
	if (begin == -1 || empty_line_map(&global->lines[begin])
			|| check_map_char(&global->lines[begin]))
		close_program("invalid map description", global);
	map = ft_calloc(get_map_lines(&global->lines[begin]) + 3, sizeof(char));
	if (!map)
		close_program("unable to allocate memory", global);

}

int map_exists(char **lines)
{
	int i;

	i = 0;
	while (lines[i])
	{
		if (ft_strlen(lines[i]))
			return (i);
		i++;
	}
	return (-1);
}

int get_max_line(char **lines)
{
	int max;

	max = 0;
	while (lines[i])
	{
		if (ft_strlen(lines[i]) > max)
			max = ft_strlen(lines[i]);
		i++;
	}
	return (max);
}

int empty_line_map(char **lines)
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
					&& lines[i][j] != 'W')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int get_map_lines(char **lines)
{
	int i;

	i = 0;
	while (lines[i])
		i++;
	return (i);
}
