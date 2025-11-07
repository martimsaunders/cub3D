/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_ctrl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 15:28:19 by mateferr          #+#    #+#             */
/*   Updated: 2025/11/07 15:52:14 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	mouse_click(int button, int x, int y)
{
	if (button != 1)
		return (0);
	if (pc()->mode == MENU)
		main_menu_click(x, y);
	else if (pc()->mode == CTRLS)
		ctrls_menu_click(x, y);
	else if (pc()->mode == LVLS)
		lvls_menu_click(x, y);
	else if (pc()->mode == GAME_MENU)
		game_menu_click(x, y);
	return (0);
}

int	mouse_out(void)
{
	return (0);
}

int	mouse_in(void)
{
	return (0);
}

void	mouse_cam_move(int x)
{
	int		dx;
	float	sens;

	sens = 0.001;
	if (!pc()->mouse_in_win)
	{
		if (MOUSE_HIDE != 0)
			mlx_mouse_hide(pc()->mlx, pc()->win);
		mlx_mouse_move(pc()->mlx, pc()->win, WIDTH / 2, HEIGHT / 2);
		pc()->mouse_in_win = 1;
		return ;
	}
	dx = x - WIDTH / 2;
	mlx_mouse_move(pc()->mlx, pc()->win, WIDTH / 2, HEIGHT / 2);
	if (dx == 0)
		return ;
	pc()->player.angle += dx * sens;
	if (pc()->player.angle > 2 * PI)
		pc()->player.angle = 0;
	if (pc()->player.angle < 0)
		pc()->player.angle = 2 * PI;
	pc()->player.dir_x = cos(pc()->player.angle);
	pc()->player.dir_y = sin(pc()->player.angle);
	pc()->player.plane_x = -pc()->player.dir_y * FOV;
	pc()->player.plane_y = pc()->player.dir_x * FOV;
}

int	mouse_move(int x, int y)
{
	if (pc()->mode == GAME || pc()->mode == EVAL || pc()->mode == LVLS_GAME)
		mouse_cam_move(x);
	/* else if (pc()->mode == MENU)
		mouse_move_main_menu(x, y);
	else if (pc()->mode == CTRLS)
		mouse_move_ctrls_menu(x, y);
	else if (pc()->mode == LVLS)
		mouse_move_lvls_menu(x, y);
	else if (pc()->mode == PAUSE)
		mouse_move_pause_menu(x, y); */
	else
	{
		pc()->player.mousex = x;
		pc()->player.mousey = y;
	}
	return (0);
}

void	mouse_move_pause_menu(int x, int y)
{
	(void)x;
	(void)y;
	return ;
}
void	mouse_move_lvls_menu(int x, int y)
{
	(void)x;
	(void)y;
	return ;
}
void	mouse_move_ctrls_menu(int x, int y)
{
	(void)x;
	(void)y;
	return ;
}
void	mouse_move_main_menu(int x, int y)
{
	(void)x;
	(void)y;

	return ;
}