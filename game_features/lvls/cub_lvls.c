/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_lvls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:54:22 by mateferr          #+#    #+#             */
/*   Updated: 2025/11/14 13:26:19 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

char	**file_matrix_fill(const char *filepath, char **matrix)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(filepath, O_RDONLY);
	if (fd == -1)
		return (perror("Error\n"), NULL);
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		matrix[i] = ft_strdup(line);
		free(line);
		if (!matrix[i++])
			return (perror("Error\n"), close(fd), NULL);
	}
	matrix[i] = NULL;
	close(fd);
	return (matrix);
}

char	**file_matrix_load(const char *filepath)
{
	int		fd;
	char	*line;
	int		line_count;
	char	**matrix;

	line_count = 0;
	fd = open(filepath, O_RDONLY);
	if (fd == -1)
		return (perror("Error\n"), NULL);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		line_count++;
		free(line);
	}
	close(fd);
	matrix = ft_calloc(line_count + 1, sizeof(char *));
	if (!matrix)
		return (perror("Error\n"), close(fd), NULL);
	return (file_matrix_fill(filepath, matrix));
}

void	choose_level(void)
{
	int	level;

	level = pc()->current_level;
	if (level == 1)
		set_lvl_1();
	else if (level == 2)
		set_lvl_2();
	else if (level == 3)
		set_lvl_3();
	else if (level == 4)
		set_lvl_4();
	else if (level == 5)
		set_lvl_5();
	else if (level == 6)
		set_lvl_6();
	else if (level == 7)
		set_lvl_7();
	else if (level == 8)
		set_lvl_8();
	else if (level == 9)
		set_lvl_9();
	else if (level == 10)
		set_lvl_10();
}

void	lvl_mode_init(void)
{
	char	*lvl_name;
	char	*lvl;
	char	*temp;

	lvl = ft_itoa(pc()->current_level);
	if (!lvl)
		return (destroy_everything(1));
	temp = ft_strjoin("maps/level", lvl);
	if (!temp)
		return (free(lvl), destroy_everything(1));
	lvl_name = ft_strjoin(temp, ".cub");
	free(temp);
	free(lvl);
	if (!lvl_name)
		return (destroy_everything(1));
	free_game_values();
	pc()->map = file_matrix_load(lvl_name);
	free(lvl_name);
	if (!pc()->map)
		destroy_everything(1);
	init_lvl_images();
	fill_values(-1, -1);
	choose_level();
}
