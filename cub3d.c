/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 12:10:34 by praders           #+#    #+#             */
/*   Updated: 2025/10/22 17:57:27 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_game	*pc(void)
{
	static t_game	pc;

	return (&pc);
}

int	end_window(void)
{
	mlx_destroy_window(pc()->mlx, pc()->win);
	mlx_destroy_display(pc()->mlx);
	free(pc()->mlx);
	exit(0);
	return (0);
}

int	key_press(int keycode)
{
	if (keycode == XK_a)
		pc()->button.A = true; 
	if (keycode == XK_w)
		pc()->button.W = true; 
	if (keycode == XK_s)
		pc()->button.S = true; 
	if (keycode == XK_d)
		pc()->button.D = true; 
	return (0);
}

int	key_release(int keycode)
{
	if (keycode == XK_a)
		pc()->button.A = false;
	if (keycode == XK_w)
		pc()->button.W = false;
	if (keycode == XK_s)
		pc()->button.S = false;
	if (keycode == XK_d)
		pc()->button.D = false;
	return (0);
}


void	create_map_player(void)
{
	int	temp[6][6] = {{1, 1, 1, 1, 1, 1}, {1, 0, 0, 0, 0, 1}, {1, 0, 0, 1, 0,
			1}, {1, 0, 1, 0, 0, 1}, {1, 0, 0, 0, 0, 1}, {1, 1, 1, 1, 1, 1}};

	ft_memcpy(pc()->map, temp, sizeof(temp));
	pc()->player.x = 2.5;
	pc()->player.y = 2.5;
	pc()->player.dir_x = -1.0;
	pc()->player.dir_y = 0.0;
	pc()->player.plane_x = 0.0;
	pc()->player.plane_y = 0.66;
	pc()->player.move_speed = 0.05;
	pc()->player.rot_speed = 0.03;
}

void	put_pixel(int x, int y, int color)
{
	int	index;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	index = (y * pc()->image.line_lenght) + (x * pc()->image.bpp / 8);
	*(unsigned int *)(pc()->image.addr + index) = color;
}

void draw_square(int x, int y, int size, int color)
{
	int i;
	int j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
			put_pixel(x + j++, y + i, color);
		i++;
	}
}

void init_player(void)
{
	pc()->player.x = WIDTH / 2;
	pc()->player.y = HEIGHT / 2;
}

void move_player()
{
	float speed = 0.5;
	
	if (pc()->button.W)
		pc()->player.y -= speed;
	if (pc()->button.S)
		pc()->player.y += speed;
	if (pc()->button.D)
		pc()->player.x += speed;
	if (pc()->button.A)
		pc()->player.x -= speed;
}

int draw_move(void)
{
	move_player();
	draw_square(pc()->player.x, pc()->player.y, 10, 0xFF00FF);
	mlx_put_image_to_window(pc()->mlx, pc()->win, pc()->image.image, 0, 0);
	return (0);
}

int	main(void)
{
	init_player();
	pc()->mlx = mlx_init();
	pc()->win = mlx_new_window(pc()->mlx, WIDTH, HEIGHT, "cub3d");
	pc()->image.image = mlx_new_image(pc()->mlx, WIDTH, HEIGHT);
	pc()->image.addr = mlx_get_data_addr(pc()->image.image, &pc()->image.bpp,
			&pc()->image.line_lenght, &pc()->image.endian);
	mlx_put_image_to_window(pc()->mlx, pc()->win, pc()->image.image, 0, 0);
	create_map_player();
	//draw_square(WIDTH / 2, HEIGHT / 2, 10, 0xFF00FF);
	mlx_hook(pc()->win, 2, 1L << 0, key_press, NULL);
	mlx_hook(pc()->win, 3, 1L << 1, key_release, NULL);
	mlx_hook(pc()->win, 17, 0, end_window, NULL);
	mlx_loop_hook(pc()->mlx, draw_move, NULL);
	mlx_loop(pc()->mlx);
	return (0);
}