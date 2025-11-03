/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_ray_cast_cf.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: praders <praders@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 11:10:23 by mprazere          #+#    #+#             */
/*   Updated: 2025/11/03 11:31:09 by praders          ###   ########.fr       */
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

void	draw_ceiling_floor(t_ray ray, int x)
{
	int		y;
	float	distance;
	int		horizon;
	int		color;

	y = 0;
	horizon = HEIGHT / 2;
	while (y < ray.drawstart)
	{
		distance = (float)HEIGHT / (2.0 * abs(horizon - y) + 1);
		color = put_brightness_cf(pc()->image.ceiling, distance);
		put_pixel(x, y++, color);
	}
	y = ray.drawend + 1;
	while (y <= HEIGHT)
	{
		distance = (float)HEIGHT / (2.0 * abs(y - horizon) + 1);
		color = put_brightness_cf(pc()->image.floor, distance);
		put_pixel(x, y++, color);
	}
}
