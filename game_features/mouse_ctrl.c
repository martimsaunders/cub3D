#include "../cub3d.h"

int mouse_out()
{
    pc()->mouse_in_win = 0;
    return (0);
}

int mouse_cam_move(int x, int y)
{
    int dx;
    float sens;

    (void)y;
    sens = 0.005;
    if (!pc()->mouse_in_win)
    {
        pc()->player.mousex = x;
        pc()->mouse_in_win = 1;
        return (0);
    }
    dx = x - pc()->player.mousex;
    pc()->player.mousex = x;
	pc()->player.angle += dx * sens;
	if (pc()->player.angle > 2 * PI)
		pc()->player.angle = 0;
	if (pc()->player.angle < 0)
		pc()->player.angle = 2 * PI;
	pc()->player.dir_x = cos(pc()->player.angle);
	pc()->player.dir_y = sin(pc()->player.angle);
	pc()->player.plane_x = -pc()->player.dir_y * FOV;
	pc()->player.plane_y = pc()->player.dir_x * FOV;
    return (0);
}
