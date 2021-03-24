/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 09:53:07 by grvelva           #+#    #+#             */
/*   Updated: 2021/03/24 10:43:16 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		draw_fc(t_all *all)
{
	int i;
	int j;

	i = 0;
	while (i < all->prms->res_v / 2)
	{
		j = 0;
		while (j < all->prms->res_h)
			my_pixel_put(all->win, j++, i, all->prms->ceil_color);
		i++;
	}
	while (i < all->prms->res_v)
	{
		j = 0;
		while (j < all->prms->res_h)
			my_pixel_put(all->win, j++, i, all->prms->floor_color);
		i++;
	}
}

void		draw_walls(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->prms->res_h)
	{
		draw_txtr_line(all, i, get_height(all, i));
		i += 1;
	}
}

int			create_img(t_all *all)
{
	all->win->img = mlx_new_image(all->win->mlx, all->prms->res_h,
		all->prms->res_v);
	all->win->addr = mlx_get_data_addr(all->win->img, &all->win->bpp,
		&all->win->line_l, &all->win->en);
	draw_fc(all);
	draw_walls(all);
	draw_sprites(all);
	return (0);
}
