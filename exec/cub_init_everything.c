/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_init_everything.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 11:50:38 by mprazere          #+#    #+#             */
/*   Updated: 2025/11/06 13:10:47 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	safe_image(char *str, t_asset *asset, t_image *image, int type)
{
	if (type == 0)
	{
		asset->image = mlx_xpm_file_to_image(pc()->mlx, str, &asset->width,
				&asset->height);
		if (!asset->image)
			return (ft_putstr_fd("Error: couldn't load images.\n", 2),
			destroy_everything(1));
		asset->addr = mlx_get_data_addr(asset->image, &asset->bpp,
				&asset->line_lenght, &asset->endian);
	}
	else if (type == 1)
	{
		image->image = mlx_new_image(pc()->mlx, WIDTH, HEIGHT);
		if (!image->image)
			return (ft_putstr_fd("Error: couldn't load images.\n", 2),
			destroy_everything(1));
		image->addr = mlx_get_data_addr(image->image, &image->bpp,
				&image->line_lenght, &image->endian);
	}
}

void	init_eval_images(void)
{
	safe_image(pc()->image.wall_n.path, &pc()->image.wall_n, NULL, 0);
	safe_image(pc()->image.wall_s.path, &pc()->image.wall_s, NULL, 0);
	safe_image(pc()->image.wall_e.path, &pc()->image.wall_e, NULL, 0);
	safe_image(pc()->image.wall_o.path, &pc()->image.wall_o, NULL, 0);
}

void init_menu_images(void)
{
	safe_image("assets/mm.xpm", &pc()->image.menu[0], NULL, 0);
	safe_image("assets/mm_play.xpm", &pc()->image.menu[1], NULL, 0);
	safe_image("assets/mm_train.xpm", &pc()->image.menu[2], NULL, 0);
	safe_image("assets/mm_keys.xpm", &pc()->image.menu[3], NULL, 0);
	safe_image("assets/mm_eval.xpm", &pc()->image.menu[4], NULL, 0);
}

void	init_images(void)
{
	safe_image(NULL, NULL, &pc()->image, 1);
	safe_image("assets/enemy2.xpm", &pc()->image.enemy, NULL, 0);
	safe_image("assets/door.xpm", &pc()->image.door[0], NULL, 0);
	safe_image("assets/door_unlock.xpm", &pc()->image.door[1], NULL, 0);
	safe_image("assets/coin1.xpm", &pc()->image.coin[0], NULL, 0);
	safe_image("assets/coin2.xpm", &pc()->image.coin[1], NULL, 0);
	safe_image("assets/coin3.xpm", &pc()->image.coin[2], NULL, 0);
	safe_image("assets/coin4.xpm", &pc()->image.coin[3], NULL, 0);
	safe_image("assets/coin5.xpm", &pc()->image.coin[4], NULL, 0);
	safe_image("assets/coin6.xpm", &pc()->image.coin[5], NULL, 0);
	safe_image("assets/coin7.xpm", &pc()->image.coin[6], NULL, 0);
	safe_image("assets/coin8.xpm", &pc()->image.coin[7], NULL, 0);
	init_menu_images();
	init_eval_images();
}

void	init_game(void)
{
	pc()->mlx = mlx_init();
	if (!pc()->mlx)
		(ft_putstr_fd("Error: couldn't initiate mlx.\n", 2),
			destroy_everything(1));
	pc()->win = mlx_new_window(pc()->mlx, WIDTH, HEIGHT, "cub3d");
	if (!pc()->win)
		(ft_putstr_fd("Error: couldn't initiate window.\n", 2),
			destroy_everything(1));
	init_images();
}
