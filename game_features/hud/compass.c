#include "../../cub3d.h"

void hud_rotated_compass(t_hud *h, int radius, int x, int y)
{
    int cx;
    int cy;
    int color;
    double rotx;
    double roty;

    cx = WIDTH - radius;
    cy = HUD + radius;
    color = hud_get_pixel_color(h->compass, radius + x, radius + y);
    if (color != 0xFFFFFF)
    {
        if (x*x + y*y > 37*37)
        {
            rotx = x * cos(h->angle) - y * sin(h->angle);
            roty = x * sin(h->angle) + y * cos(h->angle);
            put_pixel(cx + rotx, cy + roty, color);
        }
        else
            put_pixel(cx + x, cy + y, color);
    }
}

void hud_draw_compass(t_hud *h)
{
    int x;
    int y;
    int radius;

    radius = h->compass.width / 2;
    y = -radius - 1;
    while (++y < radius)
    {
        x = -radius - 1;
        while (++x <= radius)
        {
            hud_rotated_compass(h, radius, x, y);
        }
    }
    
}
