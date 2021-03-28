/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_txtr_floor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 10:21:19 by grvelva           #+#    #+#             */
/*   Updated: 2021/03/28 11:04:06 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d.h"

static int	get_pxl(t_tex *tex, int j, int i)
{
	char	*src;
	int		color;

	src = tex->addr + (j * tex->line_l + i * (tex->bpp / 8));
	color = *(int *)src;
	return (color);
}

void		calc_pos(int *x, int *y, t_all *all, int pos)
{
	t_player	p;
	double		ang_h;
	double		fov_v;
	double		len;

	fov_v = M_PI * all->prms->res_v / (3 * all->prms->res_h);
	ang_h = all->prms->plr.ang_h + M_PI / 6 - (pos >> 16) * (M_PI / (3 *
			all->prms->res_h));
	len = all->prms->res_v / (4 * tan(fov_v / 2) * (((pos << 16) >> 16) -
			all->prms->res_v / 2));
	p.pos_y = all->prms->plr.pos_y - len * sin(ang_h);
	p.pos_x = all->prms->plr.pos_x + len * cos(ang_h);
	*y = (int)((p.pos_y - floor(p.pos_y)) * 255);
	*x = (int)((p.pos_x - floor(p.pos_x)) * 255);
}

void		draw_floor_pxl(int j, int i, t_all *all)
{
	int		y;
	int		x;
	t_tex	*tex;
	int		color;

	tex = all->win->floor;
	calc_pos(&x, &y, all, j | (i << 16));
	if ((color = get_pxl(tex, x, y)) > 0)
		my_pixel_put(all->win, i, j, shadow_color(color,
			(2 * j - all->prms->res_v), all->prms->res_h));
}

void		draw_txtr_floor(t_all *all)
{
	int		i;
	int		j;

	j = all->prms->res_v / 2 + 10;
	while (j < all->prms->res_v)
	{
		i = 0;
		while (i < all->prms->res_h)
		{
			draw_floor_pxl(j, i, all);
			i++;
		}
		j++;
	}
}
