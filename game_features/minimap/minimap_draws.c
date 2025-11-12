#include "../../cub3d.h"

void	minimap_draw_outside(t_minimap *mm, int x, int y)
{
	minimap_put_pixel(mm, x, y, 0x000000);
}

void	minimap_draw_floor(t_minimap *mm, int x, int y)
{
	if ((mm->mapx + mm->mapy) % 2 == 0)
		minimap_put_pixel(mm, x, y, 0xFFFFFF);
	else
		minimap_put_pixel(mm, x, y, 0xE6E6FA);
}

void	minimap_draw_block(t_minimap *mm, int x, int y)
{
    if (is_blocked_e(mm->mapy, mm->mapx, 1))
	{
		if (minimap_is_edge(mm->mapx, mm->mapy, mm))
			minimap_draw_outside(mm, x, y);
		else if (minimap_is_wall(mm, mm->mapx, mm->mapy))
			minimap_put_pixel(mm, x, y, 0x7B68EE);
		else
			minimap_put_pixel(mm, x, y, 0x752D00);
	}
	else if (minimap_is_safe(mm))
		minimap_put_pixel(mm, x, y, 0xBEFDB6);
	else
		minimap_draw_floor(mm, x, y);
}
