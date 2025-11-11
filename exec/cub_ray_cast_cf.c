/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_ray_cast_cf.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 11:10:23 by mprazere          #+#    #+#             */
/*   Updated: 2025/11/11 12:18:09 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	put_brightness_cf(int color, float distance)
{
	float	brightness;
	int		darker_color;

	brightness = 1.0 - (distance / 10.0);
	if (brightness < 0.2)
		brightness = 0.2;
	darker_color = ((int)(((color >> 16) & 0xFF)
				* brightness) << 16) | ((int)(((color >> 8) & 0xFF)
				* brightness) << 8) | (int)((color & 0xFF) * brightness);
	return (darker_color);
}

int		get_floor_color(float floor_x, float floor_y)
{
	int mapx;
	int mapy;
	char tile;
	int checker;

	if (pc()->mode == EVAL)
		return (pc()->image.floor);
	mapx = (int)(floor_x + 0.25);
	mapy = (int)(floor_y + 0.25);
	tile = pc()->map[mapy][mapx];
	if (tile == 'g' || tile == 'n' || tile == 'p')
		return (0xBEFDB6);
	checker = (mapx + mapy) % 2;
	if (checker == 0)
		return (0xFFFFFF);
	return (0xE6E6FA);
	
}

void	draw_ceiling_floor(t_ray ray, int x)
{
	int		y;
	int		horizon;
	int		color;
	float	row_distance;
	float	floor_x;
	float	floor_y;

	y = 0;
	horizon = HEIGHT / 2;
	while (y < ray.drawstart)
	{
		row_distance = (float)HEIGHT / (2.0 * abs(horizon - y) + 1);
		if (pc()->mode == EVAL)
			color = put_brightness_cf(pc()->image.ceiling, row_distance);
		else
			color = put_brightness_cf(0x00ddff, row_distance);
		put_pixel(x, y++, color);
	}
	y = ray.drawend + 1;
	while (y <= HEIGHT)
	{
		row_distance = (float)HEIGHT / (2.0 * abs(y - horizon) + 1);
		floor_x = pc()->player.x + ray.raydirx * row_distance;
		floor_y = pc()->player.y + ray.raydiry * row_distance;
		color = get_floor_color(floor_x, floor_y);
		color = put_brightness_cf(color, row_distance);
		put_pixel(x, y++, color);
	}
}
