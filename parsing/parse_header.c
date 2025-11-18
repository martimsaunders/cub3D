/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 13:36:12 by mateferr          #+#    #+#             */
/*   Updated: 2025/11/18 16:16:05 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	parse_check_all_infos(t_parse *f)
{
	if (!f->c_col || !f->f_col)
		return (err_msg("Color info missing", 0), false);
	if (!f->n_path || !f->e_path || !f->s_path || !f->w_path)
		return (err_msg("Texture info missing", 0), false);
	return (true);
}

bool	parse_header(t_parse *f)
{
	int		i;
	bool	ret;

	i = -1;
	while (f->file[++i])
	{
		if (!parse_is_empty_line(f->file[i]))
		{
			if (parse_is_map_line(f->file[i]))
				break ;
			else if (parse_is_texture(f->file[i]))
				ret = parse_get_texture(f->file[i], f);
			else if (parse_is_color(f->file[i]))
				ret = parse_get_color(f->file[i], f);
			else
				return (err_msg("Wrong identifier: ",
						parse_get_char(f->file[i])), false);
			if (!ret)
				return (false);
		}
	}
	f->map_idx = i;
	return (parse_check_all_infos(f));
}

bool	parse_check_color_str(char *line, int *id, int *dst)
{
	char	**nums;
	int		i;
	int		count;

	count = 0;
	i = 0;
	while (line[i])
	{
		if (line[i++] == ',')
		{
			count++;
			if (!ft_isdigit(line[i]))
				return (err_msg("Invalid color", 0), false);
		}
	}
	if (count != 2)
		return (err_msg("Invalid color", 0), false);
	nums = ft_split(line, ',');
	if (!nums)
		return (perror("Error\n"), false);
	if (!parse_check_numbers(nums, id, dst))
		return (parse_free_array(nums), false);
	return (parse_free_array(nums), true);
}
