/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flood_fill.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 13:36:01 by mateferr          #+#    #+#             */
/*   Updated: 2025/11/24 12:05:29 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	parse_flood_fill_check_icons(t_parse *f, int x, int y)
{
	if (f->map_cpy[y][x] == 'e')
		f->enemy_count++;
	else if (f->map_cpy[y][x] == 'c')
		f->coin_count++;
	else if (f->map_cpy[y][x] == 'd')
	{
		if (parse_out_of_bounds(f->map, x - 1, y) || parse_out_of_bounds(f->map,
				x + 1, y) || parse_out_of_bounds(f->map, x, y - 1)
			|| parse_out_of_bounds(f->map, x, y + 1))
			return (err_msg("Door not between walls", 0), false);
		if ((f->map[y][x - 1] == '1' && f->map[y][x + 1] != '1') ||
		(f->map[y - 1][x] == '1' && f->map[y + 1][x] != '1'))
			return (err_msg("Door not between walls", 0), false);
		f->door_count++;
	}
	return (true);
}

bool	parse_map_flood_fill(t_parse *f, int x, int y)
{
	if (parse_out_of_bounds(f->map_cpy, x, y))
		return (err_msg("Map not surounded by walls", 0), false);
	if (f->map_cpy[y][x] == '1')
		return (true);
	if (parse_is_player(f->map_cpy[y][x]))
		return (err_msg("Extra player detected", 0), false);
	if (BONUS && parse_is_icon(f->map_cpy[y][x]))
	{
		if (!parse_flood_fill_check_icons(f, x, y))
			return (false);
	}
	f->map_cpy[y][x] = '1';
	if (!parse_map_flood_fill(f, x + 1, y))
		return (false);
	if (!parse_map_flood_fill(f, x - 1, y))
		return (false);
	if (!parse_map_flood_fill(f, x, y + 1))
		return (false);
	if (!parse_map_flood_fill(f, x, y - 1))
		return (false);
	return (true);
}

bool	parse_coin_flood_fill(t_parse *f, int x, int y)
{
	if (f->map_cpy[y][x] == '1' || f->map_cpy[y][x] == 'd')
		return (true);
	if (f->map_cpy[y][x] == 'c')
		f->coin_check++;
	f->map_cpy[y][x] = '1';
	parse_coin_flood_fill(f, x + 1, y);
	parse_coin_flood_fill(f, x - 1, y);
	parse_coin_flood_fill(f, x, y + 1);
	parse_coin_flood_fill(f, x, y - 1);
	if (f->coin_check != f->coin_count)
		return (false);
	return (true);
}

bool	parse_validate_coins_pos(t_parse *f)
{
	int	x;
	int	y;

	if (!BONUS)
		return (true);
	f->map_cpy = parse_copy_matrix(f->map);
	if (!f->map_cpy)
		return (false);
	parse_find_player(f, &x, &y);
	f->map_cpy[y][x] = '0';
	if (!parse_coin_flood_fill(f, x, y))
		return (err_msg("Coins not well set", 0), parse_free_array(f->map_cpy),
			false);
	parse_free_array(f->map_cpy);
	return (true);
}

bool	parse_flood_fill_extra_checks(t_parse *f)
{
	int		x;
	int		y;
	char	c;

	y = -1;
	while (f->map_cpy[++y])
	{
		x = -1;
		while (f->map_cpy[y][++x])
		{
			c = f->map_cpy[y][x];
			if (c == '0' || parse_is_player(c) || (BONUS && parse_is_icon(c)))
				if (!parse_map_flood_fill(f, x, y))
					return (false);
		}
	}
	return (true);
}
