/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_ray_cast_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateferr <mateferr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 16:38:15 by mprazere          #+#    #+#             */
/*   Updated: 2025/11/14 13:32:09 by mateferr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

void	put_brightness(t_ray *ray, t_tex *tex, t_rend *rend, int x)
{
	if (rend)
	{
		tex->brightness = 1.0 - (rend->transform_y / 10.0);
		if (tex->brightness < 0.2)
			tex->brightness = 0.2;
		tex->color = ((int)(((tex->color >> 16) & 0xFF)
					* tex->brightness) << 16)
			| ((int)(((tex->color >> 8) & 0xFF)
					* tex->brightness) << 8) | (int)((tex->color & 0xFF)
				* tex->brightness);
		put_pixel(tex->x, tex->y, tex->color);
		return ;
	}
	tex->brightness = 1.0 - (ray->perpwalldist / 10.0);
	if (tex->brightness < 0.2)
		tex->brightness = 0.2;
	tex->color = ((int)(((tex->color >> 16) & 0xFF)
				* tex->brightness) << 16) | ((int)(((tex->color >> 8) & 0xFF)
				* tex->brightness) << 8) | (int)((tex->color & 0xFF)
			* tex->brightness);
	put_pixel(x, ray->drawstart++, tex->color);
	tex->texpos += tex->step;
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
