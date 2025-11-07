/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 12:12:51 by mateferr          #+#    #+#             */
/*   Updated: 2025/11/06 18:15:17 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	fill_map(int fd, char *map_name)
{
	char	*line;
	int		i;

	line = NULL;
	close(fd);
	fd = open(map_name, O_RDONLY);
	while (ps()->map_start_in_fd--)
	{
		line = get_next_line(fd);
		if (ps()->map_start_in_fd)
			free(line);
	}
	i = 0;
	while (line)
	{
		pc()->map[i] = ft_strdup(line);
		free(line);
		if (!pc()->map[i++])
			return (perror("Error\n"), false);
		line = get_next_line(fd);
	}
	pc()->map[i] = NULL;
	return (true);
}

bool	create_map(int fd, char *map_name)
{
	char	*line;

	ps()->map_h = 1;
	line = get_next_line(fd);
	while (line)
	{
		ps()->map_h++;
		free(line);
		line = get_next_line(fd);
	}
	if (ps()->map_h < 3)
		return (err_msg("Invalid map height", 0), false);
	pc()->map = ft_calloc(ps()->map_h + 1, sizeof(char *));
	if (!pc()->map)
		return (perror("Error\n"), false);
	return (fill_map(fd, map_name));
}

bool	set_coin_value(int x, int y)
{
	static int	c_idx;

	if (!pc()->coin)
	{
		pc()->coin = ft_calloc(pc()->coin_count, sizeof(t_sprite));
		c_idx = 0;
	}
	if (!pc()->coin)
		return (perror("Error\n"), false);
	pc()->coin[c_idx].x = x + 0.25;
	pc()->coin[c_idx].y = y + 0.25;
	pc()->coin[c_idx++].is_coin = 1;
	return (true);
}

bool	set_door_value(int x, int y)
{
	static int	d_idx;

	if (!pc()->door)
	{
		pc()->door = ft_calloc(pc()->door_count, sizeof(t_sprite));
		d_idx = 0;
	}
	if (!pc()->door)
		return (perror("Error\n"), false);
	pc()->door[d_idx].x = x + 0.25;
	pc()->door[d_idx++].y = y + 0.25;
	return (true);
}

bool	set_enemy_value(int x, int y)
{
	static int	e_idx;

	if (!pc()->enemies)
	{
		pc()->enemies = ft_calloc(pc()->enemy_count, sizeof(t_sprite));
		e_idx = 0;
	}
	if (!pc()->enemies)
		return (perror("Error\n"), false);
	pc()->enemies[e_idx].x = x + 0.25;
	pc()->enemies[e_idx++].y = y + 0.25;
	return (true);
}

bool	set_elements_values(char c, int x, int y)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'O')
	{
		if (c == 'E')
			pc()->player.angle = PI * 2;
		if (c == 'N')
			pc()->player.angle = PI * 1.5;
		if (c == 'O')
			pc()->player.angle = PI;
		if (c == 'S')
			pc()->player.angle = PI * 0.5;
		pc()->player.x = x + 0.25;
		pc()->player.y = y + 0.25;
	}
	else if (c == 'e' && !set_enemy_value(x, y))
		return (false);
	else if (c == 'd' && !set_door_value(x, y))
		return (false);
	else if (c == 'c' && !set_coin_value(x, y))
		return (false);
	return (true);
}

bool	characters_count(char chr)
{
	if (chr == 'e')
		pc()->enemy_count++;
	else if (chr == 'd')
		pc()->door_count++;
	else if (chr == 'c')
		pc()->coin_count++;
	else if (chr == 'E' || chr == 'O' || chr == 'S' || chr == 'N')
		if (++ps()->p_count > 1)
			return (err_msg("Player quantity limit exceeded: ", '1'), false);
	return (true);
}
