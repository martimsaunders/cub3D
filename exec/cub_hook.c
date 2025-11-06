/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 12:57:30 by mateferr          #+#    #+#             */
/*   Updated: 2025/11/06 13:36:53 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	hook_and_loop(void)
{
	mlx_hook(pc()->win, 2, 1L << 0, key_press, NULL);
	mlx_hook(pc()->win, 3, 1L << 1, key_release, NULL);
	mlx_hook(pc()->win, 4, 1L << 2, mouse_click, NULL);
	mlx_hook(pc()->win, 6, 1L << 6, mouse_move, NULL);
	mlx_hook(pc()->win, 7, 1L << 4, mouse_in, NULL);
	mlx_hook(pc()->win, 8, 1L << 5, mouse_out, NULL);
	mlx_hook(pc()->win, 17, 0, end_window, NULL);
	mlx_loop_hook(pc()->mlx, draw_screen, NULL);
	mlx_loop(pc()->mlx);
}

int	key_press(int keycode)
{
	if (pc()->mode == EVAL || pc()->mode == GAME)
	{
		if (keycode == XK_Escape)
			pc()->mode = PAUSE;
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
	}
	else if (pc()->mode == PAUSE)
	{
		if (keycode == XK_Escape)
			(ft_putstr_fd("You exited the game\n", 1), destroy_everything(0));
	}
	return (0);
}

int	key_release(int keycode)
{
	if (pc()->mode == EVAL || pc()->mode == GAME)
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
	}
	return (0);
}

void	draw_eval_screen(void)
{
	int	i;

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
}

int	draw_screen(void)
{
	if (pc()->mode == EVAL)
		draw_eval_screen();
	if (pc()->mode == GAME)
		draw_game_screen();
	if (pc()->mode == MENU)
		draw_main_menu();
	else if (pc()->mode == CTRLS)
		draw_ctrls_menu();
	else if (pc()->mode == LVLS)
		draw_lvls_menu();
	else if (pc()->mode == PAUSE)
		draw_pause_menu();
	return (0);
}

void	draw_pause_menu(void)
{
	return ;
}
void	draw_lvls_menu(void)
{
	return ;
}
void	draw_ctrls_menu(void)
{
	return ;
}
void	draw_main_menu(void)
{
	return ;
}
void	draw_game_screen(void)
{
	return ;
}
