/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: praders <praders@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 12:10:34 by praders           #+#    #+#             */
/*   Updated: 2025/10/24 19:19:53 by praders          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_game *pc()
{
	static t_game pc;

	return (&pc);
}

void	put_pixel(int x, int y, int color)
{
	int	index;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	index = (y * pc()->image.line_lenght) + (x * pc()->image.bpp / 8);
	*(unsigned int *)(pc()->image.addr + index) = color;
}

int key_press(int keycode)
{
	if (keycode == XK_w)
		pc()->button.W = true;
	if (keycode == XK_a)
		pc()->button.A = true;
	if (keycode == XK_s)
		pc()->button.S = true;
	if (keycode == XK_d)
		pc()->button.D = true;
	if (keycode == XK_Left)
		pc()->button.left = true;
	if (keycode == XK_Right)
		pc()->button.right = true;
	return (0);
}

int key_release(int keycode)
{
	if (keycode == XK_w)
		pc()->button.W = false;
	if (keycode == XK_a)
		pc()->button.A = false;
	if (keycode == XK_s)
		pc()->button.S = false;
	if (keycode == XK_d)
		pc()->button.D = false;
	if (keycode == XK_Left)
		pc()->button.left = false;
	if (keycode == XK_Right)
		pc()->button.right = false;
	return (0);
}

int end_window()
{
	mlx_destroy_image(pc()->mlx, pc()->image.image);
	mlx_destroy_window(pc()->mlx, pc()->win);
	mlx_destroy_display(pc()->mlx);
	free(pc()->mlx);
	exit(0);
}

void init_player_map()
{
	pc()->map = malloc(sizeof(char *) * 11);
	pc()->map[0] = "1111111111";
	pc()->map[1] = "10000000P1";
	pc()->map[2] = "1011000001";
	pc()->map[3] = "1010001001";
	pc()->map[4] = "1000001001";
	pc()->map[5] = "1000011001";
	pc()->map[6] = "1000000001";
	pc()->map[7] = "1000001101";
	pc()->map[8] = "1000000001";
	pc()->map[9] = "1111111111";
	pc()->map[10] = NULL;

	find_player();
	pc()->player.move_speed = 0.03;
	pc()->player.rot_speed = 0.03;
	pc()->player.angle = PI * 1.5;
	pc()->player.dir_x = cos(pc()->player.angle);
	pc()->player.dir_y = sin(pc()->player.angle);
	pc()->player.plane_x  = -pc()->player.dir_y * 0.66;
	pc()->player.plane_y  = pc()->player.dir_x * 0.66;
}

void clear_image()
{
	int x;
	int y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
			put_pixel(x++, y, 0x000000);
		y++;
	}
}

void draw_square(int x, int y, int size, int color)
{
	int i;
	int j;
	char **a;

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

void find_player()
{
	int x;
	int y;

	y = -1;
	while (pc()->map[++y])
	{
		x = -1;
		while (pc()->map[y][++x])
		{
			if (pc()->map[y][x] == 'P')
			{
				pc()->player.x = x + 0.25;
				pc()->player.y = y + 0.25;
				return ;
			}
		}
		
	}
}

void draw_checkered_square(int x, int y, int size, int color1, int color2)
{
	int i;
	int j;
	int cell_size;
	int cell_x;
	int cell_y;

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

void move_player()
{
	if (pc()->button.left)
		pc()->player.angle -= pc()->player.rot_speed;
	if (pc()->button.right)
		pc()->player.angle += pc()->player.rot_speed;
	if (pc()->player.angle > 2 * PI)
		pc()->player.angle = 0;
	if (pc()->player.angle < 0)
		pc()->player.angle = 2 * PI;
	pc()->player.dir_x = cos(pc()->player.angle);
	pc()->player.dir_y = sin(pc()->player.angle);
	pc()->player.plane_x  = -pc()->player.dir_y * 0.66;
	pc()->player.plane_y  = pc()->player.dir_x * 0.66;
	float newx = pc()->player.x;
	float newy = pc()->player.y;
	if (pc()->button.W)
	{
		newx += pc()->player.dir_x * pc()->player.move_speed;
		newy += pc()->player.dir_y * pc()->player.move_speed;
	}
	if (pc()->button.S)
	{
		newx -= pc()->player.dir_x * pc()->player.move_speed;
		newy -= pc()->player.dir_y * pc()->player.move_speed;
	}
	if (pc()->button.A)
	{
		newx += pc()->player.dir_y * pc()->player.move_speed;
		newy -= pc()->player.dir_x * pc()->player.move_speed;
	}
	if (pc()->button.D)
	{
		newx -= pc()->player.dir_y * pc()->player.move_speed;
		newy += pc()->player.dir_x * pc()->player.move_speed;
	}
	int start_x = (int)newx;
	int end_x = (int)(newx + 0.5);
	int start_y = (int)newy;
	int end_y = (int)(newy + 0.5);
	
	for (int ty = start_y; ty <= end_y; ty++)
	{
		for (int tx = start_x; tx <= end_x; tx++)
		{
			if (pc()->map[ty][tx] == '1')
				return;
		}
	}

	pc()->player.x = newx;
	pc()->player.y = newy;
	/* float margin = 0.02;
	if (pc()->map[(int)(newy + margin)][(int)(newx + margin)] != '1' && 
		pc()->map[(int)(newy + 0.5 - margin)][(int)(newx + margin)] != '1' &&
		pc()->map[(int)(newy + margin)][(int)(newx + 0.5 - margin)] != '1' && 
		pc()->map[(int)(newy + 0.5 - margin)][(int)(newx + 0.5 - margin)] != '1')
	{
		pc()->player.x = newx;
		pc()->player.y = newy;
	} */
}

void draw_player_square(int pixel_x, int pixel_y, int size, int color)
{
	int i;
	int j;

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

void draw_map()
{
	int x;
	int y;

	y = 0;
	while (pc()->map[y])
	{
		x = -1;
		while (pc()->map[y][++x])
			if (pc()->map[y][x] == '1')
				draw_square(x, y, BLOCK, 0x7B68EE);
			else if (pc()->map[y][x] == '0' || pc()->map[y][x] == 'P')
				draw_checkered_square(x * BLOCK, y * BLOCK, BLOCK, 0xFFFFFF, 0xE6E6FA);
		y++;
	}
}

void draw_line(int x1, int y1, int color)
{
	int x0 = pc()->player.x * BLOCK;
	int y0 = pc()->player.y * BLOCK;
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx;
	if (x0 < x1)
		sx = 1;
	else
		sx = -1;
	int sy;
	if (y0 < y1)
		sy = 1;
	else
		sy = -1;
	int err = dx - dy;
	while (1)
	{
		put_pixel(x0, y0, color);
		if (x0 == x1 && y0 == y1)
			break;
		int e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

void ray_cast()
{
	int x = 0;

	while (x < WIDTH)
	{
		float camerax = 2 * x / (float)WIDTH - 1;
		float player_center_x = pc()->player.x + 0.25;
		float player_center_y = pc()->player.y + 0.25;
		int mapx = (int)player_center_x;
		int mapy = (int)player_center_y;
		float raydirx = pc()->player.dir_x + pc()->player.plane_x * camerax;
		float raydiry = pc()->player.dir_y + pc()->player.plane_y * camerax;
		if (raydirx == 0)
			raydirx = 0.0001;
		if (raydiry == 0)
			raydiry = 0.0001;	
		float deltadistx = fabs(1 / raydirx);
		float deltadisty = fabs(1 / raydiry);
		int stepx;
		int stepy;
		float sidedistx;
		float sidedisty;

		if (raydirx < 0)
			(stepx = -1, sidedistx = (player_center_x - mapx) * deltadistx);
		else
			(stepx = 1, sidedistx = (mapx + 1.0 - player_center_x) * deltadistx);
		if (raydiry < 0)
			(stepy = -1, sidedisty = (player_center_y - mapy) * deltadisty);
		else
			(stepy = 1, sidedisty = (mapy + 1.0 - player_center_y) * deltadisty);
		int hit = 0;
		int side;
		while (hit == 0)
		{
			if (sidedistx < sidedisty)
				(sidedistx += deltadistx, mapx += stepx, side = 0);
			else
				(sidedisty += deltadisty, mapy += stepy, side = 1);
			if (pc()->map[mapy][mapx] == '1')
				hit = 1;
		}
		float perpwalldist;
		if (side == 0)
			perpwalldist = (mapx - player_center_x + (1 - stepx) / 2) / raydirx;
		else
			perpwalldist = (mapy - player_center_y + (1 - stepy) / 2) / raydiry;
		int lineheight = (int)(HEIGHT / perpwalldist);
		int drawstart = -lineheight / 2 + HEIGHT / 2;
		if (drawstart < 0)
			drawstart = 0;
		int drawend = lineheight / 2 + HEIGHT / 2;
		if (drawend >= HEIGHT)
			drawend = HEIGHT - 1;
		int color;
		if (side == 0)
			color = 0xFF0000;
		else
			color = 0x880000;
		int y = drawstart;
		while (y < drawend)
		{
			put_pixel(x, y, color);
			y++;
		}
		/* float wallx = pc()->player.x + raydirx * perpwalldist;
		float wally = pc()->player.y + raydiry * perpwalldist;
		draw_line(wallx * BLOCK, wally * BLOCK, 0xFF0000); */
		x++;
	}
}

int draw_move()
{
	clear_image();
	move_player();
	ray_cast();
	draw_map();
	draw_player_square(pc()->player.x * BLOCK, pc()->player.y * BLOCK, BLOCK / 2, 0xff0000);
	mlx_put_image_to_window(pc()->mlx, pc()->win, pc()->image.image, 0, 0);
	return (0);
}

int	main(void)
{
	pc()->mlx = mlx_init();
	pc()->win = mlx_new_window(pc()->mlx, WIDTH, HEIGHT, "cub3d");
	pc()->image.image = mlx_new_image(pc()->mlx, WIDTH, HEIGHT);
	pc()->image.addr = mlx_get_data_addr(pc()->image.image, &pc()->image.bpp,
			&pc()->image.line_lenght, &pc()->image.endian);
	init_player_map();
	mlx_put_image_to_window(pc()->mlx, pc()->win, pc()->image.image, 0, 0);
	mlx_hook(pc()->win, 2, 1L << 0, key_press, NULL);
	mlx_hook(pc()->win, 3, 1L << 1, key_release, NULL);
	mlx_hook(pc()->win, 17, 0, end_window, NULL);
	mlx_loop_hook(pc()->mlx, draw_move, NULL);
	mlx_loop(pc()->mlx);
	return (0);
}