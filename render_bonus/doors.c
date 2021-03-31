/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 11:21:21 by grvelva           #+#    #+#             */
/*   Updated: 2021/03/31 10:32:22 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d.h"

static double	get_ang(t_all *all, int i)
{
	double		ang;

	ang = all->prms->plr.ang_h + M_PI / 6 - i * (M_PI / (3 * all->prms->res_h));
	(ang < 0) ? ang += 2 * M_PI : ang;
	(ang > 2 * M_PI) ? ang -= 2 * M_PI : ang;
	return (ang);
}

static void		swap_n(int *a, int *b)
{
	int tmp;

	if (*a > *b)
	{
		tmp = *a;
		*a = *b;
		*b = tmp;
	}
}

static void		get_ns(int *n_start, int *n_stop, t_sprite door, t_all *all)
{
	double		dx;
	double		dy;
	double		angle;

	dx = door.pos_x - 0.5 - all->prms->plr.pos_x;
	dy = door.pos_y - all->prms->plr.pos_y;
	angle = -atan2(-dy, dx) + all->prms->plr.ang_h;
	angle -= (angle > M_PI * 2) ? M_PI * 2 : 0;
	angle += (angle < 0) ? M_PI * 2 : 0;
	*n_start = (int)((0.5 + sin(angle)) * all->prms->res_h);
	dx = door.pos_x + 0.5 - all->prms->plr.pos_x;
	angle = -atan2(-dy, dx) + all->prms->plr.ang_h;
	angle -= (angle > M_PI * 2) ? M_PI * 2 : 0;
	angle += (angle < 0) ? M_PI * 2 : 0;
	*n_stop = (int)((0.5 + sin(angle)) * all->prms->res_h);
	swap_n(n_start, n_stop);
}

void			draw_door(int size, t_sprite *spr, int n, t_all *all)
{
	double		angle;
	int			n_start;
	int			i;
	int			n_stop;
	double		dist;

	(void)size;
	(void)n;
	get_ns(&n_start, &n_stop, *spr, all);
	i = (n_start < 0) ? -n_start : 0;
	while (n_start + i < n_stop && n_start + i < all->prms->res_h)
	{
		angle = get_ang(all, n_start + i);
		dist = fabs((spr->pos_y - all->prms->plr.pos_y) / sin(angle)) *
			cos(angle - all->prms->plr.ang_h);
		if (dist < all->prms->dists[n_start + i])
			draw_txtr_line(all, n_start + i,
				((int)((double)all->prms->res_h / 2 / tan(M_PI / 6) / dist))
				| (i * 255 / (n_stop - n_start)) << 16 | DOOR);
		i++;
	}
}
