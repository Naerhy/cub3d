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

int str_to_color(char *str)
{
	char **split;
	int colors[3];

	split = ft_split(str, ',');
	if (!split || get_nb_splits(split) != 3 || !is_digits_only(split[0])
			|| !is_digits_only(split[1]) || !is_digits_only(split[2]))
		return (-1);
	colors[0] = ft_atoi(split[0]);
	colors[1] = ft_atoi(split[1]);
	colors[2] = ft_atoi(split[2]);
	free_double_ptr((void **)split);
	if (colors[0] > 255 || colors[1] > 255 || colors[2] > 255)
		return (-1);
	return (create_trgb(0, colors[0], colors[1], colors[2]));
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
