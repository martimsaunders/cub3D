/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: praders <praders@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 12:12:51 by mateferr          #+#    #+#             */
/*   Updated: 2025/11/05 12:01:51 by praders          ###   ########.fr       */
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

void	val_err_msg(char *msg)
{
	ft_putstr_fd(msg, 2);
	ft_putnbr_fd(B_CHR_LIM, 2);
	write(2, "\n", 1);
}

bool	set_elements_values(char character, int x, int y)
{
	if (character == 'e')
	{
		if (pc()->enemy_count >= B_CHR_LIM)
			return (val_err_msg("Enemies quantity limit exceeded: "), false);
		pc()->enemies[pc()->enemy_count].x = x + 0.25;
		pc()->enemies[pc()->enemy_count].y = y + 0.25;
		pc()->enemy_count++;
	}
	else if (character == 'd')
	{
		if (pc()->door_count >= B_CHR_LIM)
			return (val_err_msg("Doors quantity limit exceeded: "), false);
		pc()->door[pc()->door_count].x = x + 0.25;
		pc()->door[pc()->door_count].y = y + 0.25;
		pc()->door_count++;
	}
	else if (character == 'c')
	{
		if (pc()->coin_count >= B_CHR_LIM)
			return (val_err_msg("Coins quantity limit exceeded: "), false);
		pc()->coin[pc()->coin_count].x = x + 0.25;
		pc()->coin[pc()->coin_count].y = y + 0.25;
		pc()->coin[pc()->coin_count].is_coin = 1;
		pc()->coin_count++;
	}
	return (true);
}

bool	set_characters_values(char chr, int x, int y)
{
	static int	p_count;

	if (!set_elements_values(chr, x, y))
		return (false);
	if (chr == 'E' || chr == 'O' || chr == 'S' || chr == 'N')
	{
		if (chr == 'E')
			pc()->player.angle = PI * 2;
		if (chr == 'N')
			pc()->player.angle = PI * 1.5;
		if (chr == 'O')
			pc()->player.angle = PI;
		if (chr == 'S')
			pc()->player.angle = PI * 0.5;
		pc()->player.x = x + 0.25;
		pc()->player.y = y + 0.25;
		if (++p_count > 1)
			return (err_msg("Player quantity limit exceeded: ", '1'), false);
	}
	return (true);
}
