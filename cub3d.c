/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: praders <praders@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 12:02:31 by praders           #+#    #+#             */
/*   Updated: 2025/11/12 15:47:32 by praders          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_game	*pc(void)
{
	static t_game	pc;

	return (&pc);
}

/* void	safe_free(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void	safe_destroy_img(void **img)
{
	if (img && *img)
	{
		mlx_destroy_image(pc()->mlx, *img);
		*img = NULL;
	}
}

void	free_game_values(void)
{
	free_array();
	safe_free((void **)&pc()->enemies);
	pc()->enemy_count = 0;
	safe_free((void **)&pc()->coin);
	pc()->coin_count = 0;
	pc()->coin_captured = 0;
	safe_free((void **)&pc()->door);
	pc()->door_count = 0;
	if (pc()->mode == LVLS)
		pc()->death_count = 0;
	safe_destroy_img((void **)&pc()->image.wall_s.image);
	safe_destroy_img((void **)&pc()->image.wall_n.image);
	safe_destroy_img((void **)&pc()->image.wall_e.image);
	safe_destroy_img((void **)&pc()->image.wall_o.image);
	safe_free((void **)&pc()->image.wall_n.path);
	safe_free((void **)&pc()->image.wall_s.path);
	safe_free((void **)&pc()->image.wall_e.path);
	safe_free((void **)&pc()->image.wall_o.path);
} */

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
