/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: praders <praders@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 12:10:34 by praders           #+#    #+#             */
/*   Updated: 2025/10/31 17:32:00 by praders          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_game	*pc(void)
{
	static t_game	pc;

	return (&pc);
}

void	init_player_map(void)
{
	pc()->map = malloc(sizeof(char *) * 11);
	pc()->map[0] = "1111111111";
	pc()->map[1] = "1E00000001";
	pc()->map[2] = "1011000001";
	pc()->map[3] = "1010001001";
	pc()->map[4] = "1E00001001";
	pc()->map[5] = "1000011001";
	pc()->map[6] = "1EP0000001";
	pc()->map[7] = "1000001101";
	pc()->map[8] = "1000000001";
	pc()->map[9] = "1111111111";
	pc()->map[10] = NULL;
	find_player();
	pc()->player.move_speed = 0.02;
	pc()->player.rot_speed = 0.02;
	pc()->player.angle = PI;
	pc()->player.dir_x = cos(pc()->player.angle);
	pc()->player.dir_y = sin(pc()->player.angle);
	pc()->player.plane_x = -pc()->player.dir_y * 0.66;
	pc()->player.plane_y = pc()->player.dir_x * 0.66;
	pc()->image.floor = 0xFF0000;
	pc()->image.ceiling = 0x00FF00;
	pc()->enemy_count = 3;
	for (int i = 0; i < pc()->enemy_count; i++)
	{
		pc()->enemies[i].speed = 0.02;
		pc()->enemies[i].direction = 1;
	}
}

void	find_player(void)
{
	int	x;
	int	y;
	int j;

	y = -1;
	j = 0;
	while (pc()->map[++y])
	{
		x = -1;
		while (pc()->map[y][++x])
		{
			if (pc()->map[y][x] == 'P')
			{
				pc()->player.x = x + 0.25;
				pc()->player.y = y + 0.25;
				return ;
			}
			else if (pc()->map[y][x] == 'E')
			{
				pc()->enemies[j].x = x + 0.25;
				pc()->enemies[j++].y = y + 0.25;
			}
		}
	}
}

int	main(void)
{
	init_game();
	hook_and_loop();
	destroy_everything(1);
	return (0);
}
