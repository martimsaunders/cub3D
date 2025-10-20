/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: praders <praders@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 12:10:34 by praders           #+#    #+#             */
/*   Updated: 2025/10/20 16:52:57 by praders          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_game *pc(void)
{
    static t_game pc;

    return (&pc);
}

int end_window(void)
{
    mlx_destroy_window(pc()->mlx, pc()->win);
    mlx_destroy_display(pc()->mlx);
    free(pc()->mlx);
    exit(0);
    return (0);
}

int handle_input(int keycode)
{
    if (keycode == XK_Escape)
    {
        mlx_destroy_window(pc()->mlx, pc()->win);
        mlx_destroy_display(pc()->mlx);
        free(pc()->mlx);
        exit(0);
    }
    return (0);
}

void create_map_player()
{
    int temp[6][6] = {
        {1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 1},
        {1, 0, 0, 1, 0, 1},
        {1, 0, 1, 0, 0, 1},
        {1, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1}
    };
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

void put_pixel(int x, int y, int color)
{
    int offset;

    if (x >= 0 && x < LENGHT && y >= 0 && y < WIDTH)
    {
        offset = (y * pc()->image.line_lenght) + (x * pc()->image.bpp /8);
        *(unsigned int *)(pc()->image.addr + offset) = color;
    }
}

int render_frame(void)
{
    int x;
    int y;

    y = 0;
    while (y < WIDTH)
    {
        x = 0;
        while (x < LENGHT)
        {
            if (y < WIDTH / 2)
                put_pixel(x, y, 0x87CEEB);
            else
                put_pixel(x, y, 0x228B22);
            x++;
        }
        y++;
    }
    mlx_put_image_to_window(pc()->mlx, pc()->win, pc()->image.image, 0, 0);
    return (0);
}

int main(void)
{
    pc()->mlx = mlx_init();
    pc()->win = mlx_new_window(pc()->mlx, LENGHT, WIDTH, "cub3d");
    pc()->image.image = mlx_new_image(pc()->mlx, LENGHT, WIDTH);
    pc()->image.addr = mlx_get_data_addr(pc()->image.image, &pc()->image.bpp, &pc()->image.line_lenght, &pc()->image.endian);
    create_map_player();
    mlx_hook(pc()->win, 2, 1L << 0, handle_input, NULL);
    mlx_hook(pc()->win, 17, 0, end_window, NULL);
    mlx_loop_hook(pc()->mlx, render_frame, NULL);
    mlx_loop(pc()->mlx);
    return (0);
}