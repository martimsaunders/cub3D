/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_sprite_rendering.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 15:05:32 by praders           #+#    #+#             */
/*   Updated: 2025/11/04 15:21:00 by mateferr         ###   ########.fr       */
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
	return;
}

void	sort_enemies(void)
{
	int		i;
	int		j;
	t_sprite	temp;

	i = -1;
	while (++i < pc()->enemy_count - 1)
	{
		j = -1;
		while (++j < pc()->enemy_count - i - 1)
		{
			if (pc()->enemies[j].distance < pc()->enemies[j + 1].distance)
			{
				temp = pc()->enemies[j];
				pc()->enemies[j] = pc()->enemies[j + 1];
				pc()->enemies[j + 1] = temp;	
			}
		}
	}
}

void	draw_sprite_columns(t_rend rend, t_tex tex, float zbuffer[WIDTH])
{
	tex.x = rend.draw_start_x - 1;
	while (++tex.x < rend.draw_end_x)
	{
		tex.texx = (tex.x - (-rend.sprite_width / 2 + rend.sprite_screen_x)) * pc()->image.enemy.width / rend.sprite_width;
		if (tex.x >= 0 && tex.x < WIDTH && rend.transform_y < zbuffer[tex.x])
		{
			tex.y = rend.draw_start_y - 1;
			while (++tex.y < rend.draw_end_y)
			{
				tex.sprite_y_pos = tex.y * 256 - HEIGHT * 128 + rend.sprite_height * 128;
				tex.texy = ((tex.sprite_y_pos * pc()->image.enemy.height) / rend.sprite_height) / 256;
				tex.index = tex.texy * pc()->image.enemy.line_lenght + tex.texx * (pc()->image.enemy.bpp / 8);
				tex.color = *(int *)(pc()->image.enemy.addr + tex.index);
				if ((tex.color & 0x00FFFFFF) != 0)
					put_brightness(NULL, &tex, &rend, 0);
			}
		}
	}
}

int	set_rend_values(t_sprite *enemy, t_rend *rend)
{
	rend->spritex = enemy->x - pc()->player.x;
	rend->spritey = enemy->y - pc()->player.y;
	rend->invdet = 1.0 / (pc()->player.plane_x * pc()->player.dir_y - pc()->player.dir_x * pc()->player.plane_y);
	rend->transform_x = rend->invdet * (pc()->player.dir_y * rend->spritex - pc()->player.dir_x * rend->spritey);
	rend->transform_y = rend->invdet * (-pc()->player.plane_y * rend->spritex + pc()->player.plane_x * rend->spritey);
	if (rend->transform_y <= 0.1)
		return (0);
	rend->sprite_screen_x = (int)((WIDTH / 2) * (1 + rend->transform_x / rend->transform_y));
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
	return (1);
}

void	sprite_rendering(float zbuffer[WIDTH])
{
	int		i;
	t_tex	tex;
	t_rend	rend;
	t_sprite	*enemy;

	i = 0;
	sort_enemies();
	ft_memset(&tex, 0, sizeof(t_tex));
	ft_memset(&rend, 0, sizeof(t_rend));
	while (i < pc()->enemy_count)
	{
		enemy = &pc()->enemies[i];
		if (set_rend_values(enemy, &rend))
			draw_sprite_columns(rend, tex, zbuffer);
		i++;
	}
}
