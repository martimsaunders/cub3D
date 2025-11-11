/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_coins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:10:57 by mprazere          #+#    #+#             */
/*   Updated: 2025/11/11 16:34:58 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_coin_colision(void)
{
	int	i;

	i = 0;
	while (i < pc()->coin_count)
	{
		distance(&pc()->coin[i]);
		if (pc()->coin[i].distance < 0.5 && pc()->coin[i].state == 0)
		{
			pc()->coin[i].state = 1;
			pc()->coin_captured++;
			return ;
		}
		i++;
	}
}

int	find_coin_state(int x, int y)
{
	int	i;

	i = 0;
	while (i < pc()->coin_count)
	{
		if ((int)pc()->coin[i].x == x && (int)pc()->coin[i].y == y)
			return (pc()->coin[i].state);
		i++;
	}
	return (1);
}
