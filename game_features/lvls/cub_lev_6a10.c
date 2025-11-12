/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_lev_6a10.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 17:07:47 by mprazere          #+#    #+#             */
/*   Updated: 2025/11/11 17:21:16 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	set_lvl_10(void)
{
	int	i;

	i = -1;
	while (++i < pc()->enemy_count)
	{
		pc()->enemies[i].direction = 2;
		pc()->enemies[i].speed = 0.25;
		pc()->enemies[i].mov = 1;
		if (i == 5 || i == 6)
		{
			pc()->enemies[i].direction = 0;
			pc()->enemies[i].mov = 0;
		}
	}
	init_player();
	pc()->player.move_speed = 0.1;
}

void	set_lvl_9(void)
{
	int	i;

	i = -1;
	while (++i < pc()->enemy_count)
	{
		pc()->enemies[i].direction = 0;
		pc()->enemies[i].speed = 0.05;
		pc()->enemies[i].mov = 3;
		pc()->enemies[i].number_mov = 20;
	}
	init_player();
}

void	set_lvl_8(void)
{
	int	i;

	i = -1;
	while (++i < pc()->enemy_count)
	{
		if (i == 10 || i == 12 || i == 47 || i == 49)
		{
			pc()->enemies[i].direction = 2;
			pc()->enemies[i].speed = 0.1;
			pc()->enemies[i].mov = 1;
		}
	}
	init_player();
}

void	set_lvl_7(void)
{
	int	i;

	i = -1;
	while (++i < pc()->enemy_count)
	{
		pc()->enemies[i].direction = 0;
		pc()->enemies[i].speed = 0.05;
		pc()->enemies[i].mov = 0;
		if (i == 10 || i == 11 || i == 12 || i == 13)
		{
			pc()->enemies[i].direction = 3;
			pc()->enemies[i].mov = 1;
		}
	}
	init_player();
}

void	set_lvl_6(void)
{
	int	i;

	i = -1;
	while (++i < pc()->enemy_count)
	{
		pc()->enemies[i].direction = 0;
		pc()->enemies[i].speed = 0.05;
		pc()->enemies[i].mov = 3;
		pc()->enemies[i].number_mov = 20;
	}
	init_player();
}
