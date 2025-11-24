/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_clicks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 13:34:47 by mateferr          #+#    #+#             */
/*   Updated: 2025/11/24 12:04:40 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

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
	else if (pc()->mode == GAME_MENU)
		game_menu_click(x, y);
	return (0);
}

void	main_menu_click(int x, int y)
{
	if ((x >= 81 && x <= 283) && (y >= 450 && y <= 611))
		pc()->mode = GAME_MENU;
	else if ((x >= 382 && x <= 595) && (y >= 450 && y <= 611))
	{
		if (!avl_mode_init(pc()->argc, pc()->argv))
			destroy_everything(1);
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

void	game_menu_click(int x, int y)
{
	if ((x >= 420 && x <= 651) && (y >= 518 && y <= 644))
		pc()->mode = MENU;
	else if ((x >= 703 && x <= 872) && (y >= 518 && y <= 644))
	{
		pc()->death_count = 0;
		pc()->current_level = 1;
		lvl_mode_init();
		pc()->mode = GAME;
	}
}
