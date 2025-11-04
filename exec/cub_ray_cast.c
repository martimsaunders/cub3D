/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_ray_cast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:27:44 by mprazere          #+#    #+#             */
/*   Updated: 2025/11/04 16:11:21 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
	check_wall(ray);
}

void	setup_wall_texture(t_ray *ray, t_tex *tex)
{
	t_asset	*wall;

	if (ray->hit == 2)
		wall = &pc()->image.door;
	else if (ray->side == 0)
	{
		if (ray->raydirx > 0)
			wall = &pc()->image.wall_e;
		else
			wall = &pc()->image.wall_o;
	}
	else
	{
		if (ray->raydiry > 0)
			wall = &pc()->image.wall_s;
		else
			wall = &pc()->image.wall_n;
	}
	tex->texx = tex->wallx * wall->width;
	tex->step = (float)wall->height / ray->lineheight;
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
	setup_wall_texture(ray, tex);
	tex->texpos = (ray->drawstart - y) * tex->step;
}

void	draw_line(t_ray *ray, t_tex *tex, int x)
{
	while (ray->drawstart <= ray->drawend)
	{
		tex->texy = (int)tex->texpos;
		if (ray->hit == 2)
		{
			tex->index = tex->texy * pc()->image.door.line_lenght + tex->texx
			* (pc()->image.door.bpp / 8);
			tex->color = *(int *)(pc()->image.door.addr + tex->index);
		}
		else if (ray->side == 0)
			draw_e_o_wall(ray, tex);
		else
			draw_n_s_wall(ray, tex);
		put_brightness(ray, tex, NULL, x);
	}
}

void	ray_cast(void)
{
	int		x;
	t_ray	ray;
	t_tex	tex;
	float	*zbuffer;

	zbuffer = malloc(sizeof(float) * WIDTH);
	if (!zbuffer)
		destroy_everything(1);
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
	sprite_rendering(zbuffer, 0);
	free(zbuffer);
}
