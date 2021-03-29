/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_spites.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 18:05:08 by grvelva           #+#    #+#             */
/*   Updated: 2021/03/29 13:18:54 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d.h"

static int		check_angle(double angle)
{
	if ((angle < (M_PI / 2) || angle > (3 * M_PI / 2)))
		return (1);
	return (0);
}

static void		draw_sprite(int size, t_sprite *spr, int n, t_all *all)
{
	int		j;
	int		x_c;

	j = n - size / 2;
	while (j < n + size / 2)
	{
		if (j > 0 && j < all->prms->res_h && all->prms->dists[j] > spr->dist)
		{
			x_c = ((j - n + size / 2) * 255 / size);
			if (spr->status_mask & Z_BARREL)
				draw_txtr_line(all, j, size | x_c << 16 | BARREL);
			else
			{
				x_c += (spr->status_mask & Z_ALIVE) ? 0 : 765;
				if (spr->status_mask & Z_GOING &&
					spr->status_mask & Z_ALIVE)
					x_c += ((int)(spr->dist * 4) % 2 == 1) ? 255 : 510;
				draw_txtr_line(all, j, size | x_c << 16);
			}
		}
		j++;
	}
}

static double	get_angle(double plr_ang, double spr_ang)
{
	double angle;

	angle = plr_ang - spr_ang;
	angle -= (angle > M_PI * 2) ? M_PI * 2 : 0;
	angle += (angle < 0) ? M_PI * 2 : 0;
	return (angle);
}

void			draw_sprites(t_all *all)
{
	int		i;
	int		n;
	double	angle;
	int		size;

	i = 0;
	prepare_sprites(all);
	while (all->prms->sprites[i] && all->prms->sprites[i + 1])
		i++;
	while (i >= 0 && all->prms->sprites[0])
	{
		angle = get_angle(all->prms->plr.ang_h, all->prms->sprites[i]->angle);
		n = (int)((0.5 + sin(angle)) * all->prms->res_h);
		size = (int)((double)all->prms->res_h / 2 / tan(M_PI / 6) /
			all->prms->sprites[i]->dist);
		if (check_angle(angle))
		{
			if (all->prms->sprites[i]->status_mask & Z_DOOR)
				draw_door(size, all->prms->sprites[i], n, all);
			else
				draw_sprite(size, all->prms->sprites[i], n, all);
		}
		i--;
	}
}
