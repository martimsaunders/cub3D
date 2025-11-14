#include "../../cub3d.h"

bool	minimap_is_edge(int mapx, int mapy, t_minimap *mm)
{
	int	relx;
	int	rely;

	relx = (int)((mm->worldx - floor(mm->worldx)) * BLOCK);
	rely = (int)((mm->worldy - floor(mm->worldy)) * BLOCK);
	if (relx == 0 && (mapx == 0 || !minimap_is_wall(mm, mapx - 1, mapy)))
		return (true);
	if (relx == BLOCK - 1 && (mm->map[mapy][mapx + 1] == '\0'
			|| !minimap_is_wall(mm, mapx + 1, mapy)))
		return (true);
	if (rely == 0 && (mapy == 0 || !minimap_is_wall(mm, mapx, mapy - 1)))
		return (true);
	if (rely == BLOCK - 1)
	{
		if (pc()->map[mapy + 1] == NULL)
			return (true);
		if (mapx < (int)ft_strlen(mm->map[mapy + 1]))
			if (!minimap_is_wall(mm, mapx, mapy + 1))
				return (true);
	}
	return (false);
}

bool	minimap_is_inside_map(t_minimap *mm)
{
	int	map_line_size;

	if (mm->mapy < 0 || mm->mapy >= mm->map_h)
		return (false);
	map_line_size = ft_strlen(mm->map[mm->mapy]);
	if (mm->mapx < 0 || mm->mapx >= map_line_size)
		return (false);
	if (!minimap_is_map(mm))
		return (false);
	return (true);
}

bool	minimap_is_wall(t_minimap *mm, int x, int y)
{
	if (mm->map[y][x] == '1' || mm->map[y][x] == '2')
		return (true);
	return (false);
}

bool	minimap_is_safe(t_minimap *mm)
{
	char	c;

	c = mm->map[mm->mapy][mm->mapx];
	if (c == 'g' || c == 'n' || c == 'p' || c == 's' || c == 'o' || c == 'r'
		|| c == 't' || (pc()->mode != EVAL && c == 'N'))
		return (true);
	return (false);
}

bool	minimap_is_map(t_minimap *mm)
{
	char	m;

	m = mm->map[mm->mapy][mm->mapx];
	if (parse_is_player(m) || parse_is_icon(m) || minimap_is_safe(mm) || m == '1' || m == '0')
		return (true);
	return (false);
}
