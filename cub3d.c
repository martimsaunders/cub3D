/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 13:02:26 by mateferr          #+#    #+#             */
/*   Updated: 2025/11/04 19:52:20 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_game	*pc(void)
{
	static t_game	pc;

	return (&pc);
}

void	restart_level(void)
{
	pc()->player.x = pc()->start.player.x;
	pc()->player.y = pc()->start.player.y;
	pc()->player.angle = pc()->start.player.angle;
}

void	init_caracters_values(void)
{
	int	i;

	pc()->player.move_speed = 0.025;
	pc()->player.rot_speed = 0.02;
	pc()->player.dir_x = cos(pc()->player.angle);
	pc()->player.dir_y = sin(pc()->player.angle);
	pc()->player.plane_x = -pc()->player.dir_y * 0.66;
	pc()->player.plane_y = pc()->player.dir_x * 0.66;
	pc()->enemy_count = 3;
	i = -1;
	while (++i < pc()->enemy_count)
	{
		pc()->enemies[i].speed = 0.02;
		pc()->enemies[i].direction = 1;
	}
}

int	main(int argc, char **argv)
{
	// char *line;
	
	if (argc != 2)
		return (err_msg("1 argument only (./map_path)", 0), 1);
	// while (1)
	// {
	// 	ft_printf("Allow bonus features? (y/n)\n");
	// 	line = get_next_line(0);
	// 	if (!line)
	// 		return (perror("Error\n"), 1);
	// 	if (!ft_strncmp(line, "y\n", 3) || !ft_strncmp(line, "n\n", 3))
	// 	{
	// 		if (!ft_strncmp(line, "y\n", 3))
	// 			ps()->bonus = 1;
	// 		free(line);
	// 		break ;
	// 	}
	// 	free(line);
	// }
	ps()->bonus = 1;
	if (!map_file_parsing(argv[1]))
		destroy_everything(1);
	init_game();
	hook_and_loop();
	destroy_everything(1);
	return (0);
}
