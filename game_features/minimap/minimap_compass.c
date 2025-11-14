/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_compass.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 13:33:17 by mateferr          #+#    #+#             */
/*   Updated: 2025/11/14 13:34:09 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static bool	minimap_get_rotated_pixel(t_minimap *mm, int dx, int dy)
{
	double	rotx;
	double	roty;
	double	srcx;
	double	srcy;

	rotx = dx * cos(mm->angle) - dy * sin(mm->angle);
	roty = dx * sin(mm->angle) + dy * cos(mm->angle);
	srcx = rotx + mm->radius;
	srcy = roty + mm->radius;
	if (srcx < 0 || srcx >= mm->compass.width || srcy < 0
		|| srcy >= mm->compass.height)
		return (false);
	mm->imgx = (int)floor(srcx);
	mm->imgy = (int)floor(srcy);
	return (true);
}

void	minimap_draw_compass(t_minimap *mm)
{
	int	win_cx;
	int	win_cy;
	int	winy;
	int	winx;
	int	color;

	win_cx = mm->radius;
	win_cy = HUD + mm->radius;
	winy = win_cy - mm->radius - 1;
	while (++winy <= win_cy + mm->radius)
	{
		winx = win_cx - mm->radius - 1;
		while (++winx <= win_cx + mm->radius)
		{
			if (!minimap_get_rotated_pixel(mm, winx - win_cx, winy - win_cy))
				continue ;
			color = hud_get_pixel_color(mm->compass, mm->imgx, mm->imgy);
			if (color != 0xFFFFFF)
				put_pixel(winx, winy, color);
		}
	}
}
