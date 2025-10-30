/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_ray_cast_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 16:38:15 by mprazere          #+#    #+#             */
/*   Updated: 2025/10/30 11:11:58 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_e_o_wall(t_ray *ray, t_tex *tex)
{
	if (ray->raydirx > 0)
	{
		tex->index = tex->texy * pc()->image.wall_e.line_lenght + tex->texx
			* (pc()->image.wall_e.bpp / 8);
		tex->color = *(int *)(pc()->image.wall_e.addr + tex->index);
	}
	else
	{
		tex->index = tex->texy * pc()->image.wall_o.line_lenght + tex->texx
			* (pc()->image.wall_o.bpp / 8);
		tex->color = *(int *)(pc()->image.wall_o.addr + tex->index);
	}
}

void	draw_n_s_wall(t_ray *ray, t_tex *tex)
{
	if (ray->raydiry > 0)
	{
		tex->index = tex->texy * pc()->image.wall_s.line_lenght + tex->texx
			* (pc()->image.wall_s.bpp / 8);
		tex->color = *(int *)(pc()->image.wall_s.addr + tex->index);
	}
	else
	{
		tex->index = tex->texy * pc()->image.wall_n.line_lenght + tex->texx
			* (pc()->image.wall_n.bpp / 8);
		tex->color = *(int *)(pc()->image.wall_n.addr + tex->index);
	}
}

void	put_brightness_wall(t_ray *ray, t_tex *tex, int x)
{
	tex->brightness = 1.0 - (ray->perpwalldist / 10.0);
	if (tex->brightness < 0.2)
		tex->brightness = 0.2;
	tex->darker_color = ((int)(((tex->color >> 16) & 0xFF)
				* tex->brightness) << 16) | ((int)(((tex->color >> 8) & 0xFF)
				* tex->brightness) << 8) | (int)((tex->color & 0xFF)
			* tex->brightness);
	put_pixel(x, ray->drawstart++, tex->darker_color);
	tex->texpos += tex->step;
}

void	check_wall(t_ray *ray, int hit)
{
	while (hit == 0)
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
		if (pc()->map[ray->mapy][ray->mapx] == '1')
			hit = 1;
	}
	if (ray->side == 0)
		ray->perpwalldist = (ray->mapx - ray->pctrx + (1 - ray->stepx) / 2)
			/ ray->raydirx;
	else
		ray->perpwalldist = (ray->mapy - ray->pctry + (1 - ray->stepy) / 2)
			/ ray->raydiry;
}

void	find_steps(t_ray *ray)
{
	if (ray->raydirx < 0)
	{
		ray->stepx = -1;
		ray->sdistx = (ray->pctrx - ray->mapx) * ray->ddistx;
	}
	else
	{
		ray->stepx = 1;
		ray->sdistx = (ray->mapx + 1.0 - ray->pctrx) * ray->ddistx;
	}
	if (ray->raydiry < 0)
	{
		ray->stepy = -1;
		ray->sdisty = (ray->pctry - ray->mapy) * ray->ddisty;
	}
	else
	{
		ray->stepy = 1;
		ray->sdisty = (ray->mapy + 1.0 - ray->pctry) * ray->ddisty;
	}
}
