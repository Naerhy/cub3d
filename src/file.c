#include "cub3d.h"

// rework function with own GNL
int file_nb_lines(char *filename)
{
	FILE *fp;
	char buffer[1000];
	int nb_lines;

	fp = fopen(filename, "r");
	// check fopen return error
	nb_lines = 0;
	while (fgets(buffer, 1000, fp))
		nb_lines++;
	fclose(fp);
	return (nb_lines);
}

// rework function with own GNL
void copy_file(char *filename, t_global *global)
{
	FILE *fp;
	char buffer[1000];
	int i;

	fp = fopen(filename, "r");
	// check fopen return error
	i = 0;
	while (fgets(buffer, 1000, fp))
	{
		global->lines[i] = ft_strdup(buffer, ft_strlen(buffer));
		// delete this function after => only delete nl character
		replace_nl(global->lines[i]);
		// check ft_strdup return error
		i++;
	}
	fclose(fp);
}

void replace_nl(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			str[i] = '\0';
		i++;
	}
}
