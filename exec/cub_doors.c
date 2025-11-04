/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_doors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 16:26:47 by praders           #+#    #+#             */
/*   Updated: 2025/11/04 16:10:53 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	distance_door(t_door *door)
{
	float	dx;
	float	dy;
	
	dx = door->x - pc()->player.x;
	dy = door->y - pc()->player.y;
	door->distance = sqrt(dx * dx + dy * dy);
	return;
}

void interact_door(void)
{
	int i;

	i = 0;
	while (i < pc()->door_count)
	{
		distance_door(&pc()->door[i]);
		if (pc()->door[i].distance <= 2 && pc()->coin_captured == pc()->coin_count)
		{
			if (pc()->door[i].state == 0)
				pc()->door[i].state = 1;
			return;
		}
		else if (pc()->door[i].distance > 2 && pc()->coin_captured == pc()->coin_count)
		{
			if (pc()->door[i].state == 1)
				pc()->door[i].state = 0;
			return;
		}
		i++;
	}
}

int	find_door_index(int x, int y)
{
	int i;

	i = 0;
	while (i < pc()->door_count)
	{
		if (pc()->door[i].x == x && pc()->door[i].y == y)
			return (i);
		i++;
	}
	return (-1);
}

int		is_door_closed(int map_y, int map_x)
{
	int i;

	i = 0;
	while (i < pc()->door_count)
	{
		if (pc()->door[i].x == map_x && pc()->door[i].y == map_y)
		{
			if (pc()->door[i].state == 0)
				return (1);
			return (0);
		}
		i++;
	}
	return (0);
}
