/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_lev_1a5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 17:07:47 by mprazere          #+#    #+#             */
/*   Updated: 2025/11/11 17:22:23 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	set_lvl_5(void)
{
	int	i;

	i = -1;
	while (++i < pc()->enemy_count)
	{
		pc()->enemies[i].direction = 3;
		pc()->enemies[i].speed = 0.05;
		pc()->enemies[i].mov = 2;
	}
	init_player();
}

void	set_lvl_4(void)
{
	int	i;

	i = -1;
	while (++i < pc()->enemy_count)
	{
		if (i % 2 == 0)
			pc()->enemies[i].direction = 2;
		else
			pc()->enemies[i].direction = 3;
		pc()->enemies[i].speed = 0.1;
		pc()->enemies[i].mov = 1;
	}
	init_player();
}

void	set_lvl_3(void)
{
	int	i;

	i = -1;
	while (++i < pc()->enemy_count)
	{
		pc()->enemies[i].direction = 0;
		pc()->enemies[i].speed = 0.1;
		pc()->enemies[i].mov = 2;
	}
	init_player();
}

void	set_lvl_2(void)
{
	int	i;

	i = -1;
	while (++i < pc()->enemy_count)
	{
		pc()->enemies[i].direction = 2;
		pc()->enemies[i].speed = 0.1;
		pc()->enemies[i].mov = 1;
	}
	init_player();
}

void	set_lvl_1(void)
{
	int	i;

	i = -1;
	while (++i < pc()->enemy_count)
	{
		pc()->enemies[i].direction = 1;
		pc()->enemies[i].speed = 0.1;
		pc()->enemies[i].mov = 0;
	}
	init_player();
}
