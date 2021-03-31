/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawers_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 18:00:04 by grvelva           #+#    #+#             */
/*   Updated: 2021/03/24 10:43:16 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	get_pxl(t_tex *tex, int i, int h, int x_coor)
{
	char	*src;
	int		color;
	int		y;
	int		x;

	y = tex->h_tex * i / h;
	x = tex->w_tex * x_coor / 255;
	src = tex->addr + (y * tex->line_l + x * (tex->bpp / 8));
	color = *(int *)src;
	return (color);
}

void		draw_txtr_line(t_all *all, int x_pos, int h)
{
	int		i;
	int		x_coor;
	t_tex	*tex;
	int		color;

	tex = all->win->sprite;
	tex = (h & NORTH) ? all->win->north : tex;
	tex = (h & SOUTH) ? all->win->south : tex;
	tex = (h & WEST) ? all->win->west : tex;
	tex = (h & EAST) ? all->win->east : tex;
	h = h & ~(0b1111 << 26);
	x_coor = h >> 16;
	h = h & ~(0b11111111 << 16);
	i = (all->prms->res_v < h) ? (-all->prms->res_v + h) / 2 : 0;
	while (i < h)
	{
		if ((all->prms->res_v - h) / 2 + i >= all->prms->res_v)
			break ;
		if ((color = get_pxl(tex, i, h, x_coor)) > 0)
			my_pixel_put(all->win, x_pos, (all->prms->res_v - h) / 2 + i,
				color);
		i++;
	}
}
