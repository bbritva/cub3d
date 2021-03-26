/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_txtr_floor .c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 10:21:19 by grvelva           #+#    #+#             */
/*   Updated: 2021/03/26 11:30:08 by grvelva          ###   ########.fr       */
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

void		calc_pos(int *x, int *y)
{
	double ang_v;
	double ang_h;


}

void		draw_floor_pxl(int j, int i, t_all *all)
{
	int		y;
	int		x;


	calc_pos(&x, &y);
	if ((color = get_pxl(tex, x, y)) > 0)
		my_pixel_put(all->win, x_pos, i, color);
}

void		draw_txtr_floor(t_all *all)
{
	int		i;
	int		j;

	j = all->prms->res_v / 2 + 50;
	while (j < all->prms->res_v)
	{
		i = 0;
		while (i < all->prms->res_h)
		{
			draw_floor_pxl(j, i, all);
		}
		j++;
	}
}
