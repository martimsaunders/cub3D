/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_check_wall.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:05:47 by praders           #+#    #+#             */
/*   Updated: 2025/11/11 16:34:53 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	find_hit(t_ray *ray)
{
	int	door_index;

	if (pc()->map[ray->mapy][ray->mapx] == '1')
		ray->hit = 1;
	else if (pc()->map[ray->mapy][ray->mapx] == 'd')
	{
		door_index = find_door_index(ray->mapx, ray->mapy);
		if (pc()->door[door_index].state == 0)
		{
			ray->hit = 2;
			return (0);
		}
	}
	return (1);
}

void	check_wall(t_ray *ray)
{
	ray->hit = 0;
	while (ray->hit == 0)
	{
		if (ray->sdistx < ray->sdisty)
		{
			ray->sdistx += ray->ddistx;
			ray->mapx += ray->stepx;
			ray->side = 0;
		}
		else
		{
			ray->sdisty += ray->ddisty;
			ray->mapy += ray->stepy;
			ray->side = 1;
		}
		if (!find_hit(ray))
			break ;
	}
	if (ray->side == 0)
		ray->perpwalldist = (ray->mapx - ray->pctrx + (1 - ray->stepx) / 2)
			/ ray->raydirx;
	else
		ray->perpwalldist = (ray->mapy - ray->pctry + (1 - ray->stepy) / 2)
			/ ray->raydiry;
}
