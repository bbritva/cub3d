/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawers_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 18:00:04 by grvelva           #+#    #+#             */
/*   Updated: 2021/03/29 12:49:55 by grvelva          ###   ########.fr       */
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
	x = tex->h_tex * x_coor / 255;
	src = tex->addr + (y * tex->line_l + x * (tex->bpp / 8));
	color = *(int *)src;
	return (color);
}

int			shadow_color(int color, int h, int res_h)
{
	int red;
	int green;
	int blue;
	int	base;

	base = (int)((double)res_h / 8 / tan(M_PI / 6));
	if (h > base)
		return (color);
	h = (h < base / 10) ? (base / 10) : h;
	red = ((color & 0xFF << 16) >> 16) * h / base;
	green = ((color & 0xFF << 8) * h >> 8) / base;
	blue = (color & 0xFF) * h / base;
	color = red << 16 | green << 8 | blue;
	return (color);
}

void		draw_txtr_line(t_all *all, int x_pos, int h)
{
	int		i;
	int		x_coor;
	t_tex	*tex;
	int		color;

	tex = (h & BARREL) ? all->win->sprite2 : all->win->sprite;
	tex = (h & DOOR) ? all->win->door : tex;
	tex = (h & NORTH) ? all->win->north : tex;
	tex = (h & SOUTH) ? all->win->south : tex;
	tex = (h & WEST) ? all->win->west : tex;
	tex = (h & EAST) ? all->win->east : tex;
	h = h & ~(0b111111 << 26);
	x_coor = h >> 16;
	h = h & ~(0b1111111111111111 << 16);
	i = (all->prms->res_v < h) ? (-all->prms->res_v + h) / 2 : 0;
	while (i < h)
	{
		if ((all->prms->res_v - h) / 2 + i >= all->prms->res_v)
			break ;
		if ((color = get_pxl(tex, i, h, x_coor)) > 0)
			my_pixel_put(all->win, x_pos, (all->prms->res_v - h) / 2 + i,
				shadow_color(color, h, all->prms->res_h));
		i++;
	}
}
