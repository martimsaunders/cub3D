/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 12:11:54 by mateferr          #+#    #+#             */
/*   Updated: 2025/11/03 13:55:13 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	draw_player(t_mmap *m)
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

bool	is_wall_edge(int mapx, int mapy, t_mmap *m)
{
	if (m->relx == 0 && (mapx == 0 || pc()->map[mapy][mapx - 1] != '1'))
		return (true);
	if (m->relx == BLOCK - 1 && (pc()->map[mapy][mapx + 1] == '\0'
		|| pc()->map[mapy][mapx + 1] != '1'))
		return (true);
	if (m->rely == 0 && (mapy == 0 || pc()->map[mapy - 1][mapx] != '1'))
		return (true);
	if (m->rely == BLOCK - 1)
	{
		if (pc()->map[mapy + 1] == NULL)
			return (true);
		if (mapx < (int)ft_strlen(pc()->map[mapy + 1]))
			if (pc()->map[mapy + 1][mapx] != '1')
				return (true);
	}
	return (false);
}

// pixel x position on the block
// pixel y position on the block
// pixel x relative position on the grid
// pixel y relative position on the grid
static void	put_floor_wall_pixel(int x, int y, t_mmap *m)
{
	int	mapy;
	int	mapx;

	mapy = m->mapy;
	mapx = m->mapx;
	if (pc()->map[mapy][mapx] == '1')
	{
		m->frac_x = m->world_x - floor(m->world_x);
		m->frac_y = m->world_y - floor(m->world_y);
		m->relx = (int)(m->frac_x * BLOCK);
		m->rely = (int)(m->frac_y * BLOCK);
		if (is_wall_edge(mapx, mapy, m))
			return (put_pixel(m->map_radius + x, m->map_radius + y, 0x000000));
		return (put_pixel(m->map_radius + x, m->map_radius + y, 0x7B68EE));
	}
	if ((mapx + mapy) % 2 == 0)
		return (put_pixel(m->map_radius + x, m->map_radius + y, 0xFFFFFF));
	return (put_pixel(m->map_radius + x, m->map_radius + y, 0xE6E6FA));
}

// posição pixel relativo a player e rotação da camera
// coordenadas na grid do pixel
static void	map_element_draw(int x, int y, t_mmap *m)
{
	m->angle = pc()->player.angle + PI / 2;
	m->rotx = x * cos(m->angle) - y * sin(m->angle);
	m->roty = x * sin(m->angle) + y * cos(m->angle);
	m->world_x = pc()->player.x + 0.25 + m->rotx / BLOCK;
	m->world_y = pc()->player.y + 0.25 + m->roty / BLOCK;
	m->mapx = (int)floor(m->world_x);
	m->mapy = (int)floor(m->world_y);
	if (m->mapy >= 0 && m->mapy < ps()->map_h && m->mapx >= 0
		&& m->mapx < (int)ft_strlen(pc()->map[m->mapy]))
	{
		put_floor_wall_pixel(x, y, m);
	}
	else
		put_pixel(m->map_radius + x, m->map_radius + y, 0x000000);
}

void	draw_mini_map(void)
{
	int		x;
	int		y;
	t_mmap	m;

	m.map_radius = HEIGHT / 6;
	y = -m.map_radius;
	while (y <= m.map_radius)
	{
		x = -m.map_radius;
		while (x <= m.map_radius)
		{
			if (x * x + y * y <= m.map_radius * m.map_radius)
			{
				if (x * x + y * y > (m.map_radius - 2) * (m.map_radius - 2))
					put_pixel(m.map_radius + x, m.map_radius + y, 0x000000);
				else
					map_element_draw(x, y, &m);
			}
			x++;
		}
		y++;
	}
	draw_player(&m);
}
