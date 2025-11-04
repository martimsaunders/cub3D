/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 19:31:57 by mateferr          #+#    #+#             */
/*   Updated: 2025/11/04 19:46:56 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	check_door_pos(char chr, int x, int y)
{
	int	safe_x;
	int	safe_y;

	safe_x = 0;
	safe_y = 0;
	if (chr != 'd')
		return (true);
	if (x > 0 && x < (int)ft_strlen(pc()->map[y]))
		safe_x = 1;
	if (y > 0 && pc()->map[y] != NULL && x < (int)ft_strlen(pc()->map[y - 1])
		&& x < (int)ft_strlen(pc()->map[y + 1]))
		safe_y = 1;
	if (safe_x && pc()->map[y][x + 1] == '1' && pc()->map[y][x - 1] == '1')
		return (true);
	if (safe_y && pc()->map[y + 1][x] == '1' && pc()->map[y - 1][x] == '1')
		return (true);
	return (err_msg("Door not between walls", 0), false);
}

static bool	flood_fill_coin(char **map, int x, int y)
{
	static int	coin;

	if (map[y][x] == '1' || map[y][x] == 'd')
		return (true);
	if (map[y][x] == 'c')
		coin++;
	map[y][x] = '1';
	flood_fill_coin(map, x + 1, y);
	flood_fill_coin(map, x - 1, y);
	flood_fill_coin(map, x, y + 1);
	flood_fill_coin(map, x, y - 1);
	if (coin == pc()->coin_count)
		return (true);
	return (false);
}

bool	coins_pos(void)
{
	char	**map_copy;

	if (pc()->coin_count == 0)
	{
		return (true);
	}
	map_copy = copy_matrix(pc()->map, ps()->map_h);
	if (!map_copy)
		return (perror("Error\n"), false);
	map_copy[(int)pc()->player.y][(int)pc()->player.x] = '0';
	if (!flood_fill_coin(map_copy, pc()->player.x, pc()->player.y))
		return (err_msg("Coins not well set", 0), free_cpy(map_copy), false);
	free_cpy(map_copy);
	return (true);
}
