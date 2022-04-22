#include "cub3d.h"

// to delete, for tests only:
#include <string.h>

int main(int argc, char **argv)
{
	t_global global;

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
	// don't forget to reove newline character from file lines
	// don't forget to reove newline character from file lines
	copy_file(argv[1], &global);

	parse_scene(&global);

	// for testing purposes:
	printf("tex_NO: %s | tex_SO: %s | tex_EA: %s | tex_WE: %s | color_F: %d | color_C: %d\n",
			global.scene.tex_north, global.scene.tex_south, global.scene.tex_east,
			global.scene.tex_west, global.scene.color_floor, global.scene.color_ceiling);

	// if no error, program closes succesfully
	close_program(NULL, &global);
	return (0);
}
