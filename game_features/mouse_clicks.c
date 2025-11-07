#include "../cub3d.h"

void	main_menu_click(int x, int y)
{
	if ((x >= 81 && x <= 283) && (y >= 450 && y <= 611))
		pc()->mode = GAME_MENU;
	else if ((x >= 382 && x <= 595) && (y >= 450 && y <= 611))
    {
        if (!avl_mode_init(pc()->argc, pc()->argv))
            exit(1);
            // destroy_everything(1);
		pc()->mode = EVAL;
    }
	else if ((x >= 686 && x <= 904) && (y >= 450 && y <= 611))
		pc()->mode = LVLS;
	else if ((x >= 1003 && x <= 1208) && (y >= 450 && y <= 611))
		pc()->mode = CTRLS;
}
void	ctrls_menu_click(int x, int y)
{
	if (x >= 527 && x <= 752 && y >= 520 && y <= 639)
        pc()->mode = MENU;
}
void	lvls_menu_click(int x, int y)
{
	printf("lvls menu\nx- %i, y- %i\n", x, y);
}
void	game_menu_click(int x, int y)
{
	if ((x >= 420 && x <= 651) && (y >= 518 && y <= 644))
		pc()->mode = MENU;
	else if ((x >= 703 && x <= 872) && (y >= 518 && y <= 644))
		pc()->mode = GAME;
}