/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_sprite_rendering_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: praders <praders@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:09:51 by praders           #+#    #+#             */
/*   Updated: 2025/11/10 15:21:16 by praders          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	distance(t_sprite *enemy)
{
	float	dx;
	float	dy;

	dx = enemy->x - pc()->player.x;
	dy = enemy->y - pc()->player.y;
	enemy->distance = sqrt(dx * dx + dy * dy);
	return ;
}

void		set_rend_values2(t_rend *rend)
{
	rend->sprite_screen_x = (int)((WIDTH / 2) * (1 + rend->transform_x
		/ rend->transform_y));
	rend->sprite_height = abs((int)(HEIGHT / rend->transform_y));
	rend->sprite_width = abs((int)(HEIGHT / rend->transform_y));
	rend->draw_start_y = -rend->sprite_height / 2 + HEIGHT / 2;
	if (rend->draw_start_y < 0)
		rend->draw_start_y = 0;
	rend->draw_end_y = rend->sprite_height / 2 + HEIGHT / 2;
	if (rend->draw_end_y >= HEIGHT)
		rend->draw_end_y = HEIGHT - 1;
	rend->draw_start_x = -rend->sprite_width / 2 + rend->sprite_screen_x;
	if (rend->draw_start_x < 0)
		rend->draw_start_x = 0;
	rend->draw_end_x = rend->sprite_width / 2 + rend->sprite_screen_x;
	if (rend->draw_end_x >= WIDTH)
		rend->draw_end_x = WIDTH - 1;
}