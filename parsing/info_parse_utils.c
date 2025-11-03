/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_parse_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 12:11:48 by mateferr          #+#    #+#             */
/*   Updated: 2025/11/03 16:55:48 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	get_tex_path(char *line, char **dst, int *info)
{
	int	fd;

	while (*line && (*line == '\t' || *line == ' '))
		line++;
	line[ft_strlen(line) - 1] = '\0';
	if (*dst)
		return (err_msg("Duplicated texture info", 0), 1);
	*dst = ft_strdup(line);
	if (!*dst)
		return (perror("Error\n"), 1);
	fd = open(*dst, O_RDONLY);
	if (fd == -1)
		return (write(2, "Error\n", 6), perror(*dst), 1);
	*info = 1;
	close(fd);
	return (0);
}

bool	valid_color_nums(int i, char **nums, int rgb[3])
{
	int	j;

	if (i == 3)
		return (err_msg("Invalid color information (C/F R,G,B)", 0), false);
	j = 0;
	while (nums[i][j + 1])
	{
		if (j == 3)
			return (err_msg("Invalid color number (0 a 255)", 0), false);
		if (!ft_isdigit(nums[i][j]))
			return (err_msg("Invalid color information (C/F R,G,B)", 0),
				false);
		j++;
	}
	rgb[i] = ft_atoi(nums[i]);
	if (rgb[i] > 255)
		return (err_msg("Invalid color number (0 a 255)", 0), false);
	return (true);
}

int	get_hex_num(char *line, int *dst, int *info)
{
	char	**nums;
	int		i;
	int		rgb[3];

	while (*line && (*line == '\t' || *line == ' '))
		line++;
	nums = ft_split(line, ',');
	if (!nums)
		return (perror("Error\n"), 1);
	i = 0;
	while (nums[i])
	{
		if (!valid_color_nums(i, nums, rgb))
			return (free_cpy(nums), 1);
		i++;
	}
	*dst = ((unsigned)rgb[0] << 16) | ((unsigned)rgb[1] << 8)
		| (unsigned)rgb[2];
	*info = 1;
	free_cpy(nums);
	return (0);
}
