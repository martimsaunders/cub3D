/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.lvls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:54:22 by mateferr          #+#    #+#             */
/*   Updated: 2025/11/07 16:54:24 by mateferr         ###   ########.fr       */
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

void	set_lvl_2()
{
	int i;

	i = -1;
	while (++i < pc()->enemy_count)
	{
		if (i % 2 == 0)
			pc()->enemies[i].direction = 2;
		else
			pc()->enemies[i].direction = 3;
		pc()->enemies[i].speed = 0.125;
	}
	pc()->image.ceiling = 0xCA1568;
	pc()->image.floor = 0x796446;
	pc()->player.x = 3.25;
	pc()->player.y = 4.25;
	pc()->player.move_speed = 0.1;
	pc()->player.rot_speed = 0.02;
	pc()->player.angle = PI * 0.5;
	pc()->player.dir_x = cos(pc()->player.angle);
	pc()->player.dir_y = sin(pc()->player.angle);
	pc()->player.plane_x = -pc()->player.dir_y * 0.66;
	pc()->player.plane_y = pc()->player.dir_x * 0.66;
	pc()->start.player.x = pc()->player.x;
	pc()->start.player.y = pc()->player.y;
}

void	set_lvl_1()
{
	int i;

	i = -1;
	while (++i < pc()->enemy_count)
	{
		if (i % 2 == 0)
			pc()->enemies[i].direction = 3;
		else
			pc()->enemies[i].direction = 4;
		pc()->enemies[i].speed = 0.1;
	}
	pc()->image.ceiling = 0xCA1568;
	pc()->image.floor = 0x796446;
	pc()->player.x = 3.25;
	pc()->player.y = 4.25;
	pc()->player.move_speed = 0.1;
	pc()->player.rot_speed = 0.02;
	pc()->player.angle = PI * 0.5;
	pc()->player.dir_x = cos(pc()->player.angle);
	pc()->player.dir_y = sin(pc()->player.angle);
	pc()->player.plane_x = -pc()->player.dir_y * 0.66;
	pc()->player.plane_y = pc()->player.dir_x * 0.66;
	pc()->start.player.x = pc()->player.x;
	pc()->start.player.y = pc()->player.y;
	pc()->player.move_speed = 0.025;
	pc()->player.rot_speed = 0.02;
	pc()->player.dir_x = cos(pc()->player.angle);
	pc()->player.dir_y = sin(pc()->player.angle);
	pc()->player.plane_x = -pc()->player.dir_y * 0.66;
	pc()->player.plane_y = pc()->player.dir_x * 0.66;
}

char **file_matrix_fill(const char *filepath, char **matrix)
{
    int fd;
    char *line;
    int i;

    fd = open(filepath, O_RDONLY);
    if (fd == -1)
        return (perror("Error\n"), NULL);
    i = 0;
    while (1)
    {
        line = get_next_line(fd);
        if (!line)
            break ;
        matrix[i] = ft_strdup(line);
        if (!matrix[i++])
            return (perror("Error\n"), close(fd), NULL);
    }
    matrix[i] = NULL;
    close(fd);
    return (matrix);
}

char **file_matrix_load(const char *filepath)
{
    int fd;
    char *line;
	int line_count;
	char **matrix;

	line_count = 0;
    fd = open(filepath, O_RDONLY);
    if (fd == -1)
        return (perror("Error\n"), NULL);
    while (1)
    {
        line = get_next_line(fd);
        if (!line)
            break ;
        line_count++;
    }
    matrix = ft_calloc(line_count + 1, sizeof(char *));
    if (!matrix)
        return (perror("Error\n"), close(fd), NULL);
    close(fd);
    return (file_matrix_fill(filepath, matrix));
}

void	lvl_mode_init()
{
	char *lvl_name;
	char *lvl;
	char *temp;

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
	free_game_values();
	pc()->map = file_matrix_load(lvl_name);
	free(lvl_name);
	if (!pc()->map)
		destroy_everything(1);
	init_lvl_images();
	fill_values();
	if (pc()->current_level == 1)
		set_lvl_1();
	if (pc()->current_level == 2)
		set_lvl_2();
}

	