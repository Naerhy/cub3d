/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduarte <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 13:28:50 by qduarte           #+#    #+#             */
/*   Updated: 2022/06/20 13:29:32 by qduarte          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	close_program(char *error_msg, t_global *global)
{
	free_double_ptr((void **)global->lines);
	free_scene(&global->scene);
	free_mlx(global);
	if (error_msg)
	{
		ft_wrstr(2, "Error: ");
		ft_wrstr_nl(2, error_msg);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

void	free_scene(t_scene *scene)
{
	free(scene->tex_north);
	free(scene->tex_south);
	free(scene->tex_east);
	free(scene->tex_west);
	free_double_ptr((void **)scene->map);
}

void	free_mlx(t_global *global)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (global->textures[i].img)
			mlx_destroy_image(global->mlx, global->textures[i].img);
		i++;
	}
	if (global->img.img)
		mlx_destroy_image(global->mlx, global->img.img);
	if (global->window)
		mlx_destroy_window(global->mlx, global->window);
	if (global->mlx)
	{
		mlx_destroy_display(global->mlx);
		free(global->mlx);
	}
}

void	free_double_ptr(void **ptr)
{
	char	**ptr_c;
	int		i;

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
