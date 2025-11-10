/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_move_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: praders <praders@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:07:38 by mprazere          #+#    #+#             */
/*   Updated: 2025/11/10 16:20:27 by praders          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	calculate_player_values(float *newx, float *newy)
{
	if (pc()->button.left)
		pc()->player.angle -= pc()->player.rot_speed;
	if (pc()->button.right)
		pc()->player.angle += pc()->player.rot_speed;
	if (pc()->player.angle > 2 * PI)
		pc()->player.angle = 0;
	if (pc()->player.angle < 0)
		pc()->player.angle = 2 * PI;
	pc()->player.dir_x = cos(pc()->player.angle);
	pc()->player.dir_y = sin(pc()->player.angle);
	pc()->player.plane_x = -pc()->player.dir_y * FOV;
	pc()->player.plane_y = pc()->player.dir_x * FOV;
	*newx = pc()->player.x;
	*newy = pc()->player.y;
}

int		is_blocked(int map_y, int map_x)
{
	if (pc()->map[map_y][map_x] == '1')
		return (1);
	if (pc()->map[map_y][map_x]== 'd' && is_door_closed(map_y, map_x))
		return (1);
	if (pc()->map[map_y][map_x] == 'n')
	{
		if (pc()->mode == LVLS_GAME)
		{
			mlx_mouse_show(pc()->mlx, pc()->win);
			pc()->mode = LVLS;
			return (1);
		}
		else if (pc()->mode == GAME)
		{
			pc()->current_level++;
			lvl_mode_init();
			return (1);
		}
	}
	return (0);
}

int		is_blocked_e(int map_y, int map_x, int type)
{
	if (type == 0)
	{
		if (pc()->map[map_y][map_x] == '1' || pc()->map[map_y][map_x] == 'd' || pc()->map[map_y][map_x] == 'g')
			return (1);
	}	
	else
		if (pc()->map[map_y][map_x] == '1' || pc()->map[map_y][map_x] == 'd')
			return (1);
	return (0);
}

void	check_collision(float newx, float newy)
{
	float	check;

	check = 0.5 - pc()->player.move_speed;
	if (!is_blocked((int)(pc()->player.y), (int)(newx))
		&& !is_blocked((int)(pc()->player.y + check), (int)(newx))
		&& !is_blocked((int)(pc()->player.y), (int)(newx + check))
		&& !is_blocked((int)(pc()->player.y + check), (int)(newx + check)))
		pc()->player.x = newx;
	if (!is_blocked((int)(newy), (int)(pc()->player.x))
		&& !is_blocked((int)(newy + check), (int)(pc()->player.x))
		&& !is_blocked((int)(newy), (int)(pc()->player.x + check))
		&& !is_blocked((int)(newy + check), (int)(pc()->player.x + check)))
		pc()->player.y = newy;
}

void	move_player(void)
{
	float	newx;
	float	newy;

	calculate_player_values(&newx, &newy);
	if (pc()->button.w)
	{
		newx += pc()->player.dir_x * pc()->player.move_speed;
		newy += pc()->player.dir_y * pc()->player.move_speed;
	}
	if (pc()->button.s)
	{
		newx -= pc()->player.dir_x * pc()->player.move_speed;
		newy -= pc()->player.dir_y * pc()->player.move_speed;
	}
	if (pc()->button.a)
	{
		newx += pc()->player.dir_y * pc()->player.move_speed;
		newy -= pc()->player.dir_x * pc()->player.move_speed;
	}
	if (pc()->button.d)
	{
		newx -= pc()->player.dir_y * pc()->player.move_speed;
		newy += pc()->player.dir_x * pc()->player.move_speed;
	}
	check_collision(newx, newy);
}
