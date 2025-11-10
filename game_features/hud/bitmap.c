/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:59:21 by mateferr          #+#    #+#             */
/*   Updated: 2025/11/07 17:21:09 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void hud_init(t_hud *h)
{
    h->lvl_px = 660;
    h->coin_px = 150;
    h->death_px = 1155;
    h->mode = pc()->mode;
    h->hud_bar = pc()->image.hud_bar;
    h->width = h->hud_bar.width;
    h->lvl = pc()->current_level;
    h->height = h->hud_bar.height;
    h->deaths = pc()->death_count;
    h->coins = pc()->coin_captured;
    h->bitmap = pc()->image.hud_bitmap;
    h->compass = pc()->image.compass;
    h->angle = -(pc()->player.angle + PI / 2);
}

unsigned int hud_get_pixel_color(t_asset asset, int x, int y)
{
    char *pixel;
    int index;

    index = (y * asset.line_lenght) + (x * asset.bpp / 8);
    pixel = asset.addr + index;
	return (*(unsigned int *)pixel);
}

void hud_draw_background(t_hud *h)
{
    int x;
    int y;
    int color;

    y = -1;
    while (++y <= h->height)
    {
        x = -1;
        while (++x <= h->width)
        {
            color = hud_get_pixel_color(h->hud_bar, x, y);
            put_pixel(x, y, color);
        }
    }
}

void draw_hud()
{
    t_hud h;

    hud_init(&h);
    hud_draw_background(&h);
    hud_draw_number(&h, h.coins, h.coin_px);
    if (h.mode == EVAL)
        hud_draw_char(&h, 'e', h.lvl_px);
    else
        hud_draw_number(&h, h.lvl, h.lvl_px);
    hud_draw_number(&h, h.deaths, h.death_px);
    hud_draw_compass(&h);
}
