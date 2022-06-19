#include "cub3d.h"

int file_nb_lines(char *filename)
{
	int fd;
	char *line;
	int gnl_return;
	int nb_lines;

	gnl_return = 1;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (-1);
	nb_lines = 0;
	while (gnl_return == 1)
	{
		gnl_return = get_next_line(fd, &line);
		if (gnl_return == -1)
			return (-1);
		if (gnl_return)
			nb_lines++;
		free(line);
	}
	close(fd);
	return (nb_lines);
}

void copy_file(char *filename, t_global *global)
{
	int fd;
	char *line;
	int gnl_return;
	int i;

	gnl_return = 1;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		close_program("unable to open the file", global);
	i = 0;
	while (gnl_return == 1)
	{
		gnl_return = get_next_line(fd, &line);
		if (gnl_return == -1)
			close_program("unable to allocate GNL", global);
		if (gnl_return)
			global->lines[i] = ft_strdup(line, ft_strlen(line));
		i++;
		free(line);
	}
	close(fd);
}
