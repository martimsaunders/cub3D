/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_init_everything.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: praders <praders@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 11:50:38 by mprazere          #+#    #+#             */
/*   Updated: 2025/10/31 14:43:16 by praders          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	safe_image(char *str, t_asset *asset, t_image *image, int type)
{
	if (type == 0)
		asset->image = mlx_xpm_file_to_image(pc()->mlx, str, &asset->width,
				&asset->height);
	else if (type == 1)
		image->image = mlx_new_image(pc()->mlx, WIDTH, HEIGHT);
}

void	safe_address(t_asset *asset, t_image *image, int type)
{
	if (type == 0)
		asset->addr = mlx_get_data_addr(asset->image, &asset->bpp,
				&asset->line_lenght, &asset->endian);
	else if (type == 1)
		image->addr = mlx_get_data_addr(image->image, &image->bpp,
				&image->line_lenght, &image->endian);
}

void	init_images(void)
{
	safe_image(NULL, NULL, &pc()->image, 1);
	safe_image("assets/enemy1.xpm", &pc()->image.enemy, NULL, 0);
	safe_image("assets/wall.xpm", &pc()->image.wall_n, NULL, 0);
	safe_image("assets/wall_s.xpm", &pc()->image.wall_s, NULL, 0);
	safe_image("assets/wall_e.xpm", &pc()->image.wall_e, NULL, 0);
	safe_image("assets/wall_o.xpm", &pc()->image.wall_o, NULL, 0);
	if (!pc()->image.image || !pc()->image.wall_n.image
		|| !pc()->image.wall_s.image || !pc()->image.wall_e.image
		|| !pc()->image.wall_o.image || !pc()->image.enemy.image)
		return (ft_putstr_fd("Error: couldn't load images.\n", 2),
			destroy_everything(1));
	safe_address(NULL, &pc()->image, 1);
	safe_address(&pc()->image.enemy, NULL, 0);
	safe_address(&pc()->image.wall_n, NULL, 0);
	safe_address(&pc()->image.wall_s, NULL, 0);
	safe_address(&pc()->image.wall_e, NULL, 0);
	safe_address(&pc()->image.wall_o, NULL, 0);
}

void	init_game(void)
{
	pc()->mlx = mlx_init();
	if (!pc()->mlx)
		(ft_putstr_fd("Error: couldn't initiate mlx.\n", 2),
			destroy_everything(1));
	init_images();
	pc()->win = mlx_new_window(pc()->mlx, WIDTH, HEIGHT, "cub3d");
	if (!pc()->win)
		(ft_putstr_fd("Error: couldn't initiate window.\n", 2),
			destroy_everything(1));
	init_player_map();
}
