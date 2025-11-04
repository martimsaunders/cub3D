/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:21:32 by mateferr          #+#    #+#             */
/*   Updated: 2025/11/04 14:33:30 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_player(t_mmap *m)
{
	int	player_radius;
	int	x;
	int	y;

	player_radius = BLOCK / 4;
	y = -player_radius - 1;
	while (++y <= player_radius)
	{
		x = -player_radius - 1;
		while (++x <= player_radius)
		{
			if (y == -player_radius || y == player_radius || x == -player_radius
				|| x == player_radius)
				put_pixel(m->map_radius + x, m->map_radius + y, 0x000000);
			else
				put_pixel(m->map_radius + x, m->map_radius + y, 0xff0000);
		}
	}
}

static void	enemy_put_pixel(t_mmap *m, int e_radius)
{
	int	x;
	int	y;

	y = -e_radius - 1;
	while (++y <= e_radius)
	{
		x = -e_radius - 1;
		while (++x <= e_radius)
		{
			if (x * x + y * y > e_radius * e_radius)
				continue ;
			m->pxlex = m->mapx + x;
			m->pxley = m->mapy + y;
			m->difex = m->pxlex - m->map_radius;
			m->difey = m->pxley - m->map_radius;
			if (m->difex * m->difex + m->difey * m->difey > m->map_radius
				* m->map_radius)
				continue ;
			if (x * x + y * y > (e_radius - 2) * (e_radius - 2))
				put_pixel(m->pxlex, m->pxley, 0x000000);
			else
				put_pixel(m->pxlex, m->pxley, 0x0003D1);
		}
	}
}

void	draw_enemies(t_mmap *m)
{
	int	i;

	i = -1;
	while (++i < pc()->enemy_count)
	{
		m->difx = pc()->enemies[i].x - pc()->player.x;
		m->dify = pc()->enemies[i].y - pc()->player.y;
		m->rotx = m->difx * cos(-m->angle) - m->dify * sin(-m->angle);
		m->roty = m->difx * sin(-m->angle) + m->dify * cos(-m->angle);
		m->pxlx = m->rotx * BLOCK;
		m->pxly = m->roty * BLOCK;
		m->mapx = (int)(m->map_radius + m->pxlx);
		m->mapy = (int)(m->map_radius + m->pxly);
		m->difex = m->mapx - m->map_radius;
		m->difey = m->mapy - m->map_radius;
		if (m->difex * m->difex + m->difey * m->difey > m->map_radius
			* m->map_radius)
			continue ;
		enemy_put_pixel(m, BLOCK / 4);
	}
}
