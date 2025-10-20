/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: praders <praders@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 12:10:34 by praders           #+#    #+#             */
/*   Updated: 2025/10/20 13:39:52 by praders          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int end_window(void *param)
{
    t_map *game;

    game = (t_map *)param;
    mlx_destroy_window(game->mlx, game->win);
    mlx_destroy_display(game->mlx);
    free(game->mlx);
    exit(0);
    return (0);
}

int handle_input(int keycode, void *param)
{
    t_map *game;

    game = (t_map *)param;
    if (keycode == XK_Escape)
    {
        mlx_destroy_window(game->mlx, game->win);
        mlx_destroy_display(game->mlx);
        free(game->mlx);
        exit(0);
    }
    return (0);
}

int main(void)
{
    t_map test;

    ft_memset(&test, 0, sizeof(t_map));
    test.mlx = mlx_init();
    test.win = mlx_new_window(test.mlx, LENGHT, WIDTH, "cub3d");
    mlx_hook(test.win, 2, 1L << 0, handle_input, &test);
    mlx_hook(test.win, 17, 0, end_window, &test);
    mlx_loop(test.mlx);
    
    return (0);
}