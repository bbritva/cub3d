/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_spites.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 18:05:08 by grvelva           #+#    #+#             */
/*   Updated: 2021/03/15 12:51:02 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * BONUS
 */
#include "../includes_bonus/cub3d.h"

static void		sort_sprites(t_sprite **sprites)
{
	int			i;
	int			j;
	t_sprite	*temp;

	i = 0;
	if (!sprites || !sprites[0])
		return ;
	while (sprites[i + 1])
	{
		j = i;
		while (sprites[j + 1])
		{
			if (sprites[j]->dist > sprites[j + 1]->dist)
			{
				temp = sprites[j];
				sprites[j] = sprites[j + 1];
				sprites[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

static void		prepare_sprites(t_all *all)
{
	int			i;

	i = 0;
	while (all->prms->sprites[i])
	{
		set_spr_prms(all->prms->sprites[i++], all->prms->plr);
	}
	sort_sprites(all->prms->sprites);
}

static double	get_angle(double plr_ang, double spr_ang)
{
	double angle;

	angle = plr_ang - spr_ang;
	angle -= (angle > M_PI * 2) ? M_PI * 2 : 0;
	angle += (angle < 0) ? M_PI * 2 : 0;
	return (angle);
}

static int		check_angle(double angle)
{
	if ((angle < (M_PI / 2) || angle > (3 * M_PI / 2)))
		return (1);
	return (0);
}

void			draw_sprites(t_all *all)
{
	int		i;
	int		j;
	int		n;
	int		x_c;
	double	angle;
	int		size;

	i = 0;
	prepare_sprites(all);
	while (all->prms->sprites[i] && all->prms->sprites[i + 1])
		i++;
	while (i >= 0)
	{
		angle = get_angle(all->prms->plr.ang_h, all->prms->sprites[i]->angle);
		n = (int)((0.5 + sin(angle)) * all->prms->res_h);
		size = (int)((double)all->prms->res_h / 2 / tan(M_PI / 6) /
			all->prms->sprites[i]->dist);
		j = n - size / 2;
		while (j < n + size / 2)
		{
			x_c = ((j - n + size / 2) * 255 / size);
			x_c += ((int)(all->prms->sprites[i]->dist * 10) % 4 == 1) ? 255 : 0;
			x_c += ((int)(all->prms->sprites[i]->dist * 10) % 4 == 3) ? 510 : 0;
			if (j > 0 && j < all->prms->res_h && check_angle(angle) &&
			all->prms->dists[j] > all->prms->sprites[i]->dist)
				draw_txtr_line(all, j, size | x_c << 16);
			j++;
		}
		i--;
	}
}
