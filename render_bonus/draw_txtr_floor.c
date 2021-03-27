/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_txtr_floor .c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 10:21:19 by grvelva           #+#    #+#             */
/*   Updated: 2021/03/27 08:59:28 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d.h"

static int	get_pxl(t_tex *tex, int x, int y)
{
	char	*src;
	int		color;

	src = tex->addr + (y * tex->line_l + x * (tex->bpp / 8));
	color = *(int *)src;
	return (color);
}

void		calc_pos(int *x, int *y, t_all *all, int j, int i)
{
	t_player	p;
	double		ang_h;
	double		len;

	(void)i;
	ang_h = all->prms->plr.ang_h + M_PI / 6 - i * (M_PI / (3 *
			all->prms->res_h));
	len = (j - all->prms->res_v / 2) * tan(M_PI / 6) / all->prms->res_v;
	p.pos_y = all->prms->plr.pos_y + len * sin(ang_h);
	p.pos_x = all->prms->plr.pos_x + len * cos(ang_h);
	*y = (int)((p.pos_y - floor(p.pos_y)) * 255);
	*x = (int)((p.pos_x - floor(p.pos_x)) * 255);
}

void		draw_floor_pxl(int j, int i, t_all *all)
{
	int		y;
	int		x;
	t_tex	*tex;
	int 	color;

	tex = all->win->floor;
	calc_pos(&x, &y, all, j, i);
	if ((color = get_pxl(tex, x, y)) > 0)
		my_pixel_put(all->win, j, i, color);
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
			draw_floor_pxl(i, j, all);
			i++;
		}
		j++;
	}
}
