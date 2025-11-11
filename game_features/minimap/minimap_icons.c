#include "../../cub3d.h"

void	minimap_draw_player(t_minimap *mm)
{
	int	x;
	int	y;

	y = -mm->char_size - 1;
	while (++y <= mm->char_size)
	{
		x = -mm->char_size - 1;
		while (++x <= mm->char_size)
		{
			if (y == -mm->char_size || y == mm->char_size || x == -mm->char_size
				|| x == mm->char_size)
				minimap_draw_outside(mm, x, y);
			else
				minimap_put_pixel(mm, x, y, 0xff0000);
		}
	}
}

void	minimap_icon_coords(t_minimap *mm, t_sprite icon)
{
	double	distx;
	double	disty;

	distx = icon.x - mm->player.x;
	disty = icon.y - mm->player.y;
	mm->rotx = distx * cos(-mm->angle) - disty * sin(-mm->angle);
	mm->roty = distx * sin(-mm->angle) + disty * cos(-mm->angle);
	mm->mapx = (int)(mm->rotx * BLOCK);
	mm->mapy = (int)(mm->roty * BLOCK);
}

void	minimap_draw_icon(t_minimap *mm, int color)
{
	int	x;
	int	y;
	int	px;
	int	py;

	y = -mm->char_size - 1;
	while (++y <= mm->char_size)
	{
		x = -mm->char_size - 1;
		while (++x <= mm->char_size)
		{
			if (!minimap_is_inside_circle(x, y, mm->char_size))
				continue ;
			px = mm->mapx + x;
			py = mm->mapy + y;
			if (!minimap_is_inside_circle(px, py, mm->radius))
				continue ;
			if (!minimap_is_inside_circle(x, y, mm->char_size - 2))
				minimap_draw_outside(mm, px, py);
			else
				minimap_put_pixel(mm, px, py, color);
		}
	}
}

void	minimap_draw_all_icons(t_minimap *mm)
{
	int	i;

	i = -1;
	while (++i < mm->coin_count)
	{
		minimap_icon_coords(mm, mm->coins[i]);
		if (!minimap_is_inside_circle(mm->mapx, mm->mapy, mm->radius + 2)
			|| mm->coins[i].state)
			continue ;
		minimap_draw_icon(mm, 0xF4DC0B);
	}
	i = -1;
	while (++i < mm->enemy_count)
	{
		minimap_icon_coords(mm, mm->enemies[i]);
		if (!minimap_is_inside_circle(mm->mapx, mm->mapy, mm->radius + 2))
			continue ;
		minimap_draw_icon(mm, 0x0003D1);
	}
	minimap_draw_player(mm);
}
