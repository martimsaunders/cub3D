#include "../../cub3d.h"

void	hud_get_image_pixel(t_hud *h, int dx, int dy)
{
	double	rotx;
	double	roty;
	double	srcx;
	double	srcy;

	rotx = dx * cos(h->angle) - dy * sin(h->angle);
	roty = dx * sin(h->angle) + dy * cos(h->angle);
	srcx = rotx + h->radius;
	srcy = roty + h->radius;
	if (srcx < 0 || srcx >= h->compass.width || srcy < 0
		|| srcy >= h->compass.height)
		return ;
	h->imgx = (int)floor(srcx);
	h->imgy = (int)floor(srcy);
}

void	hud_draw_compass(t_hud *h)
{
	int	win_cx;
	int	win_cy;
	int	winy;
	int	winx;
	int	color;

	win_cx = WIDTH - h->radius;
	win_cy = HUD + h->radius;
	winy = win_cy - h->radius - 1;
	while (++winy < win_cy + h->radius)
	{
		winx = win_cx - h->radius - 1;
		while (++winx < win_cx + h->radius)
		{
			hud_get_image_pixel(h, winx - win_cx, winy - win_cy);
			color = hud_get_pixel_color(h->compass, h->imgx, h->imgy);
			if (color != 0xFFFFFF)
				put_pixel(winx, winy, color);
		}
	}
}

// desenhar bussola maior em minimapa