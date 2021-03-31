/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_gun.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 11:12:08 by grvelva           #+#    #+#             */
/*   Updated: 2021/03/30 18:49:39 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d.h"

static int	get_pxl(t_tex *tex, int j, int i, t_all *all)
{
	char	*src;
	int		color;
	int		x;
	int		y;

	x = (i - all->prms->res_h / 2) * 2 * tex->w_tex / all->prms->res_h;
	y = (j - 0.6 * all->prms->res_v) * 2.5 * tex->h_tex / all->prms->res_v;
	src = tex->addr + (y * tex->line_l + x * (tex->bpp / 8));
	color = *(int *)src;
	return (color);
}

void		draw_gun(t_all *all)
{
	static int	count = 0;
	int			i;
	int			j;
	t_tex		*tex;
	int			color;

	count += (all->prms->plr.status_mask & IS_SHOOT) ? 1 : 0;
	tex = (all->prms->plr.status_mask & IS_SHOOT && count > 7) ?
			all->win->gun2 : all->win->gun;
	j = 0.6 * all->prms->res_v;
	while (j < all->prms->res_v)
	{
		i = all->prms->res_h / 2;
		while (i < all->prms->res_h)
		{
			if ((color = get_pxl(tex, j, i, all)) > 0)
				my_pixel_put(all->win, i, j, color);
			i++;
		}
		j++;
	}
	all->prms->plr.status_mask = (count == 10) ? 0 : all->prms->plr.status_mask;
	count = (count == 10) ? 0 : count;
}
