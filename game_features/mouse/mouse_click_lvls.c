#include "../../cub3d.h"

static void	lvls_10_end_click(int x, int y)
{
    if ((x >= 1001 && x <= 1204) && (y >= 320 && y <= 525))
	{
		pc()->current_level = 10;
		lvl_mode_init();
		pc()->mode = LVLS_GAME;
	}
	else if ((x >= 525 && x <= 755) && (y >= 549 && y <= 672))
		pc()->mode = MENU;
	else
		return ;
}

static void	lvls_7_9_click(int x, int y)
{
    if ((x >= 307 && x <= 511) && (y >= 320 && y <= 525))
	{
		pc()->current_level = 7;
		lvl_mode_init();
		pc()->mode = LVLS_GAME;
	}
	else if ((x >= 539 && x <= 742) && (y >= 320 && y <= 525))
	{
		pc()->current_level = 8;
		lvl_mode_init();
		pc()->mode = LVLS_GAME;
	}
	else if ((x >= 770 && x <= 973) && (y >= 320 && y <= 525))
	{
		pc()->current_level = 9;
		lvl_mode_init();
		pc()->mode = LVLS_GAME;
	}
	else
		lvls_10_end_click(x, y);
}

static void	lvls_4_6_click(int x, int y)
{
    if ((x >= 770 && x <= 973) && (y >= 69 && y <= 275))
	{
		pc()->current_level = 4;
		lvl_mode_init();
		pc()->mode = LVLS_GAME;
	}
	else if ((x >= 1001 && x <= 1204) && (y >= 69 && y <= 275))
	{
		pc()->current_level = 5;
		lvl_mode_init();
		pc()->mode = LVLS_GAME;
	}
	else if ((x >= 74 && x <= 280) && (y >= 320 && y <= 525))
	{
		pc()->current_level = 6;
		lvl_mode_init();
		pc()->mode = LVLS_GAME;
	}
    else
        lvls_7_9_click(x, y);
}

void	lvls_menu_click(int x, int y)
{
	if ((x >= 74 && x <= 280) && (y >= 69 && y <= 275))
	{
		pc()->current_level = 1;
		lvl_mode_init();
		pc()->mode = LVLS_GAME;
	}
	else if ((x >= 307 && x <= 511) && (y >= 69 && y <= 275))
	{
		pc()->current_level = 2;
		lvl_mode_init();
		pc()->mode = LVLS_GAME;
	}
	else if ((x >= 539 && x <= 742) && (y >= 69 && y <= 275))
	{
		pc()->current_level = 3;
		lvl_mode_init();
		pc()->mode = LVLS_GAME;
	}
	else
		lvls_4_6_click(x, y);
}
