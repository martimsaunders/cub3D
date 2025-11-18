/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 13:35:54 by mateferr          #+#    #+#             */
/*   Updated: 2025/11/18 16:15:21 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	parse_file_fill(t_parse *f, const char *filepath)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(filepath, O_RDONLY);
	if (fd == -1)
		return (perror("Error\n"), false);
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		f->file[i] = ft_strdup(line);
		free(line);
		if (!f->file[i++])
			return (perror("Error\n"), close(fd), false);
	}
	f->file[i] = NULL;
	close(fd);
	return (true);
}

bool	parse_file_load(t_parse *f, const char *filepath)
{
	int		fd;
	char	*line;

	fd = open(filepath, O_RDONLY);
	if (fd == -1)
		return (ft_putendl_fd("Error", 2), perror(filepath), false);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		free(line);
		f->line_count++;
	}
	close(fd);
	f->file = ft_calloc(f->line_count + 1, sizeof(char *));
	if (!f->file)
		return (perror("Error\n"), false);
	return (parse_file_fill(f, filepath));
}

void	parse_file_destroy(t_parse *f, int error)
{
	if (f->file)
		parse_free_array(f->file);
	pc()->map = f->map;
	pc()->image.floor = f->f_hex;
	pc()->image.ceiling = f->c_hex;
	pc()->coin_count = f->coin_count;
	pc()->door_count = f->door_count;
	pc()->enemy_count = f->enemy_count;
	pc()->image.wall_n.path = f->n_path;
	pc()->image.wall_s.path = f->s_path;
	pc()->image.wall_e.path = f->e_path;
	pc()->image.wall_o.path = f->w_path;
	if (error)
		destroy_everything(1);
}

bool	parse_validate_map(t_parse *f)
{
	int	x;
	int	y;

	f->map_cpy = parse_copy_matrix(f->map);
	if (!f->map_cpy)
		return (false);
	if (!parse_find_player(f, &x, &y))
		return (err_msg("Player not set", 0), parse_free_array(f->map_cpy),
			false);
	f->map_cpy[y][x] = '0';
	if (!parse_map_flood_fill(f, x, y))
		return (parse_free_array(f->map_cpy), false);
	if (!parse_flood_fill_extra_checks(f))
		return (parse_free_array(f->map_cpy), false);
	parse_free_array(f->map_cpy);
	f->map_cpy = NULL;
	return (parse_validate_coins_pos(f));
}
