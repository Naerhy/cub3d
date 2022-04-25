#include "cub3d.h"

// to delete, for tests only:
#include <string.h>

int main(int argc, char **argv)
{
	t_global global;
	int index_map;

	global.lines = NULL; // call global_init func?
	init_scene(&global.scene);
	if (argc != 2)
		close_program("invalid number of arguments", &global);
	if (ft_strlen(argv[1]) <= 4 ||
			ft_strcmp(".cub", argv[1] + ft_strlen(argv[1]) - 4, 4))
		close_program("invalid filename", &global);
	global.lines = ft_calloc(file_nb_lines(argv[1]) + 1, sizeof(char *));
	if (!global.lines)
		close_program("unable to allocate memory", &global);
	copy_file(argv[1], &global);
	index_map = parse_scene(&global);
	parse_map(&global, index_map);
	// if no error, program closes succesfully
	close_program(NULL, &global);
	return (0);
}
