/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 15:29:11 by mateferr          #+#    #+#             */
/*   Updated: 2025/11/11 16:39:06 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	hook_and_loop(void)
{
	mlx_hook(pc()->win, 2, 1L << 0, key_press, NULL);
	mlx_hook(pc()->win, 3, 1L << 1, key_release, NULL);
	mlx_hook(pc()->win, 4, 1L << 2, mouse_click, NULL);
	mlx_hook(pc()->win, 6, 1L << 6, mouse_move, NULL);
	mlx_hook(pc()->win, 17, 0, end_window, NULL);
	mlx_loop_hook(pc()->mlx, draw_screen, NULL);
	mlx_loop(pc()->mlx);
}

int	is_mode(void)
{
	int	i;

	i = pc()->mode;
	if (i == GAME || i == EVAL || i == LVLS_GAME)
		return (1);
	return (0);
}

int	key_press(int keycode)
{
	if (pc()->mode == MENU && keycode == XK_Escape)
		return (ft_putstr_fd("You exited the game\n", 1), destroy_everything(0),
			0);
	if (is_mode() && keycode == XK_Escape)
	{
		mlx_mouse_show(pc()->mlx, pc()->win);
		pc()->mode = MENU;
	}
	if (is_mode() && keycode == XK_w)
		pc()->button.w = true;
	if (is_mode() && keycode == XK_a)
		pc()->button.a = true;
	if (is_mode() && keycode == XK_s)
		pc()->button.s = true;
	if (is_mode() && keycode == XK_d)
		pc()->button.d = true;
	if (is_mode() && keycode == XK_Left)
		pc()->button.left = true;
	if (is_mode() && keycode == XK_Right)
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

int	draw_screen(void)
{
	if (pc()->mode == EVAL)
		draw_game_screen();
	else if (pc()->mode == GAME)
		draw_game_screen();
	else if (pc()->mode == MENU)
		draw_main_menu();
	else if (pc()->mode == CTRLS)
		draw_ctrls_menu();
	else if (pc()->mode == LVLS)
		draw_lvls_menu();
	else if (pc()->mode == LVLS_GAME)
		draw_game_screen();
	else if (pc()->mode == GAME_MENU)
		draw_game_menu();
	return (0);
}
