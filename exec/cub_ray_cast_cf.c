/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_ray_cast_cf.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 11:10:23 by mprazere          #+#    #+#             */
/*   Updated: 2025/11/11 18:05:19 by mprazere         ###   ########.fr       */
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

int	get_floor_color(int mapx, int mapy, float distance, t_ray ray)
{
	float	floorx;
	float	floory;
	char	tile;
	int		checker;

	if (pc()->mode == EVAL)
		return (pc()->image.floor);
	floorx = pc()->player.x + ray.raydirx * distance;
	floory = pc()->player.y + ray.raydiry * distance;
	mapx = (int)(floorx + 0.25);
	mapy = (int)(floory + 0.25);
	tile = pc()->map[mapy][mapx];
	if (tile == 'g' || tile == 'n' || tile == 'p' || tile == 'N')
		return (0xBEFDB6);
	else if (tile == 's' || tile == 'o' || tile == 't' || tile == 'r')
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
		color = get_floor_color(0, 0, row_distance, ray);
		color = put_brightness_cf(color, row_distance);
		put_pixel(x, y++, color);
	}
}
