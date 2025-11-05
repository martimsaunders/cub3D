/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_coins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: praders <praders@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:10:57 by mprazere          #+#    #+#             */
/*   Updated: 2025/11/05 13:00:10 by praders          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_coin_colision(void)
{
	int i;

	i = 0;
	while (i < pc()->coin_count)
	{
		distance(&pc()->coin[i]);
		if (pc()->coin[i].distance < 0.5 && pc()->coin[i].state == 0)
		{
			pc()->coin[i].state = 1;
			pc()->coin_captured++;
			return;
		}
		i++;
	}
}

int	find_coin_state(int x, int y)
{
	int i;

	i = 0;
	while (i < pc()->coin_count)
	{
		if ((int)pc()->coin[i].x == x && (int)pc()->coin[i].y == y)
			return (pc()->coin[i].state);
		i++;
	}
	return (1);
}