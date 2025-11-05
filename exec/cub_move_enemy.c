/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_move_enemy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: praders <praders@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 17:06:19 by praders           #+#    #+#             */
/*   Updated: 2025/11/05 12:39:56 by praders          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	iswall(float newx, float newy, t_sprite *enemy)
{
	float	check;
	int		value;

	check = 0.5 - enemy->speed;
	value = 0;
	if (!is_blocked_e((int)(enemy->y), (int)(newx))
		&& !is_blocked_e((int)(enemy->y + check), (int)(newx))
		&& !is_blocked_e((int)(enemy->y), (int)(newx + check))
		&& !is_blocked_e((int)(enemy->y + check), (int)(newx + check)))
		value++;
	if (!is_blocked_e((int)(newy), (int)(enemy->x))
		&& !is_blocked_e((int)(newy + check), (int)(enemy->x))
		&& !is_blocked_e((int)(newy), (int)(enemy->x + check))
		&& !is_blocked_e((int)(newy + check), (int)(enemy->x + check)))
		value++;
	if (value == 2)
		return (0);
	return (1);
}

void	move_enemy(t_sprite *enemy)
{
	float	next_x;
	float	next_y;

	next_x = enemy->x;
	next_y = enemy->y;
	if (enemy->direction == 0)
		next_x += enemy->speed;
	else if (enemy->direction == 1)
		next_x -= enemy->speed;
	else if (enemy->direction == 2)
		next_y += enemy->speed;
	else if (enemy->direction == 3)
		next_y -= enemy->speed;
	if (iswall(next_x, next_y, enemy))
	{
		if (enemy->direction == 0)
			enemy->direction = 1;
		else if (enemy->direction == 1)
			enemy->direction = 0;
		else if (enemy->direction == 2)
			enemy->direction = 3;
		else if (enemy->direction == 3)
			enemy->direction = 2;
	}
	else
	{
		enemy->x = next_x;
		enemy->y = next_y;
	}
}

void	check_enemy_colision(void)
{
	int i;

	i = 0;
	while (i < pc()->enemy_count)
	{
		distance(&pc()->enemies[i]);
		if (pc()->enemies[i].distance < 0.5)
			return (restart_level());
		i++;
	}
}