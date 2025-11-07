/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:03:34 by mateferr          #+#    #+#             */
/*   Updated: 2025/11/06 18:37:40 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	valid_map_characters(void)
{
	int		y;
	int		x;
	char	c;

	y = -1;
	while (pc()->map[++y])
	{
		x = -1;
		while (pc()->map[y][++x])
		{
			c = pc()->map[y][x];
			if (c != ' ' && c != '\t' && c != '1' && c != '0' && c != '\n'
				&& c != 'N' && c != 'S' && c != 'E' && c != 'O' && !(ps()->bonus
					&& (c == 'e' || c == 'd' || c == 'c')))
			{
				return (err_msg("Invalid map character: ", pc()->map[y][x]),
					false);
			}
			else if (!characters_count(c) || !check_door_pos(c, x, y))
				return (false);
		}
	}
	return (true);
}

bool	characters_set_value(void)
{
	int		y;
	int		x;
	char	c;

	y = -1;
	while (pc()->map[++y])
	{
		x = -1;
		while (pc()->map[y][++x])
		{
			c = pc()->map[y][x];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'O' || c == 'e'
				|| c == 'd' || c == 'c')
			{
				if (!set_elements_values(c, x, y))
					return (false);
			}
		}
	}
	return (true);
}

bool	flood_fill_map(char **map, int x, int y) // print flood fill
{
	if (ps()->ff_ret)
		return (false);
	if (map[y][x] == '1')
		return (true);
	if (map[y][x] != '0')
	{
		if (!(ps()->bonus && (map[y][x] == 'e' || map[y][x] == 'd'
					|| map[y][x] == 'c')))
		{
			ps()->ff_ret = 1;
			return (false);
		}
	}
	map[y][x] = '1';
	flood_fill_map(map, x + 1, y);
	flood_fill_map(map, x - 1, y);
	flood_fill_map(map, x, y + 1);
	flood_fill_map(map, x, y - 1);
	if (ps()->ff_ret)
		return (false);
	return (true);
}

char	**copy_matrix(char **src, int size)
{
	char	**copy;
	int		y;

	copy = ft_calloc(size + 1, sizeof(char *));
	if (!copy)
		return (NULL);
	y = 0;
	while (src[y])
	{
		copy[y] = ft_strdup(src[y]);
		if (!copy[y])
			return (NULL);
		y++;
	}
	copy[y] = NULL;
	return (copy);
}

bool	surounded_walls(void)
{
	char	**map_copy;
	int		y;
	int		x;

	map_copy = copy_matrix(pc()->map, ps()->map_h);
	if (!map_copy)
		return (perror("Error\n"), false);
	map_copy[(int)pc()->player.y][(int)pc()->player.x] = '0';
	if (!flood_fill_map(map_copy, pc()->player.x, pc()->player.y))
		return (err_msg("Map not surounded by walls 1", 0), free_cpy(map_copy),
			false);
	y = -1;
	while (map_copy[++y])
	{
		x = 0;
		while (map_copy[y][x])
		{
			if (map_copy[y][x++] == '0')
				if (!flood_fill_map(map_copy, x - 1, y))
					return (err_msg("Map not surounded by walls 2", 0),
						free_cpy(map_copy), false);
		}
	}
	free_cpy(map_copy);
	return (true);
}
