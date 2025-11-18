/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_header_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 13:36:07 by mateferr          #+#    #+#             */
/*   Updated: 2025/11/18 16:16:59 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	parse_check_texture(char *line, char **dst)
{
	char	tex;
	int		tex_last;
	int		fd;

	if (*dst)
		return (err_msg("Duplicated texture: ", *line), false);
	tex = *line;
	line++;
	while (parse_is_space(*line))
		line++;
	if (*line == '\0' || *line == '\n')
		return (err_msg("Invalid texture: ", tex), false);
	tex_last = (int)ft_strlen(line) - 1;
	if (line[tex_last] == '\n')
		line[tex_last] = '\0';
	*dst = ft_strdup(line);
	if (!*dst)
		return (perror("Error\n"), false);
	fd = open(*dst, O_RDONLY);
	if (fd == -1)
		return (err_msg("Invalid texture: ", tex), false);
	close(fd);
	return (true);
}

bool	parse_get_texture(char *line, t_parse *f)
{
	while (line)
	{
		if (parse_is_space(*line))
			line++;
		else if (*line == 'N')
			return (parse_check_texture(line, &f->n_path));
		else if (*line == 'E')
			return (parse_check_texture(line, &f->e_path));
		else if (*line == 'S')
			return (parse_check_texture(line, &f->s_path));
		else if (*line == 'W')
			return (parse_check_texture(line, &f->w_path));
	}
	return (false);
}

bool	parse_check_numbers(char **nums, int *id, int *dst)
{
	int	i;
	int	j;
	int	rgb[3];

	i = -1;
	while (nums[++i])
	{
		j = -1;
		while (nums[i][++j])
		{
			if (j > 2 || !ft_isdigit(nums[i][j]))
				return (err_msg("Invalid color number", 0), false);
		}
		if (i > 2)
			return (err_msg("Invalid color", 0), false);
		rgb[i] = atoi(nums[i]);
		if (rgb[i] < 0 || rgb[i] > 255)
			return (err_msg("Invalid color number", 0), false);
	}
	*dst = ((unsigned)rgb[0] << 16)
		| ((unsigned)rgb[1] << 8) | (unsigned)rgb[2];
	*id = 1;
	return (true);
}

bool	parse_check_color(char *line, int *id, int *dst)
{
	int	line_last;

	if (*id != 0)
		return (err_msg("Duplicated color: ", *line), false);
	line++;
	while (parse_is_space(*line))
		line++;
	if (*line == '\0' || *line == '\n')
		return (err_msg("Invalid color", 0), false);
	line_last = (int)ft_strlen(line) - 1;
	if (line[line_last] == '\n')
		line[line_last] = '\0';
	if (!parse_check_color_str(line, id, dst))
		return (false);
	return (true);
}

bool	parse_get_color(char *line, t_parse *f)
{
	while (line)
	{
		if (parse_is_space(*line))
			line++;
		else if (*line == 'C')
			return (parse_check_color(line, &f->c_col, &f->c_hex));
		else if (*line == 'F')
			return (parse_check_color(line, &f->f_col, &f->f_hex));
	}
	return (false);
}
