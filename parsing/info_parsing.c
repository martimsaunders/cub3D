/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 12:12:15 by mateferr          #+#    #+#             */
/*   Updated: 2025/11/03 16:56:14 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	find_tex_info(char *line)
{
	if (*line == 'N')
		return (get_tex_path(++line, &pc()->image.wall_n.path, &ps()->n_tex));
	if (*line == 'S')
		return (get_tex_path(++line, &pc()->image.wall_s.path, &ps()->s_tex));
	if (*line == 'E')
		return (get_tex_path(++line, &pc()->image.wall_e.path, &ps()->e_tex));
	if (*line == 'W')
		return (get_tex_path(++line, &pc()->image.wall_o.path, &ps()->o_tex));
	return (2);
}

int	find_map_info(char *line)
{
	int	i;
	int	ret;

	i = 0;
	while (line[i] && (line[i] == '\t' || line[i] == ' '))
		i++;
	if (line[i] == '\n' || line[i] == '\0')
		return (0);
	ret = find_tex_info(line);
	if (ret != 2)
	{
		return (ret);
	}
	if (line[i] == 'F')
		return (get_hex_num(&line[i + 1], &pc()->image.floor, &ps()->c_floor));
	if (line[i] == 'C')
		return (get_hex_num(&line[i + 1], &pc()->image.ceiling, &ps()->c_ceil));
	if (line[i] == '1')
		return (2);
	return (err_msg("Wrong identifier (C, F, N, S, E, W, e, d) ", line[i]), 1);
}

bool	check_missing_infos(void)
{
	if (!ps()->n_tex)
		return (err_msg("North texture missing", 0), true);
	if (!ps()->e_tex)
		return (err_msg("East texture missing", 0), true);
	if (!ps()->o_tex)
		return (err_msg("West texture missing", 0), true);
	if (!ps()->s_tex)
		return (err_msg("South texture missing", 0), true);
	if (!ps()->c_floor)
		return (err_msg("Floor color missing", 0), true);
	if (!ps()->c_ceil)
		return (err_msg("Ceiling color missing", 0), true);
	return (false);
}

bool	valid_map_info(int fd, char *map_name)
{
	char	*line;
	int		ret;

	line = get_next_line(fd);
	while (line)
	{
		ps()->map_start_in_fd++;
		ret = find_map_info(line);
		free(line);
		if (ret == 2)
			break ;
		if (ret == 1)
			return (false);
		line = get_next_line(fd);
	}
	if (check_missing_infos())
		return (false);
	if (!create_map(fd, map_name))
		return (false);
	return (true);
}
