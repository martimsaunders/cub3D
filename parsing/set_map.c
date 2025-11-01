#include "../cub3d.h"

bool	fill_map(int fd, char *map_name)
{
	char	*line;
	int		i;

	line = NULL;
	close(fd);
	fd = open(map_name, O_RDONLY);
	while (ps()->map_start_in_fd--)
	{
		line = get_next_line(fd);
		if (ps()->map_start_in_fd)
			free(line);
	}
	i = 0;
	while (line)
	{
		pc()->map[i] = ft_strdup(line);
		free(line);
		if (!pc()->map[i++])
			return (perror("Error\n"), false);
		line = get_next_line(fd);
	}
	pc()->map[i] = NULL;
	return (true);
}

bool	create_map(int fd, char *map_name)
{
	char	*line;

	ps()->map_h = 1;
	line = get_next_line(fd);
	while (line)
	{
		ps()->map_h++;
		free(line);
		line = get_next_line(fd);
	}
	if (ps()->map_h < 3)
		return (err_msg("Invalid map height", NULL), false);
	pc()->map = ft_calloc(ps()->map_h + 1, sizeof(char *));
	if (!pc()->map)
		return (perror("Error\n"), false);
	return (fill_map(fd, map_name));
}

void	player_set(char orientation, int x, int y)
{
	if (orientation == 'E')
		pc()->player.angle = PI * 2;
	if (orientation == 'N')
		pc()->player.angle = PI * 1.5;
	if (orientation == 'O')
		pc()->player.angle = PI;
	if (orientation == 'S')
		pc()->player.angle = PI * 0.5;
	pc()->player.x = x;
	pc()->player.y = y;
}
