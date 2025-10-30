/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:40:37 by mprazere          #+#    #+#             */
/*   Updated: 2025/10/30 11:30:32 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	ft_memset(pc()->image.addr, 0, HEIGHT * pc()->image.line_lenght);
	move_player();
	ray_cast();
	draw_map();
	mlx_put_image_to_window(pc()->mlx, pc()->win, pc()->image.image, 0, 0);
	return (0);
}
