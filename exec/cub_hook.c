/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: praders <praders@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 13:01:08 by mateferr          #+#    #+#             */
/*   Updated: 2025/11/05 18:20:40 by praders          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	hook_and_loop(void)
{
	mlx_hook(pc()->win, 2, 1L << 0, key_press, NULL);
	mlx_hook(pc()->win, 3, 1L << 1, key_release, NULL);
	mlx_hook(pc()->win, 17, 0, end_window, NULL);
	mlx_loop_hook(pc()->mlx, draw_move, NULL);
	mlx_loop(pc()->mlx);
}

int	key_press(int keycode)
{
	if (keycode == XK_Escape)
		(ft_putstr_fd("You exited the game\n", 1), destroy_everything(0));
	if (keycode == XK_w)
		pc()->button.w = true;
	if (keycode == XK_a)
		pc()->button.a = true;
	if (keycode == XK_s)
		pc()->button.s = true;
	if (keycode == XK_d)
		pc()->button.d = true;
	if (keycode == XK_Left)
		pc()->button.left = true;
	if (keycode == XK_Right)
		pc()->button.right = true;
	return (0);
}

int	key_release(int keycode)
{
	if (keycode == XK_w)
		pc()->button.w = false;
	if (keycode == XK_a)
		pc()->button.a = false;
	if (keycode == XK_s)
		pc()->button.s = false;
	if (keycode == XK_d)
		pc()->button.d = false;
	if (keycode == XK_Left)
		pc()->button.left = false;
	if (keycode == XK_Right)
		pc()->button.right = false;
	return (0);
}

int	draw_move(void)
{
	int i;

	i = -1;
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
	draw_mini_map();
	mlx_put_image_to_window(pc()->mlx, pc()->win, pc()->image.image, 0, 0);
	return (0);
}
