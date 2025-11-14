/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_set_values.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 13:36:29 by mateferr          #+#    #+#             */
/*   Updated: 2025/11/14 13:36:30 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	parse_set_player(t_parse *f)
{
	int		x;
	int		y;
	char	c;

	parse_find_player(f, &x, &y);
	c = f->map[y][x];
	if (c == 'E')
		pc()->player.angle = PI * 2;
	if (c == 'N')
		pc()->player.angle = PI * 1.5;
	if (c == 'O')
		pc()->player.angle = PI;
	if (c == 'S')
		pc()->player.angle = PI * 0.5;
	pc()->player.x = x + 0.25;
	pc()->player.y = y + 0.25;
}

bool	parse_set_doors(t_parse *f)
{
	int		x;
	int		y;
	int		i;
	t_door	*d;

	d = ft_calloc(f->door_count, sizeof(t_door));
	if (!d)
		return (perror("Error\n"), false);
	i = 0;
	y = -1;
	while (f->map[++y])
	{
		x = -1;
		while (f->map[y][++x])
		{
			if (f->map[y][x] == 'd')
			{
				d[i].y = y + 0.25;
				d[i++].x = x + 0.25;
			}
		}
	}
	pc()->door = d;
	return (true);
}

bool	parse_set_enemies(t_parse *f)
{
	int			x;
	int			y;
	int			i;
	t_sprite	*e;

	e = ft_calloc(f->enemy_count, sizeof(t_sprite));
	if (!e)
		return (perror("Error\n"), false);
	i = 0;
	y = -1;
	while (f->map[++y])
	{
		x = -1;
		while (f->map[y][++x])
		{
			if (f->map[y][x] == 'e')
			{
				e[i].y = y + 0.25;
				e[i++].x = x + 0.25;
			}
		}
	}
	pc()->enemies = e;
	return (true);
}

bool	parse_set_coins(t_parse *f)
{
	int			x;
	int			y;
	int			i;
	t_sprite	*c;

	c = ft_calloc(f->coin_count, sizeof(t_sprite));
	if (!c)
		return (perror("Error\n"), false);
	i = 0;
	y = -1;
	while (f->map[++y])
	{
		x = -1;
		while (f->map[y][++x])
		{
			if (f->map[y][x] == 'c')
			{
				c[i].is_coin = 1;
				c[i].y = y + 0.25;
				c[i++].x = x + 0.25;
			}
		}
	}
	pc()->coin = c;
	return (true);
}

bool	parse_set_icons_values(t_parse *f)
{
	parse_set_player(f);
	if (!parse_set_doors(f))
		return (false);
	if (!parse_set_enemies(f))
		return (false);
	if (!parse_set_coins(f))
		return (false);
	return (true);
}
