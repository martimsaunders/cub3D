/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_coins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:10:57 by mprazere          #+#    #+#             */
/*   Updated: 2025/11/04 16:11:10 by mprazere         ###   ########.fr       */
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