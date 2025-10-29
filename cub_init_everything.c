/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_init_everything.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 11:50:38 by mprazere          #+#    #+#             */
/*   Updated: 2025/10/29 18:32:13 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	safe_image(char *str, t_asset *image)
{
	image->image = mlx_xpm_file_to_image(pc()->mlx, str, &image->width,
			&image->height);
}

void	safe_address(t_asset *image)
{
	image->addr = mlx_get_data_addr(image->image, &image->bpp,
			&image->line_lenght, &image->endian);
}

void	init_images(void)
{
	void	*temp;
	char	*addr;

	temp = mlx_new_image(pc()->mlx, WIDTH, HEIGHT);
	pc()->image.image = temp;
	safe_image("assets/wall.xpm", &pc()->image.wall_n);
	safe_image("assets/wall_s.xpm", &pc()->image.wall_s);
	safe_image("assets/wall_e.xpm", &pc()->image.wall_e);
	safe_image("assets/wall_o.xpm", &pc()->image.wall_o);
	if (!pc()->image.image || !pc()->image.wall_n.image
		|| !pc()->image.wall_s.image || !pc()->image.wall_e.image
		|| !pc()->image.wall_o.image)
		return (ft_putstr_fd("Error: couldn't load images.\n", 2),
			destroy_everything(1));
	addr = mlx_get_data_addr(pc()->image.image, &pc()->image.bpp,
			&pc()->image.line_lenght, &pc()->image.endian);
	pc()->image.addr = addr;
	safe_address(&pc()->image.wall_n);
	safe_address(&pc()->image.wall_s);
	safe_address(&pc()->image.wall_e);
	safe_address(&pc()->image.wall_o);
}

void	init_game(void)
{
	pc()->mlx = mlx_init();
	if (!pc()->mlx)
		(ft_putstr_fd("Error: mlx couldn't initiate.\n", 2),
			destroy_everything(1));
	init_images();
	pc()->win = mlx_new_window(pc()->mlx, WIDTH, HEIGHT, "cub3d");
	if (!pc()->win)
		(ft_putstr_fd("Error: window couldn't initiate.\n", 2),
			destroy_everything(1));
	init_player_map();
}
