#include "../../cub3d.h"

void	minimap_put_pixel(t_minimap *mm, int x, int y, int color)
{
	put_pixel(mm->radius + x, HUD + mm->radius + y, color);
}

void	minimap_init(t_minimap *mm)
{
	mm->radius = MINIMAP - 2;
	mm->angle = pc()->player.angle + PI / 2;
	mm->player = pc()->player;
	mm->map = pc()->map;
	mm->map_h = parse_map_height(pc()->map);
	mm->char_size = BLOCK / 4;
	mm->coin_count = pc()->coin_count;
	mm->coins = pc()->coin;
	mm->enemy_count = pc()->enemy_count;
	mm->enemies = pc()->enemies;
}

bool	minimap_is_inside_circle(int x, int y, int radius)
{
	if (x * x + y * y <= radius * radius)
		return (true);
	return (false);
}

void	minimap_world_coords(t_minimap *mm, int x, int y)
{
	mm->rotx = x * cos(mm->angle) - y * sin(mm->angle);
	mm->roty = x * sin(mm->angle) + y * cos(mm->angle);
	mm->worldx = mm->player.x + 0.25 + mm->rotx / BLOCK;
	mm->worldy = mm->player.y + 0.25 + mm->roty / BLOCK;
	mm->mapx = (int)floor(mm->worldx);
	mm->mapy = (int)floor(mm->worldy);
}

void	draw_minimap(void)
{
	t_minimap	mm;
	int			x;
	int			y;

	minimap_init(&mm);
	y = -(mm.radius + 2) - 1;
	while (++y <= mm.radius)
	{
		x = -(mm.radius + 2) - 1;
		while (++x <= mm.radius)
		{
			if (!minimap_is_inside_circle(x, y, mm.radius))
			{
				if (minimap_is_inside_circle(x, y, mm.radius + 2))
					minimap_draw_outside(&mm, x, y);
				continue ;
			}
			minimap_world_coords(&mm, x, y);
			if (!minimap_is_inside_map(&mm))
				minimap_draw_outside(&mm, x, y);
			else
				minimap_draw_block(&mm, x, y);
		}
	}
	minimap_draw_all_icons(&mm);
}
