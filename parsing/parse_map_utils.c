#include "../cub3d.h"

bool	parse_is_player(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (true);
	return (false);
}

bool	parse_is_icon(char c)
{
	if (c == 'd' || c == 'e' || c == 'c')
		return (true);
	return (false);
}

bool	parse_is_map(char c)
{
	if (parse_is_space(c) || c == '\n' || parse_is_player(c) || (BONUS
			&& parse_is_icon(c)) || c == '0' || c == '1')
		return (true);
	return (false);
}

bool	parse_out_of_bounds(char **map, int x, int y)
{
	int	line_len;

	if (y < 0 || map[y] == NULL)
		return (true);
	line_len = (int)ft_strlen(map[y]);
	if (x < 0 || x > line_len)
		return (true);
	if (parse_is_space(map[y][x]) || map[y][x] == '\n' || map[y][x] == '\0')
		return (true);
	return (false);
}
