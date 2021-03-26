/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sky.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 19:27:20 by grvelva           #+#    #+#             */
/*   Updated: 2021/03/26 09:56:47 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d.h"

static int	get_pxl(t_tex *tex, int i, int h, int x_coor)
{
	char	*src;
	int		color;
	int		y;
	int		x;

	y = tex->h_tex * i / h;
	x = tex->w_tex * x_coor / 4800;
	src = tex->addr + (y * tex->line_l + x * (tex->bpp / 8));
	color = *(int *)src;
	return (color);
}

static double	get_ang(t_all *all, int i)
{
	double		ang;

	ang = all->prms->plr.ang_h + M_PI / 6 - i * (M_PI / (3 * all->prms->res_h));
	(ang < 0) ? ang += 2 * M_PI : ang;
	(ang > 2 * M_PI) ? ang -= 2 * M_PI : ang;
	return (ang);
}


void		draw_skyline(t_all *all, int x_pos, int h)
{
	int		i;
	int		x_coor;
	t_tex	*tex;
	int		color;
	double	angle;

	angle = get_ang(all, x_pos);
	tex = all->win->sky;
	x_coor = (int)(angle * tex->w_tex * 0.745);
	i = 0;
	while (i < h)
	{
		if ((color = get_pxl(tex, i, h, x_coor)) > 0)
			my_pixel_put(all->win, x_pos, i, color);
		i++;
	}
}

void		draw_sky(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->prms->res_h)
	{
		draw_skyline(all, i, all->prms->res_v / 2);
		i += 1;
	}
}