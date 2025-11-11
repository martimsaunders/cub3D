#include "../../cub3d.h"



// void hud_rotated_compass(t_hud *h, int x, int y, int color)
// {
//     int cx;
//     int cy;
//     double rotx;
//     double roty;
//     double wx;
//     double wy;
    
//     cx = WIDTH - h->radius;
//     cy = HUD + h->radius;
//     rotx = x * cos(h->angle) - y * sin(h->angle);
//     roty = x * sin(h->angle) + y * cos(h->angle);
//     wx = cx + rotx;
//     wy = cy + roty;
//     if (x*x + y*y > 37*37)
//         put_pixel(wx, wy, color);
//     else
//         put_pixel(cx + x, cy + y, color);

// }

// void hud_draw_compass(t_hud *h)
// {
//     int x;
//     int y;
//     int color;

//     y = -h->radius - 1;
//     while (++y < h->radius)
//     {
//         x = -h->radius - 1;
//         while (++x <= h->radius)
//         {
//             color = hud_get_pixel_color(h->compass, h->radius + x, h->radius + y);
//             hud_rotated_compass(h, x, y, color);
//         }
//     }
    
// }
