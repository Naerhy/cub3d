#include "cub3d.h"

void close_program(char *error_msg, t_global *global)
{
	free_double_ptr((void **)global->lines);
	free_scene(&global->scene);
	if (error_msg)
	{
		ft_wrstr(2, "Error: ");
		ft_wrstr_nl(2, error_msg);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

void free_scene(t_scene *scene) // could pass by value but let's optimize a bit
{
	free(scene->tex_north);
	free(scene->tex_south);
	free(scene->tex_east);
	free(scene->tex_west);
}

void free_double_ptr(void **ptr)
{
	char **ptr_c;
	int i;

	ptr_c = (char **)ptr;
	if (ptr_c)
	{
		i = 0;
		while (ptr_c[i])
		{
			free(ptr_c[i]);
			i++;
		}
		free(ptr_c);
	}
}
