/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_ray_cast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:27:44 by mprazere          #+#    #+#             */
/*   Updated: 2025/10/30 16:01:05 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_ray_values_hit(t_ray *ray, int x)
{
	ray->camerax = 2 * x / (float)WIDTH - 1;
	ray->pctrx = pc()->player.x + 0.25;
	ray->pctry = pc()->player.y + 0.25;
	ray->mapx = (int)ray->pctrx;
	ray->mapy = (int)ray->pctry;
	ray->raydirx = pc()->player.dir_x + pc()->player.plane_x * ray->camerax;
	ray->raydiry = pc()->player.dir_y + pc()->player.plane_y * ray->camerax;
	if (ray->raydirx == 0)
		ray->raydirx = 0.0001;
	if (ray->raydiry == 0)
		ray->raydiry = 0.0001;
	ray->ddistx = fabs(1 / ray->raydirx);
	ray->ddisty = fabs(1 / ray->raydiry);
	find_steps(ray);
	check_wall(ray, 0);
}

void	set_tex_values(t_ray *ray, t_tex *tex)
{
	int	y;

	if (ray->side == 0)
		tex->wallx = ray->pctry + ray->perpwalldist * ray->raydiry;
	else
		tex->wallx = ray->pctrx + ray->perpwalldist * ray->raydirx;
	tex->wallx -= (int)tex->wallx;
	ray->lineheight = (int)(HEIGHT / ray->perpwalldist);
	ray->drawstart = -ray->lineheight / 2 + HEIGHT / 2;
	y = ray->drawstart;
	if (ray->drawstart < 0)
		ray->drawstart = 0;
	ray->drawend = ray->lineheight / 2 + HEIGHT / 2;
	if (ray->drawend >= HEIGHT)
		ray->drawend = HEIGHT - 1;
	tex->texx = tex->wallx * pc()->image.wall_n.width;
	tex->step = (float)pc()->image.wall_n.height / ray->lineheight;
	tex->texpos = (ray->drawstart - y) * tex->step;
}

void	draw_line(t_ray *ray, t_tex *tex, int x)
{
	while (ray->drawstart <= ray->drawend)
	{
		tex->texy = (int)tex->texpos;
		if (ray->side == 0)
			draw_e_o_wall(ray, tex);
		else
			draw_n_s_wall(ray, tex);
		put_brightness_wall(ray, tex, x);
	}
}

void	ray_cast(void)
{
	int		x;
	t_ray	ray;
	t_tex	tex;
	float	zbuffer[WIDTH];

	x = 0;
	ft_memset(&ray, 0, sizeof(t_ray));
	ft_memset(&tex, 0, sizeof(t_tex));
	while (x < WIDTH)
	{
		set_ray_values_hit(&ray, x);
		set_tex_values(&ray, &tex);
		draw_ceiling_floor(ray, x);
		draw_line(&ray, &tex, x);
		zbuffer[x] = ray.perpwalldist;
		x++;
	}
}
