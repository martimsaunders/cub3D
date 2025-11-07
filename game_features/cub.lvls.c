/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.lvls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 11:58:10 by mprazere          #+#    #+#             */
/*   Updated: 2025/11/07 15:15:38 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_lvl_images(void)
{
	safe_image("assets/roxo.xpm", &pc()->image.wall_n, NULL, 0);
	safe_image("assets/roxo.xpm", &pc()->image.wall_s, NULL, 0);
	safe_image("assets/roxo.xpm", &pc()->image.wall_e, NULL, 0);
	safe_image("assets/roxo.xpm", &pc()->image.wall_o, NULL, 0);
}

void	fill_values()
{
	int x;
	int y;
	char c;

	y = -1;
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

void	set_lvl_1()
{
	int i;

	i = -1;
	while (++i < pc()->enemy_count)
	{
		if (i % 2 == 0)
			pc()->enemies[i].direction = 0;
		else
			pc()->enemies[i].direction = 1;
		pc()->enemies[i].speed = 0.05;
	}
	pc()->player.x = 3.25;
	pc()->player.y = 4.25;
	pc()->player.angle = PI * 0.5;
	pc()->start.player.x = pc()->player.x;
	pc()->start.player.y = pc()->player.y;
	pc()->player.move_speed = 0.025;
	pc()->player.rot_speed = 0.02;
	pc()->player.dir_x = cos(pc()->player.angle);
	pc()->player.dir_y = sin(pc()->player.angle);
	pc()->player.plane_x = -pc()->player.dir_y * 0.66;
	pc()->player.plane_y = pc()->player.dir_x * 0.66;
}

void	lvl_mode_init()
{
	char *lvl_name;
	char *lvl;
	char *temp;
	int fd;

	lvl = ft_itoa(pc()->current_level);
	if (!lvl)
		return (destroy_everything(1));
	temp = ft_strjoin("maps/level", lvl);
	if (!temp)
		return (free(lvl), destroy_everything(1));
	lvl_name = ft_strjoin(temp, ".cub");
	free(temp);
	free(lvl);
	if (!lvl_name)
		return (destroy_everything(1));
	fd = open(lvl_name, O_RDONLY);
	if (fd == -1)
		return (free(lvl_name), destroy_everything(1));
	ft_memset(ps(), 0, sizeof(t_parse));
	ps()->map_start_in_fd = 1;
	free_game_values();
	if (!create_map(fd, lvl_name))
		return (close(fd), destroy_everything(1));
	close (fd);
	init_lvl_images();
	fill_values();
	set_lvl_1();
}

	