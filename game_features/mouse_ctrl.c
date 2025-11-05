#include "../cub3d.h"

int	mouse_click(int button, int x, int y)
{
	if (button != 1)
		return (0);
	if (pc()->mode == MENU)
		main_menu_click(x, y);
	else if (pc()->mode == CTRLS)
		ctrls_menu_click(x, y);
	else if (pc()->mode == LVLS)
		lvls_menu_click(x, y);
	else if (pc()->mode == PAUSE)
		pause_menu_click(x, y);
	return (0);
}

int mouse_out() // verificar necessidade de proteção para clicks fora da tela
{
    if (pc()->mode == GAME || pc()->mode == EVAL)
        pc()->mouse_in_win = 0;
    return (0);
}

void mouse_cam_move(int x) //implementar fps mecanic
{
    int dx;
    float sens;

    sens = 0.001;
    if (!pc()->mouse_in_win)
    {
        pc()->player.mousex = x;
        pc()->mouse_in_win = 1;
        return ;
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
}

int mouse_move(int x, int y)
{
    if (pc()->mode == GAME || pc()->mode == EVAL)
        mouse_cam_move(x);
    else if (pc()->mode == MENU)
		mouse_move_main_menu(x, y);
	else if (pc()->mode == CTRLS)
		mouse_move_ctrls_menu(x, y);
	else if (pc()->mode == LVLS)
		mouse_move_lvls_menu(x, y);
	else if (pc()->mode == PAUSE)
		mouse_move_pause_menu(x, y);
    return (0);
}

void mouse_move_pause_menu(int x, int y)
{
	(void)x;
	(void)y;
	return ;
}
void mouse_move_lvls_menu(int x, int y)
{
	(void)x;
	(void)y;
	return ;
}
void mouse_move_ctrls_menu(int x, int y)
{
	(void)x;
	(void)y;
	return ;
}
void mouse_move_main_menu(int x, int y)
{
	(void)x;
	(void)y;
	return ;
}