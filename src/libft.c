#include "cub3d.h"

// temporary file until I import my own libft or idk !!!
// temporary file until I import my own libft or idk !!!
// temporary file until I import my own libft or idk !!!

int ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int ft_strcmp(char *str1, char *str2, int n)
{
	int i;

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

char *ft_strcpy(char *dest, char *src, int length)
{
	int i;

	i = 0;
	while (i < length && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char *ft_strdup(char *src, int length)
{
	char *dup;

	dup = ft_calloc(length + 1, sizeof(char));
	if (!dup)
		return (NULL);
	dup = ft_strcpy(dup, src, length);
	return (dup);
}

void *ft_calloc(int nb_elem, int size)
{
	void *mem_zone;

	mem_zone = malloc(nb_elem * size);
	if (!mem_zone)
		return (NULL);
	mem_zone = ft_memset(mem_zone, 0, nb_elem * size);
	return (mem_zone);
}

void *ft_memset(void *ptr, int c, int n)
{
	unsigned char *ptr_c;
	int i;

	ptr_c = (unsigned char *)ptr;
	i = 0;
	while (i < n)
	{
		ptr_c[i] = (unsigned char)c;
		i++;
	}
	return (ptr);
}

void ft_wrstr(int fd, char *str)
{
	write(fd, str, ft_strlen(str));
}

void ft_wrstr_nl(int fd, char *str)
{
	write(fd, str, ft_strlen(str));
	write(fd, "\n", 1);
}

long ft_atoi(char *str)
{
	long result;
	int i;

	result = 0;
	i = 0;
	while (str[i])
	{
		result = result * 10 + str[i] - 48;
		i++;
	}
	return (result);
}
