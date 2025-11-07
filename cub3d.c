/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 13:00:33 by mprazere          #+#    #+#             */
/*   Updated: 2025/11/07 13:00:35 by mprazere         ###   ########.fr       */
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

void safe_free(void *ptr)
{
	if (ptr)
		free(ptr);
	ptr = NULL;
}

void safe_destroy_img(void * img)
{
	if (img)
		mlx_destroy_image(pc()->mlx, img);
	img = NULL;
}

void free_game_values()
{
	free_array();
	safe_free(pc()->enemies);
	pc()->enemy_count = 0;
	safe_free(pc()->coin);
	pc()->coin_count = 0;
	pc()->coin_captured = 0;
	safe_free(pc()->door);
	pc()->door_count = 0;
	safe_destroy_img(pc()->image.wall_s.image);
	safe_destroy_img(pc()->image.wall_n.image);
	safe_destroy_img(pc()->image.wall_e.image);
	safe_destroy_img(pc()->image.wall_o.image);
	safe_free(pc()->image.wall_n.path);
	safe_free(pc()->image.wall_s.path);
	safe_free(pc()->image.wall_e.path);
	safe_free(pc()->image.wall_o.path);
}

void reset_ps()
{
	ps()->bonus = 0;
	ps()->c_ceil = 0;
	ps()->c_floor = 0;
	ps()->e_tex = 0;
	ps()->ff_coin = 0;
	ps()->ff_ret = 0;
	ps()->map_h = 0;
	ps()->map_start_in_fd = 0;
	ps()->n_tex = 0;
	ps()->o_tex = 0;
	ps()->p_count = 0;
	ps()->s_tex = 0;
	ps()->x = 0;
	ps()->y = 0;
}

bool	avl_mode_init(int argc, char **argv)
{
	free_game_values();
	ft_memset(ps(), 0, sizeof(t_parse));
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
	init_eval_images();
	return (true);
}

int	main(int argc, char **argv)
{
	pc()->argc = argc;
	pc()->argv = argv;
	pc()->mode = MENU;
	init_game();
	hook_and_loop();
	destroy_everything(1);
	return (0);
}

/*
draw_hud - lvl no centro ou eval numero de mortes na esquerda
carregar imagem da barra com texto fixo
carregar imagem de cada digito 
juntar as partes a cada frame
*/