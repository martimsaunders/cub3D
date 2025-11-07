/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 15:29:11 by mateferr          #+#    #+#             */
/*   Updated: 2025/11/07 14:38:51 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	hook_and_loop(void)
{
	mlx_hook(pc()->win, 2, 1L << 0, key_press, NULL);
	mlx_hook(pc()->win, 3, 1L << 1, key_release, NULL);
	mlx_hook(pc()->win, 4, 1L << 2, mouse_click, NULL);
	mlx_hook(pc()->win, 6, 1L << 6, mouse_move, NULL);
	/* mlx_hook(pc()->win, 7, 1L << 4, mouse_in, NULL);
	mlx_hook(pc()->win, 8, 1L << 5, mouse_out, NULL); */
	mlx_hook(pc()->win, 17, 0, end_window, NULL);
	mlx_loop_hook(pc()->mlx, draw_screen, NULL);
	mlx_loop(pc()->mlx);
}

int	key_press(int keycode)
{
	if (pc()->mode == MENU && keycode == XK_Escape)
		return (ft_putstr_fd("You exited the game\n", 1), destroy_everything(0),
			0);
	if ((pc()->mode == GAME || pc()->mode == EVAL || pc()->mode == LVLS_GAME) && keycode == XK_Escape)
	{
		mlx_mouse_show(pc()->mlx, pc()->win);
		pc()->mode = MENU;
	}
	if ((pc()->mode == GAME || pc()->mode == EVAL || pc()->mode == LVLS_GAME) && keycode == XK_w)
		pc()->button.w = true;
	if ((pc()->mode == GAME || pc()->mode == EVAL || pc()->mode == LVLS_GAME) && keycode == XK_a)
		pc()->button.a = true;
	if ((pc()->mode == GAME || pc()->mode == EVAL || pc()->mode == LVLS_GAME) && keycode == XK_s)
		pc()->button.s = true;
	if ((pc()->mode == GAME || pc()->mode == EVAL || pc()->mode == LVLS_GAME) && keycode == XK_d)
		pc()->button.d = true;
	if ((pc()->mode == GAME || pc()->mode == EVAL || pc()->mode == LVLS_GAME) && keycode == XK_Left)
		pc()->button.left = true;
	if ((pc()->mode == GAME || pc()->mode == EVAL || pc()->mode == LVLS_GAME) && keycode == XK_Right)
		pc()->button.right = true;
	return (0);
}

int	key_release(int keycode)
{
	if (pc()->mode == EVAL || pc()->mode == GAME || pc()->mode == LVLS_GAME)
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
	draw_mini_map();
	mlx_put_image_to_window(pc()->mlx, pc()->win, pc()->image.image, 0, 0);
}

int	draw_screen(void)
{
	if (pc()->mode == EVAL)
		draw_eval_screen();
	else if (pc()->mode == GAME)
		draw_game_screen();
	else if (pc()->mode == MENU)
		draw_main_menu();
	else if (pc()->mode == CTRLS)
		draw_ctrls_menu();
	else if (pc()->mode == LVLS)
		draw_lvls_menu();
	else if (pc()->mode == LVLS_GAME)
		draw_lvls_game();
	else if (pc()->mode == GAME_MENU)
		draw_game_menu();
	return (0);
}

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

void	draw_lvls_game(void)
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
	draw_mini_map();
	mlx_put_image_to_window(pc()->mlx, pc()->win, pc()->image.image, 0, 0);
}

void	draw_lvls_menu(void)
{
	int	x;
	int	y;

	x = pc()->player.mousex;
	y = pc()->player.mousey;
	if ((x >= 74 && x <= 280) && (y >= 69 && y <= 275))
		mlx_put_image_to_window(pc()->mlx, pc()->win, pc()->image.train[0].image, 0,
			0);
	else if ((x >= 307 && x <= 511) && (y >= 69 && y <= 275))
		mlx_put_image_to_window(pc()->mlx, pc()->win, pc()->image.train[1].image, 0,
			0);
	else if ((x >= 539 && x <= 742) && (y >= 69 && y <= 275))
		mlx_put_image_to_window(pc()->mlx, pc()->win, pc()->image.train[2].image, 0,
			0);
	else if ((x >= 770 && x <= 973) && (y >= 69 && y <= 275))
		mlx_put_image_to_window(pc()->mlx, pc()->win, pc()->image.train[3].image, 0,
			0);
	else if ((x >= 1001 && x <= 1204) && (y >= 69 && y <= 275))
		mlx_put_image_to_window(pc()->mlx, pc()->win, pc()->image.train[4].image, 0,
			0);
	else if ((x >= 74 && x <= 280) && (y >= 320 && y <= 525))
		mlx_put_image_to_window(pc()->mlx, pc()->win, pc()->image.train[5].image, 0,
			0);
	else if ((x >= 307 && x <= 511) && (y >= 320 && y <= 525))
		mlx_put_image_to_window(pc()->mlx, pc()->win, pc()->image.train[6].image, 0,
			0);
	else if ((x >= 539 && x <= 742) && (y >= 320 && y <= 525))
		mlx_put_image_to_window(pc()->mlx, pc()->win, pc()->image.train[7].image, 0,
			0);
	else if ((x >= 770 && x <= 973) && (y >= 320 && y <= 525))
		mlx_put_image_to_window(pc()->mlx, pc()->win, pc()->image.train[8].image, 0,
			0);
	else if ((x >= 1001 && x <= 1204) && (y >= 320 && y <= 525))
		mlx_put_image_to_window(pc()->mlx, pc()->win, pc()->image.train[9].image, 0,
			0);
	else if ((x >= 525 && x <= 755) && (y >= 549 && y <= 672))
		mlx_put_image_to_window(pc()->mlx, pc()->win, pc()->image.train[11].image, 0,
			0);
	else
		mlx_put_image_to_window(pc()->mlx, pc()->win,
			pc()->image.train[10].image, 0, 0);
	return ;
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
void	draw_game_screen(void)
{
	return ;
}
