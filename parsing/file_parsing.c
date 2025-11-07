/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 12:11:59 by mateferr          #+#    #+#             */
/*   Updated: 2025/11/06 17:46:51 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_parse	*ps(void)
{
	static t_parse	parse;

	return (&parse);
}

void	free_cpy(char **array)
{
	int	y;

	y = 0;
	while (array[y])
		free(array[y++]);
	free(array);
}

void	err_msg(char *msg, char var)
{
	ft_putstr_fd("Error\n", 2);
	if (msg)
		ft_putstr_fd(msg, 2);
	if (var)
		ft_putchar_fd(var, 2);
	write(2, "\n", 1);
}

bool	map_file_parsing(char *map_name)
{
	int		fd;
	char	*file_type;

	file_type = ft_strrchr(map_name, '.');
	if (!file_type || ft_strncmp(file_type, ".cub", 5))
		return (err_msg("map file is not type .cub", 0), false);
	fd = open(map_name, O_RDONLY);
	if (fd == -1)
		return (ft_putstr_fd("Error\n", 2), perror(map_name), false);
	if (!valid_map_info(fd, map_name))
		return (close(fd), false);
	close(fd);
	if (!valid_map_characters() || !characters_set_value())
		return (false);
	if (!surounded_walls() || !coins_pos())
		return (false);
	pc()->start.player.x = pc()->player.x;
	pc()->start.player.y = pc()->player.y;
	pc()->start.player.angle = pc()->player.angle;
	return (true);
}
