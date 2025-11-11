/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_lvls_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 17:13:13 by mprazere          #+#    #+#             */
/*   Updated: 2025/11/11 18:00:40 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	init_lvl_images(void)
{
	safe_image("assets/roxo.xpm", &pc()->image.wall_n, NULL, 0);
	safe_image("assets/roxo.xpm", &pc()->image.wall_s, NULL, 0);
	safe_image("assets/roxo.xpm", &pc()->image.wall_e, NULL, 0);
	safe_image("assets/roxo.xpm", &pc()->image.wall_o, NULL, 0);
}

void	fill_values(int x, int y)
{
	char	c;

	while (pc()->map[++y])
	{
		x = -1;
		while (pc()->map[y][++x])
		{
			c = pc()->map[y][x];
			characters_count(c);
		}
	}
	y = -1;
	while (pc()->map[++y])
	{
		x = -1;
		while (pc()->map[y][++x])
		{
			c = pc()->map[y][x];
			if (c != '0' && c != '1')
				if (!set_elements_values(c, x, y))
					destroy_everything(1);
		}
	}
}

int	is_player(int y, int x)
{
	if (pc()->map[y][x] == 's')
		return (pc()->player.angle = PI * 0.5, 1);
	else if (pc()->map[y][x] == 'o')
		return (pc()->player.angle = PI, 1);
	else if (pc()->map[y][x] == 't')
		return (pc()->player.angle = PI * 2, 1);
	else if (pc()->map[y][x] == 'r')
		return (pc()->player.angle = PI * 1.5, 1);
	return (0);
}

void	find_player(void)
{
	int	x;
	int	y;

	y = -1;
	while (pc()->map[++y])
	{
		x = -1;
		while (pc()->map[y][++x])
		{
			if (is_player(y, x))
			{
				pc()->player.x = x + 0.25;
				pc()->player.y = y + 0.25;
			}
		}
	}
}

void	init_player(void)
{
	find_player();
	pc()->image.ceiling = 0xCA1568;
	pc()->image.floor = 0x796446;
	pc()->player.move_speed = 0.05;
	pc()->player.rot_speed = 0.05;
	pc()->player.dir_x = cos(pc()->player.angle);
	pc()->player.dir_y = sin(pc()->player.angle);
	pc()->player.plane_x = -pc()->player.dir_y * FOV;
	pc()->player.plane_y = pc()->player.dir_x * FOV;
	pc()->start.player.x = pc()->player.x;
	pc()->start.player.y = pc()->player.y;
	pc()->start.player.angle = pc()->player.angle;
}
