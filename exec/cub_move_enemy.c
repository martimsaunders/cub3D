/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_move_enemy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 17:06:19 by praders           #+#    #+#             */
/*   Updated: 2025/11/11 16:48:47 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	iswall(float newx, float newy, t_sprite *enemy)
{
	float	check;
	int		value;

	check = 0.75 - enemy->speed;
	value = 0;
	if (!is_blocked_e((int)(enemy->y), (int)(newx), 0)
		&& !is_blocked_e((int)(enemy->y + check), (int)(newx), 0)
		&& !is_blocked_e((int)(enemy->y), (int)(newx + check), 0)
		&& !is_blocked_e((int)(enemy->y + check), (int)(newx + check), 0))
		value++;
	if (!is_blocked_e((int)(newy), (int)(enemy->x), 0)
		&& !is_blocked_e((int)(newy + check), (int)(enemy->x), 0)
		&& !is_blocked_e((int)(newy), (int)(enemy->x + check), 0)
		&& !is_blocked_e((int)(newy + check), (int)(enemy->x + check), 0))
		value++;
	if (value == 2)
		return (0);
	return (1);
}

static void	move_enemy2(t_sprite *enemy)
{
	if (enemy->mov == 0)
	{
		if (enemy->direction == 0)
			enemy->direction = 1;
		else if (enemy->direction == 1)
			enemy->direction = 0;
	}
	else if (enemy->mov == 1)
	{
		if (enemy->direction == 2)
			enemy->direction = 3;
		else if (enemy->direction == 3)
			enemy->direction = 2;
	}
	else if (enemy->mov == 2)
	{
		if (enemy->direction == 0)
			enemy->direction = 2;
		else if (enemy->direction == 1)
			enemy->direction = 3;
		else if (enemy->direction == 2)
			enemy->direction = 1;
		else if (enemy->direction == 3)
			enemy->direction = 0;
	}
}

static void	move_enemy3(t_sprite *enemy)
{
	if (enemy->mov == 3)
	{
		enemy->mov_count++;
		if (enemy->number_mov == enemy->mov_count)
		{
			if (enemy->direction == 0)
				enemy->direction = 2;
			else if (enemy->direction == 1)
				enemy->direction = 3;
			else if (enemy->direction == 2)
				enemy->direction = 1;
			else if (enemy->direction == 3)
				enemy->direction = 0;
			enemy->mov_count = 0;
		}
	}
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
		move_enemy2(enemy);
	else
	{
		enemy->x = next_x;
		enemy->y = next_y;
	}
	move_enemy3(enemy);
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