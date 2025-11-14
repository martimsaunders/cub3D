/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 13:25:10 by mateferr          #+#    #+#             */
/*   Updated: 2025/11/14 13:25:33 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	hud_find_index(char c)
{
	char	*bitmap;
	int		i;

	bitmap = "0123456789e";
	i = -1;
	while (bitmap[++i])
	{
		if (bitmap[i] == c)
			return (i);
	}
	return (-1);
}

void	hud_draw_char(t_hud *h, char c, int px)
{
	int	idx;
	int	bmap_w;
	int	color;
	int	x;
	int	y;

	idx = hud_find_index(c);
	if (idx == -1)
		return ;
	if (c == 'e')
		bmap_w = 100;
	else
		bmap_w = 30;
	y = -1;
	while (++y <= HUD)
	{
		x = -1;
		while (++x <= bmap_w)
		{
			color = hud_get_pixel_color(h->bitmap, x + idx * 30, y);
			put_pixel(x + px, y, color);
		}
	}
}

void	hud_draw_number(t_hud *h, int num, int px)
{
	int		i;
	char	*str;

	str = ft_itoa(num);
	if (!str)
		destroy_everything(1);
	i = -1;
	while (str[++i])
	{
		hud_draw_char(h, str[i], px);
		px += 30;
	}
	free(str);
}
