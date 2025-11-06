/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 13:02:26 by mateferr          #+#    #+#             */
/*   Updated: 2025/11/06 12:57:13 by mateferr         ###   ########.fr       */
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
	int	i;

	pc()->player.x = pc()->start.player.x;
	pc()->player.y = pc()->start.player.y;
	pc()->player.angle = pc()->start.player.angle;
	pc()->coin_captured = 0;
	i = -1;
	while (++i < pc()->door_count)
		pc()->door[i].state = 0;
	i = -1;
	while (++i < pc()->coin_count)
		pc()->coin[i].state = 0;
}

void	init_eval_characters_values(void)
{
	int	i;

	pc()->player.move_speed = 0.025;
	pc()->player.rot_speed = 0.02;
	pc()->player.dir_x = cos(pc()->player.angle);
	pc()->player.dir_y = sin(pc()->player.angle);
	pc()->player.plane_x = -pc()->player.dir_y * 0.66;
	pc()->player.plane_y = pc()->player.dir_x * 0.66;
	i = -1;
	while (++i < pc()->enemy_count)
	{
		pc()->enemies[i].speed = 0.02;
		pc()->enemies[i].direction = 0;
		pc()->enemies[i].is_coin = 0;
	}
}

void	init_eval_images(void)
{
	safe_image(pc()->image.wall_n.path, &pc()->image.wall_n, NULL, 0);
	safe_image(pc()->image.wall_s.path, &pc()->image.wall_s, NULL, 0);
	safe_image(pc()->image.wall_e.path, &pc()->image.wall_e, NULL, 0);
	safe_image(pc()->image.wall_o.path, &pc()->image.wall_o, NULL, 0);
	if (!pc()->image.wall_n.image || !pc()->image.wall_s.image
		|| !pc()->image.wall_e.image || !pc()->image.wall_o.image)
		return (ft_putstr_fd("Error: couldn't load eval images.\n", 2),
			destroy_everything(1));
	safe_address(&pc()->image.wall_n, NULL, 0);
	safe_address(&pc()->image.wall_s, NULL, 0);
	safe_address(&pc()->image.wall_e, NULL, 0);
	safe_address(&pc()->image.wall_o, NULL, 0);
}

bool	avl_mode_init(int argc, char **argv)
{
	// char *line;
	if (argc != 2)
		return (err_msg("1 argument only (./map_path)", 0), false);
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
		return (false);
	init_eval_characters_values();
	return (true);
}

int	main(int argc, char **argv)
{
	pc()->mode = EVAL;
	init_game();
	if (!avl_mode_init(argc, argv)) // chamar a partir do menu ao clicar
		return (1);
	hook_and_loop();
	destroy_everything(1);
	return (0);
}

/*
ao entrar no jogo dar init aos elementos (a partir do menu)
ao sair do jogo dar free aos elementos do jogo (a partir do pausa ou esc)
*/