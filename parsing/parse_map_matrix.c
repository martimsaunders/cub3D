#include "../cub3d.h"

void	parse_free_array(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

int	parse_map_height(char **map)
{
	int	i;
	int	size;

	size = 0;
	i = -1;
	while (map[++i])
		size++;
	return (size);
}

bool	parse_map_matrix(t_parse *f)
{
	int	i;
	int	j;
	int	k;

	f->line_count = parse_map_height(&f->file[f->map_idx]);
	if (f->line_count < 3)
		return (err_msg("Invalid map height", 0), false);
	f->map = ft_calloc(f->line_count + 1, sizeof(char *));
	if (!f->map)
		return (perror("Error\n"), false);
	i = f->map_idx - 1;
	j = 0;
	while (f->file[++i])
	{
		k = -1;
		while (f->file[i][++k])
			if (!parse_is_map(f->file[i][k]))
				return (err_msg("Invalid map char: ", f->file[i][k]), false);
		f->map[j] = ft_strdup(f->file[i]);
		if (!f->map[j++])
			return (perror("Error\n"), false);
	}
	f->map[j] = NULL;
	return (true);
}

char	**parse_copy_matrix(char **src)
{
	char	**copy;
	int		y;
	int		size;

	size = 0;
	y = -1;
	while (src[++y])
		size++;
	copy = ft_calloc(size + 1, sizeof(char *));
	if (!copy)
		return (perror("Error\n"), NULL);
	y = -1;
	while (src[++y])
	{
		copy[y] = ft_strdup(src[y]);
		if (!copy[y])
			return (perror("Error\n"), parse_free_array(copy), NULL);
	}
	copy[y] = NULL;
	return (copy);
}

bool	parse_find_player(t_parse *f, int *px, int *py)
{
	int	x;
	int	y;

	y = -1;
	while (f->map[++y])
	{
		x = -1;
		while (f->map[y][++x])
		{
			if (parse_is_player(f->map[y][x]))
			{
				*px = x;
				*py = y;
				return (true);
			}
		}
	}
	return (false);
}
