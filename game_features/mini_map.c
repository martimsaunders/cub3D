/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 12:55:51 by mateferr          #+#    #+#             */
/*   Updated: 2025/11/06 12:55:53 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	is_edge(int mapx, int mapy, t_map *m)
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

static void	put_coin_pixel(int x, int y, t_map *m, double radius)
{
	double	val;
	double	rr;
	double	irr;

	rr = radius * radius;
	irr = (radius - 2) * (radius - 2);
	m->disx = m->world_x - (m->mapx + 0.5);
	m->disy = m->world_y - (m->mapy + 0.5);
	m->pxlx = m->disx * BLOCK;
	m->pxly = m->disy * BLOCK;
	val = m->pxlx * m->pxlx + m->pxly * m->pxly;
	if (val < irr)
		put_pixel(m->map_radius + x, m->map_radius + y, 0xF4DC0B);
	else if (val <= rr)
		put_pixel(m->map_radius + x, m->map_radius + y, 0x000000);
}

// convertion of the map pixel into block position
static void	put_element_pixel(int x, int y, t_map *m)
{
	int	mapy;
	int	mapx;

	mapy = m->mapy;
	mapx = m->mapx;
	if (pc()->map[mapy][mapx] == '1' || pc()->map[mapy][mapx] == 'd')
	{
		m->frac_x = m->world_x - floor(m->world_x);
		m->frac_y = m->world_y - floor(m->world_y);
		m->relx = (int)(m->frac_x * BLOCK);
		m->rely = (int)(m->frac_y * BLOCK);
		if (is_edge(mapx, mapy, m))
			put_pixel(m->map_radius + x, m->map_radius + y, 0x000000);
		else if (pc()->map[mapy][mapx] == '1')
			put_pixel(m->map_radius + x, m->map_radius + y, 0x7B68EE);
		else
			put_pixel(m->map_radius + x, m->map_radius + y, 0x752D00);
	}
	else if ((mapx + mapy) % 2 == 0)
		put_pixel(m->map_radius + x, m->map_radius + y, 0xFFFFFF);
	else
		put_pixel(m->map_radius + x, m->map_radius + y, 0xE6E6FA);
	if (pc()->map[mapy][mapx] == 'c' && !find_coin_state(mapx, mapy))
		put_coin_pixel(x, y, m, BLOCK / 4);
}

// convertion of the window pixel in map coordinates
// starting from players position and rotated
static void	put_map_pixel(int x, int y, t_map *m)
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
		put_element_pixel(x, y, m);
	}
	else
		put_pixel(m->map_radius + x, m->map_radius + y, 0x000000);
}

void	draw_mini_map(void)
{
	int		x;
	int		y;
	t_map	m;

	m.map_radius = HEIGHT / 6 - 2;
	y = -m.map_radius;
	while (y <= m.map_radius)
	{
		x = -m.map_radius;
		while (x <= m.map_radius)
		{
			if (x * x + y * y <= (m.map_radius + 2) * (m.map_radius + 2))
			{
				if (x * x + y * y > m.map_radius * m.map_radius)
					put_pixel(m.map_radius + x, m.map_radius + y, 0x000000);
				else
					put_map_pixel(x, y, &m);
			}
			x++;
		}
		y++;
	}
	draw_enemies(&m);
	draw_player(&m);
}
