/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 13:00:56 by mprazere          #+#    #+#             */
/*   Updated: 2025/11/07 13:00:58 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	destroy_asset(t_asset *asset, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		if (asset[i].image)
			mlx_destroy_image(pc()->mlx, asset[i].image);
		i++;
	}
}

void	destroy_everything(int exit_status)
{
	if (pc()->image.image)
		mlx_destroy_image(pc()->mlx, pc()->image.image);
	destroy_asset(pc()->image.coin, 8);
	destroy_asset(pc()->image.door, 2);
	destroy_asset(pc()->image.menu, 5);
	destroy_asset(pc()->image.m_ctrls, 2);
	destroy_asset(pc()->image.train, 12);
	if (pc()->image.enemy.image)
		mlx_destroy_image(pc()->mlx, pc()->image.enemy.image);
	free_game_values();
	if (pc()->win)
		mlx_destroy_window(pc()->mlx, pc()->win);
	if (pc()->mlx)
		(mlx_destroy_display(pc()->mlx), free(pc()->mlx));
	exit(exit_status);
}

void	free_array(void)
{
	int	y;

	y = 0;
	if (!pc()->map)
		return ;
	while (pc()->map[y])
		free(pc()->map[y++]);
	free(pc()->map);
	pc()->map = NULL;
}

int	end_window(void)
{
	ft_putstr_fd("You exited the game\n", 1);
	destroy_everything(0);
	return (0);
}
