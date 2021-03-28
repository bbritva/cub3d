/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sky.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 19:27:20 by grvelva           #+#    #+#             */
/*   Updated: 2021/03/28 10:18:48 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d.h"

static int		get_pxl(t_tex *tex, int i, int h, int x_coor)
{
	char	*src;
	int		color;
	int		y;

	y = tex->h_tex * i / h;
	x_coor -= (x_coor > tex->w_tex) ? tex->w_tex : 0;
	x_coor += (x_coor < 0) ? tex->w_tex : 0;
	src = tex->addr + (y * tex->line_l + x_coor * (tex->bpp / 8));
	color = *(int *)src;
	return (color);
}

static double	get_ang(t_all *all)
{
	double		ang;

	ang = all->prms->plr.ang_h + M_PI / 6;
	(ang < 0) ? ang += 2 * M_PI : ang;
	(ang > 2 * M_PI) ? ang -= 2 * M_PI : ang;
	return (ang);
}

static void		draw_skyline(t_all *all, int x_coor, int x_pos, int h)
{
	int		i;
	int		color;

	i = 0;
	while (i < h)
	{
		if ((color = get_pxl(all->win->sky, i, h, x_coor)) > 0)
			my_pixel_put(all->win, x_pos, i, color);
		i++;
	}
}

void			draw_sky(t_all *all)
{
	double	x_start;
	double	x_end;
	double	x_step;
	double	angle;
	int		i;

	angle = get_ang(all);
	x_start = angle * all->win->sky->w_tex / (2 * M_PI);
	x_end = (angle - M_PI / 3) * all->win->sky->w_tex / (2 * M_PI);
	x_step = (x_end - x_start) / all->prms->res_h;
	i = 0;
	while (x_start > x_end)
	{
		draw_skyline(all, (int)x_start, i, all->prms->res_v / 2);
		x_start += x_step;
		i++;
	}
}
