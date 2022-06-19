#include "cub3d.h"

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
