/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 13:36:41 by mateferr          #+#    #+#             */
/*   Updated: 2025/11/14 13:36:42 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	parse_init_f(t_parse *f)
{
	f->c_col = 0;
	f->f_col = 0;
	f->file = NULL;
	f->coin_check = 0;
	f->line_count = 0;
	f->map = NULL;
	f->f_hex = 0;
	f->c_hex = 0;
	f->coin_count = 0;
	f->door_count = 0;
	f->enemy_count = 0;
	f->n_path = NULL;
	f->s_path = NULL;
	f->e_path = NULL;
	f->w_path = NULL;
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

char	parse_get_char(char *line)
{
	while (line)
	{
		if (parse_is_space(*line))
			line++;
		else
			return (*line);
	}
	return (0);
}

bool	parse_is_cub_file(const char *filepath)
{
	char	*cub;

	cub = ft_strrchr(filepath, '.');
	if (!cub)
		return (err_msg("Not a .cub file", 0), false);
	if (ft_strncmp(cub, ".cub", 5) != 0)
		return (err_msg("Not a .cub file", 0), false);
	return (true);
}

void	parse_map_file(const char *filepath)
{
	t_parse	f;

	parse_init_f(&f);
	if (!parse_is_cub_file(filepath))
		parse_file_destroy(&f, 1);
	if (!parse_file_load(&f, filepath))
		parse_file_destroy(&f, 1);
	if (!parse_header(&f))
		parse_file_destroy(&f, 1);
	if (!parse_map_matrix(&f))
		parse_file_destroy(&f, 1);
	if (!parse_validate_map(&f))
		parse_file_destroy(&f, 1);
	if (!parse_set_icons_values(&f))
		parse_file_destroy(&f, 1);
	parse_file_destroy(&f, 0);
}
