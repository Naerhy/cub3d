/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduarte <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 13:53:36 by qduarte           #+#    #+#             */
/*   Updated: 2022/06/20 13:54:20 by qduarte          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strcmp(char *str1, char *str2, int n)
{
	int	i;

	i = 0;
	while (i < n && (str1[i] || str2[i]))
	{
		if (!(str1[i] - str2[i]))
			i++;
		else
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
	}
	return (0);
}

char	*ft_strcpy(char *dest, char *src, int length)
{
	int	i;

	i = 0;
	while (i < length && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(char *src, int length)
{
	char	*dup;

	dup = ft_calloc(length + 1, sizeof(char));
	if (!dup)
		return (NULL);
	dup = ft_strcpy(dup, src, length);
	return (dup);
}

void	*ft_calloc(int nb_elem, int size)
{
	void	*mem_zone;

	mem_zone = malloc(nb_elem * size);
	if (!mem_zone)
		return (NULL);
	mem_zone = ft_memset(mem_zone, 0, nb_elem * size);
	return (mem_zone);
}
