/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_draw_screen.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:58:55 by praders           #+#    #+#             */
/*   Updated: 2025/11/11 16:35:37 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_game_menu(void)
{
	int	x;
	int	y;

	x = pc()->player.mousex;
	y = pc()->player.mousey;
	if ((x >= 420 && x <= 651) && (y >= 518 && y <= 644))
		mlx_put_image_to_window(pc()->mlx, pc()->win,
			pc()->image.game_m[1].image, 0, 0);
	else if ((x >= 703 && x <= 872) && (y >= 518 && y <= 644))
		mlx_put_image_to_window(pc()->mlx, pc()->win,
			pc()->image.game_m[2].image, 0, 0);
	else
		mlx_put_image_to_window(pc()->mlx, pc()->win,
			pc()->image.game_m[0].image, 0, 0);
	return ;
}

void	draw_game_screen(void)
{
	int	i;

	i = 0;
	ft_memset(pc()->image.addr, 0, HEIGHT * pc()->image.line_lenght);
	move_player();
	interact_door();
	while (i < pc()->enemy_count)
		move_enemy(&pc()->enemies[i++]);
	pc()->coin_frame_counter++;
	if (pc()->coin_frame_counter > 5)
	{
		pc()->coin_frame_counter = 0;
		pc()->coin_frame = (pc()->coin_frame + 1) % 8;
	}
	check_enemy_colision();
	check_coin_colision();
	ray_cast();
	draw_minimap();
	mlx_put_image_to_window(pc()->mlx, pc()->win, pc()->image.image, 0, 0);
}

void	draw_ctrls_menu(void)
{
	int	x;
	int	y;

	x = pc()->player.mousex;
	y = pc()->player.mousey;
	if (x >= 527 && x <= 752 && y >= 520 && y <= 639)
		mlx_put_image_to_window(pc()->mlx, pc()->win,
			pc()->image.m_ctrls[1].image, 0, 0);
	else
		mlx_put_image_to_window(pc()->mlx, pc()->win,
			pc()->image.m_ctrls[0].image, 0, 0);
	return ;
}
void	draw_main_menu(void)
{
	int	x;
	int	y;

	x = pc()->player.mousex;
	y = pc()->player.mousey;
	if ((x >= 81 && x <= 283) && (y >= 450 && y <= 611))
		mlx_put_image_to_window(pc()->mlx, pc()->win, pc()->image.menu[1].image,
			0, 0);
	else if ((x >= 382 && x <= 595) && (y >= 450 && y <= 611))
		mlx_put_image_to_window(pc()->mlx, pc()->win, pc()->image.menu[4].image,
			0, 0);
	else if ((x >= 686 && x <= 904) && (y >= 450 && y <= 611))
		mlx_put_image_to_window(pc()->mlx, pc()->win, pc()->image.menu[2].image,
			0, 0);
	else if ((x >= 1003 && x <= 1208) && (y >= 450 && y <= 611))
		mlx_put_image_to_window(pc()->mlx, pc()->win, pc()->image.menu[3].image,
			0, 0);
	else
		mlx_put_image_to_window(pc()->mlx, pc()->win, pc()->image.menu[0].image,
			0, 0);
	return ;
}
