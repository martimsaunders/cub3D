/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 13:02:26 by mateferr          #+#    #+#             */
/*   Updated: 2025/11/04 16:46:10 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_game	*pc(void)
{
	static t_game	pc;

	return (&pc);
}

void	reset_level(void)
{
	for (int i = 0; i < pc()->enemy_count; i++)
	{
		pc()->enemies[i].x = pc()->begin.enemiesx[i];
		pc()->enemies[i].y = pc()->begin.enemiesy[i];
	}
	pc()->player.x = pc()->begin.playerx;
	pc()->player.y = pc()->begin.playery;
	pc()->player.angle = pc()->begin.p_angle;
}

void	init_caracters_values(void)
{
	pc()->player.move_speed = 0.025;
	pc()->player.rot_speed = 0.02;
	pc()->player.dir_x = cos(pc()->player.angle);
	pc()->player.dir_y = sin(pc()->player.angle);
	pc()->player.plane_x = -pc()->player.dir_y * 0.66;
	pc()->player.plane_y = pc()->player.dir_x * 0.66;
	pc()->enemy_count = 2;
	pc()->door_count = 1;
	pc()->coin_count = 2;
	for (int i = 0; i < pc()->door_count; i++)
	{
		pc()->door[i].x = 1;
		pc()->door[i].y = 5;
		pc()->door[i].state = 0;
	}
	pc()->enemies[0].x = 8.25;
	pc()->enemies[0].y = 5.25;
	pc()->enemies[1].x = 8.25;
	pc()->enemies[1].y = 6.25;
	pc()->map[5][8] = 'e';
	pc()->map[6][8] = 'e';
	for (int i = 0; i < pc()->coin_count; i++)
	{
		pc()->coin[i].state = 0;
		pc()->coin[i].is_coin = 1;
	}
	pc()->map[5][3] = 'c';
	pc()->map[6][4] = 'c';
	pc()->coin[0].x = 3;
	pc()->coin[0].y = 5;
	pc()->coin[1].x = 4;
	pc()->coin[1].y = 6;
	pc()->map[5][1] = 'd';
	for (int i = 0; i < pc()->enemy_count; i++)
	{
		pc()->enemies[i].speed = 0.02;
		pc()->enemies[i].direction = 0;
		pc()->enemies[i].is_coin = 0;
	}
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (err_msg("1 argument only (./map_path)", NULL), 1);
	if (!map_file_parsing(argv[1]))
		return (1);
	init_game();
	hook_and_loop();
	destroy_everything(1);
	return (0);
}
