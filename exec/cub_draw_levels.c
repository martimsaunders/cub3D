/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_draw_levels.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 12:03:35 by praders           #+#    #+#             */
/*   Updated: 2025/11/14 13:27:08 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	lvls_10_end_draw(int x, int y)
{
	if ((x >= 1001 && x <= 1204) && (y >= 320 && y <= 525))
		mlx_put_image_to_window(pc()->mlx, pc()->win,
			pc()->image.train[9].image, 0, 0);
	else if ((x >= 525 && x <= 755) && (y >= 549 && y <= 672))
		mlx_put_image_to_window(pc()->mlx, pc()->win,
			pc()->image.train[11].image, 0, 0);
	else
		mlx_put_image_to_window(pc()->mlx, pc()->win,
			pc()->image.train[10].image, 0, 0);
}

static void	lvls_7_9_draw(int x, int y)
{
	if ((x >= 307 && x <= 511) && (y >= 320 && y <= 525))
		mlx_put_image_to_window(pc()->mlx, pc()->win,
			pc()->image.train[6].image, 0, 0);
	else if ((x >= 539 && x <= 742) && (y >= 320 && y <= 525))
		mlx_put_image_to_window(pc()->mlx, pc()->win,
			pc()->image.train[7].image, 0, 0);
	else if ((x >= 770 && x <= 973) && (y >= 320 && y <= 525))
		mlx_put_image_to_window(pc()->mlx, pc()->win,
			pc()->image.train[8].image, 0, 0);
	else
		lvls_10_end_draw(x, y);
}

static void	lvls_4_6_draw(int x, int y)
{
	if ((x >= 770 && x <= 973) && (y >= 69 && y <= 275))
		mlx_put_image_to_window(pc()->mlx, pc()->win,
			pc()->image.train[3].image, 0, 0);
	else if ((x >= 1001 && x <= 1204) && (y >= 69 && y <= 275))
		mlx_put_image_to_window(pc()->mlx, pc()->win,
			pc()->image.train[4].image, 0, 0);
	else if ((x >= 74 && x <= 280) && (y >= 320 && y <= 525))
		mlx_put_image_to_window(pc()->mlx, pc()->win,
			pc()->image.train[5].image, 0, 0);
	else
		lvls_7_9_draw(x, y);
}

void	draw_lvls_menu(void)
{
	int	x;
	int	y;

	x = pc()->player.mousex;
	y = pc()->player.mousey;
	if ((x >= 74 && x <= 280) && (y >= 69 && y <= 275))
		mlx_put_image_to_window(pc()->mlx, pc()->win,
			pc()->image.train[0].image, 0, 0);
	else if ((x >= 307 && x <= 511) && (y >= 69 && y <= 275))
		mlx_put_image_to_window(pc()->mlx, pc()->win,
			pc()->image.train[1].image, 0, 0);
	else if ((x >= 539 && x <= 742) && (y >= 69 && y <= 275))
		mlx_put_image_to_window(pc()->mlx, pc()->win,
			pc()->image.train[2].image, 0, 0);
	else
		lvls_4_6_draw(x, y);
	return ;
}
