/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_sprite_rendering.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 15:05:32 by praders           #+#    #+#             */
/*   Updated: 2025/11/11 16:49:45 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	sort_sprites(t_sprite **sprite, int size)
{
	int			i;
	int			j;
	t_sprite	*temp;

	i = -1;
	while (++i < size - 1)
	{
		j = -1;
		while (++j < size - i - 1)
		{
			if (sprite[j]->distance < sprite[j + 1]->distance)
			{
				temp = sprite[j];
				sprite[j] = sprite[j + 1];
				sprite[j + 1] = temp;
			}
		}
	}
}

void	draw_sprite_columns(t_rend rend, t_tex tex, float *zbuffer,
		t_asset *sprite)
{
	tex.x = rend.draw_start_x - 1;
	while (++tex.x < rend.draw_end_x)
	{
		tex.texx = (tex.x - (-rend.sprite_width / 2 + rend.sprite_screen_x))
			* sprite->width / rend.sprite_width;
		if (tex.x >= 0 && tex.x < WIDTH && rend.transform_y < zbuffer[tex.x])
		{
			tex.y = rend.draw_start_y - 1;
			while (++tex.y < rend.draw_end_y)
			{
				tex.sprite_y_pos = tex.y * 256 - HEIGHT * 128
					+ rend.sprite_height * 128;
				tex.texy = ((tex.sprite_y_pos * sprite->height)
						/ rend.sprite_height) / 256;
				tex.index = tex.texy * sprite->line_lenght + tex.texx
					* (sprite->bpp / 8);
				tex.color = *(int *)(sprite->addr + tex.index);
				if ((tex.color & 0x00FFFFFF) != 0)
					put_brightness(NULL, &tex, &rend, 0);
			}
		}
	}
}

int	set_rend_values(t_sprite *sprite, t_rend *rend)
{
	rend->spritex = sprite->x - pc()->player.x;
	rend->spritey = sprite->y - pc()->player.y;
	rend->invdet = 1.0 / (pc()->player.plane_x * pc()->player.dir_y
			- pc()->player.dir_x * pc()->player.plane_y);
	rend->transform_x = rend->invdet * (pc()->player.dir_y * rend->spritex
			- pc()->player.dir_x * rend->spritey);
	rend->transform_y = rend->invdet * (-pc()->player.plane_y * rend->spritex
			+ pc()->player.plane_x * rend->spritey);
	if (rend->transform_y <= 0.1)
		return (0);
	set_rend_values2(rend);
	return (1);
}

t_sprite	**create_sorted_sprites(void)
{
	int			i;
	int			j;
	int			size;
	t_sprite	**sprites;

	i = 0;
	j = 0;
	size = pc()->coin_count + pc()->enemy_count;
	sprites = malloc(sizeof(t_sprite *) * size);
	if (!sprites)
		return (NULL);
	while (i < pc()->coin_count)
		sprites[j++] = &pc()->coin[i++];
	i = 0;
	while (i < pc()->enemy_count)
		sprites[j++] = &pc()->enemies[i++];
	sort_sprites(sprites, size);
	return (sprites);
}

void	sprite_rendering(float *zbuffer, int size, int i)
{
	t_tex		tex;
	t_rend		rend;
	t_sprite	*temp;
	t_sprite	**sprites;

	sprites = create_sorted_sprites();
	if (!sprites)
		return (free(zbuffer), destroy_everything(1));
	size = pc()->coin_count + pc()->enemy_count;
	ft_memset(&tex, 0, sizeof(t_tex));
	ft_memset(&rend, 0, sizeof(t_rend));
	while (++i < size)
	{
		temp = sprites[i];
		if (set_rend_values(temp, &rend) && !temp->state)
		{
			if (temp->is_coin)
				draw_sprite_columns(rend, tex, zbuffer,
					&pc()->image.coin[pc()->coin_frame]);
			else
				draw_sprite_columns(rend, tex, zbuffer, &pc()->image.enemy);
		}
	}
	free(sprites);
}
