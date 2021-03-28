/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 09:53:07 by grvelva           #+#    #+#             */
/*   Updated: 2021/03/28 12:07:59 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d.h"

void		draw_deathscreen(t_all *all)
{
	int i;
	int j;

	i = 0;
	while (i < all->prms->res_v)
	{
		j = 0;
		while (j < all->prms->res_h)
		{
			my_pixel_put(all->win, j, i, 0x999999);
			j++;
		}
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

void		draw_bite(t_all *all)
{
	int i;
	int j;

	i = 0;
	while (i < all->prms->res_v)
	{
		j = 0;
		while (j < all->prms->res_h)
		{
			my_pixel_put(all->win, j, i, 0x8B0000);
			j += 2;
		}
		i += 2;
	}
}

int			create_img(t_all *all)
{
	all->win->img = mlx_new_image(all->win->mlx, all->prms->res_h,
		all->prms->res_v);
	all->win->addr = mlx_get_data_addr(all->win->img, &all->win->bpp,
		&all->win->line_l, &all->win->en);
	if (all->prms->plr.health > 0)
	{
		draw_txtr_floor(all);
		draw_sky(all);
		draw_walls(all);
		draw_sprites(all);
		if (all->win->move_mask & IS_BITTEN)
			draw_bite(all);
		draw_gun(all);
		draw_hud(all);
	}
	else
		draw_deathscreen(all);
	return (0);
}
