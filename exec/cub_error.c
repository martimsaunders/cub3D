/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: praders <praders@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 12:59:43 by mateferr          #+#    #+#             */
/*   Updated: 2025/11/05 18:24:37 by praders          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	destroy_everything(int exit_status)
{
	if (pc()->image.image)
		mlx_destroy_image(pc()->mlx, pc()->image.image);
	if (pc()->image.coin[0].image)
		mlx_destroy_image(pc()->mlx, pc()->image.coin[0].image);
	if (pc()->image.coin[1].image)
		mlx_destroy_image(pc()->mlx, pc()->image.coin[1].image);
	if (pc()->image.coin[2].image)
		mlx_destroy_image(pc()->mlx, pc()->image.coin[2].image);
	if (pc()->image.coin[3].image)
		mlx_destroy_image(pc()->mlx, pc()->image.coin[3].image);
	if (pc()->image.coin[4].image)
		mlx_destroy_image(pc()->mlx, pc()->image.coin[4].image);
	if (pc()->image.coin[5].image)
		mlx_destroy_image(pc()->mlx, pc()->image.coin[5].image);
	if (pc()->image.coin[6].image)
		mlx_destroy_image(pc()->mlx, pc()->image.coin[6].image);
	if (pc()->image.coin[7].image)
		mlx_destroy_image(pc()->mlx, pc()->image.coin[7].image);
	if (pc()->image.door[0].image)
		mlx_destroy_image(pc()->mlx, pc()->image.door[0].image);
	if (pc()->image.door[1].image)
		mlx_destroy_image(pc()->mlx, pc()->image.door[1].image);
	if (pc()->image.enemy.image)
		mlx_destroy_image(pc()->mlx, pc()->image.enemy.image);
	if (pc()->image.wall_n.image)
		mlx_destroy_image(pc()->mlx, pc()->image.wall_n.image);
	if (pc()->image.wall_s.image)
		mlx_destroy_image(pc()->mlx, pc()->image.wall_s.image);
	if (pc()->image.wall_e.image)
		mlx_destroy_image(pc()->mlx, pc()->image.wall_e.image);
	if (pc()->image.wall_o.image)
		mlx_destroy_image(pc()->mlx, pc()->image.wall_o.image);
	if (pc()->image.wall_n.path)
		free(pc()->image.wall_n.path);
	if (pc()->image.wall_s.path)
		free(pc()->image.wall_s.path);
	if (pc()->image.wall_e.path)
		free(pc()->image.wall_e.path);
	if (pc()->image.wall_o.path)
		free(pc()->image.wall_o.path);
	if (pc()->win)
		mlx_destroy_window(pc()->mlx, pc()->win);
	if (pc()->mlx)
		(mlx_destroy_display(pc()->mlx), free(pc()->mlx));
	if (pc()->map)
		free_array();
	exit(exit_status);
}

void	free_array(void)
{
	int	y;

	y = 0;
	while (pc()->map[y])
		free(pc()->map[y++]);
	free(pc()->map);
}

int	end_window(void)
{
	ft_putstr_fd("You exited the game\n", 1);
	destroy_everything(0);
	return (0);
}
