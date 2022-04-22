#include "cub3d.h"

char **ft_split(char *str, char delimiter)
{
	char **split;
	int nb_words;

	nb_words = get_nb_words(str, delimiter);
	if (!nb_words)
		return (NULL);
	split = ft_calloc(nb_words + 1, sizeof(char *));
	if (!split)
		return (NULL);
	split = split_words(split, str, delimiter);
	if (!split)
		return (NULL);
	split[nb_words] = NULL;
	return (split);
}

int get_nb_words(char *str, char delimiter)
{
	int nb_words;
	int i;

	nb_words = 0;
	if (str[0] && str[0] != delimiter)
		nb_words++;
	i = 0;
	while (str[i])
	{
		if ((str[i] == delimiter) && (str[i + 1] && str[i + 1] != delimiter))
			nb_words++;
		i++;
	}
	return (nb_words);
}

char **split_words(char **split, char *str, char delimiter)
{
	int i;
	int j;
	int nb_char;

	i = 0;
	j = 0;
	while (str[i])
	{
		nb_char = get_nb_char(&str[i], delimiter);
		if (nb_char)
		{
			split[j] = ft_calloc(nb_char + 1, sizeof(char));
			if (!split[j])
			{
				free_double_ptr((void **)split);
				return (NULL);
			}
			split[j] = ft_strcpy(split[j], &str[i], nb_char);
			i += nb_char;
			j++;
		}
		else
			i++;
	}
	return (split);
}

int get_nb_char(char *str, char delimiter)
{
	int nb_char;
	int i;

	nb_char = 0;
	i = 0;
	while (str[i] && str[i] != delimiter)
	{
		nb_char++;
		i++;
	}
	return (nb_char);
}
