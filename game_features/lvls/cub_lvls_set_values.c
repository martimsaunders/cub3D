/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lvls_set_values.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 12:12:51 by mateferr          #+#    #+#             */
/*   Updated: 2025/11/11 17:21:29 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

bool	set_coin_value(int x, int y)
{
	static int	c_idx;

	if (!pc()->coin)
	{
		pc()->coin = ft_calloc(pc()->coin_count, sizeof(t_sprite));
		c_idx = 0;
	}
	if (!pc()->coin)
		return (perror("Error\n"), false);
	pc()->coin[c_idx].x = x + 0.25;
	pc()->coin[c_idx].y = y + 0.25;
	pc()->coin[c_idx++].is_coin = 1;
	return (true);
}

bool	set_door_value(int x, int y)
{
	static int	d_idx;

	if (!pc()->door)
	{
		pc()->door = ft_calloc(pc()->door_count, sizeof(t_sprite));
		d_idx = 0;
	}
	if (!pc()->door)
		return (perror("Error\n"), false);
	pc()->door[d_idx].x = x + 0.25;
	pc()->door[d_idx++].y = y + 0.25;
	return (true);
}

bool	set_enemy_value(int x, int y)
{
	static int	e_idx;

	if (!pc()->enemies)
	{
		pc()->enemies = ft_calloc(pc()->enemy_count, sizeof(t_sprite));
		e_idx = 0;
	}
	if (!pc()->enemies)
		return (perror("Error\n"), false);
	pc()->enemies[e_idx].x = x + 0.25;
	pc()->enemies[e_idx++].y = y + 0.25;
	return (true);
}

bool	set_elements_values(char c, int x, int y)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'O')
	{
		if (c == 'E')
			pc()->player.angle = PI * 2;
		if (c == 'N')
			pc()->player.angle = PI * 1.5;
		if (c == 'O')
			pc()->player.angle = PI;
		if (c == 'S')
			pc()->player.angle = PI * 0.5;
		pc()->player.x = x + 0.25;
		pc()->player.y = y + 0.25;
	}
	else if (c == 'e' && !set_enemy_value(x, y))
		return (false);
	else if (c == 'd' && !set_door_value(x, y))
		return (false);
	else if (c == 'c' && !set_coin_value(x, y))
		return (false);
	return (true);
}

bool	characters_count(char chr)
{
	if (chr == 'e')
		pc()->enemy_count++;
	else if (chr == 'd')
		pc()->door_count++;
	else if (chr == 'c')
		pc()->coin_count++;
	return (true);
}
