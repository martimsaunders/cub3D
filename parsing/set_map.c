/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 12:12:51 by mateferr          #+#    #+#             */
/*   Updated: 2025/11/03 17:19:16 by mateferr         ###   ########.fr       */
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

bool	set_player_values(char character, int x, int y)
{
	static int	p_count;

	if (character == 'E')
		pc()->player.angle = PI * 2;
	if (character == 'N')
		pc()->player.angle = PI * 1.5;
	if (character == 'O')
		pc()->player.angle = PI;
	if (character == 'S')
		pc()->player.angle = PI * 0.5;
	pc()->player.x = x + 0.25;
	pc()->player.y = y + 0.25;
	if (++p_count > 1)
		return (err_msg("Player quantity limit exceeded: ", '1'), false);
	return (true);
}

bool	set_characters_values(char character, int x, int y)
{
	if (character == 'e')
	{
		if (pc()->enemy_count >= BONUS_CHAR_LIMIT)
		{
			ft_putstr_fd("Enemies quantity limit exceeded: ", 2);
			ft_putnbr_fd(BONUS_CHAR_LIMIT, 2);
			write(2, "\n", 1);
			return (false);
		}
		pc()->enemies[pc()->enemy_count].x = x + 0.25;
		pc()->enemies[pc()->enemy_count].y = y + 0.25;
		pc()->enemy_count++;
		return (true);
	}
	if (character == 'd')
	{
		// doors position
		// doors limit check
		return (true);
	}
	return (set_player_values(character, x, y));
}

void	set_start_values(void)
{
	int	i;

	pc()->start.player.x = pc()->player.x;
	pc()->start.player.x = pc()->player.x;
	pc()->start.player.angle = pc()->player.angle;
	i = -1;
	while (++i < pc()->enemy_count)
	{
		pc()->start.enemies[i].x = pc()->enemies[i].x;
		pc()->start.enemies[i].y = pc()->enemies[i].y;
	}
	// doors start values
}
