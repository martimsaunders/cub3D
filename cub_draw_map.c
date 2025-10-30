/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_draw_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:56:33 by mprazere          #+#    #+#             */
/*   Updated: 2025/10/30 11:38:45 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_map(void)
{
	int	x;
	int	y;

	y = 0;
	while (pc()->map[y])
	{
		x = -1;
		while (pc()->map[y][++x])
		{
			if (pc()->map[y][x] == '1')
				draw_square(x, y, BLOCK, 0x7B68EE);
			else if (pc()->map[y][x] == '0' || pc()->map[y][x] == 'P')
				draw_checkered_square(x * BLOCK, y * BLOCK, BLOCK, 0xFFFFFF,
					0xE6E6FA);
		}
		y++;
	}
	draw_player_square(pc()->player.x * BLOCK, pc()->player.y * BLOCK, BLOCK
		/ 2, 0xff0000);
}

void	draw_player_square(int pixel_x, int pixel_y, int size, int color)
{
	int	i;
	int	j;

	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size)
		{
			if (i == 0 || i == size - 1 || j == 0 || j == size - 1)
				put_pixel(pixel_x + i, pixel_y + j, 0x000000);
			else
				put_pixel(pixel_x + i, pixel_y + j, color);
		}
	}
}

void	draw_checkered_square(int x, int y, int size, int color1, int color2)
{
	int	i;
	int	j;
	int	cell_size;
	int	cell_x;
	int	cell_y;

	cell_size = size / 2;
	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size)
		{
			cell_x = i / cell_size;
			cell_y = j / cell_size;
			if ((cell_x + cell_y) % 2 == 0)
				put_pixel(x + i, y + j, color1);
			else
				put_pixel(x + i, y + j, color2);
		}
	}
}

void	draw_square(int x, int y, int size, int color)
{
	int		i;
	int		j;
	char	**a;

	a = pc()->map;
	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size)
		{
			if (x > 0 && a[y][x - 1] != '1' && i == 0)
				put_pixel((x * BLOCK) + i, (y * BLOCK) + j, 0x000000);
			else if (a[y][x + 1] && a[y][x + 1] != '1' && i == size - 1)
				put_pixel((x * BLOCK) + i, (y * BLOCK) + j, 0x000000);
			else if (y > 0 && a[y - 1][x] != '1' && j == 0)
				put_pixel((x * BLOCK) + i, (y * BLOCK) + j, 0x000000);
			else if (a[y + 1] && a[y + 1][x] != '1' && j == size - 1)
				put_pixel((x * BLOCK) + i, (y * BLOCK) + j, 0x000000);
			else
				put_pixel((x * BLOCK) + i, (y * BLOCK) + j, color);
		}
	}
}

void	put_pixel(int x, int y, int color)
{
	int	index;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	index = (y * pc()->image.line_lenght) + (x * pc()->image.bpp / 8);
	*(unsigned int *)(pc()->image.addr + index) = color;
}
