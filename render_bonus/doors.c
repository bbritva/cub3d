/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 11:21:21 by grvelva           #+#    #+#             */
/*   Updated: 2021/03/30 16:11:27 by grvelva          ###   ########.fr       */
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

void		draw_door(int size, t_sprite *spr, int n, t_all *all)
{
	t_sprite	tmp;
	double		angle;
	double		dx;
	double		dy;
	int 		h;
	int 		x_c;
	int 		n_start;
	int 		i;
	int 		n_stop;
	int 		n_tmp;
	double		dist;

	(void)size;
	(void)n;
	tmp = *spr;
	tmp.pos_x -= 0.5;
	dx = tmp.pos_x - all->prms->plr.pos_x;
	dy = tmp.pos_y - all->prms->plr.pos_y;
	angle =  - atan2(-dy, dx) + all->prms->plr.ang_h;
	angle -= (angle > M_PI * 2) ? M_PI * 2 : 0;
	angle += (angle < 0) ? M_PI * 2 : 0;
	n_start = (int)((0.5 + sin(angle)) * all->prms->res_h);
	dx = tmp.pos_x + 1 - all->prms->plr.pos_x;
	angle =  - atan2(-dy, dx) + all->prms->plr.ang_h;
	angle -= (angle > M_PI * 2) ? M_PI * 2 : 0;
	angle += (angle < 0) ? M_PI * 2 : 0;
	n_stop = (int)((0.5 + sin(angle)) * all->prms->res_h);
	if (n_stop < n_start)
	{
		n_tmp = n_start;
		n_start = n_stop;
		n_stop = n_tmp;
	}
	i = (n_start < 0) ? -n_start : 0;
	while (n_start + i < n_stop && n_start + i < all->prms->res_h)
	{
		angle = get_ang(all, n_start + i);
		dist = fabs(dy / sin(angle)) * cos(angle - all->prms->plr.ang_h);
		if (dist < all->prms->dists[n_start + i])
		{
			h = (int)((double)all->prms->res_h / 2 / tan(M_PI / 6) / dist);
			x_c = i * 255 / (n_stop - n_start);
			draw_txtr_line(all, n_start + i, h | x_c << 16 | DOOR);
		}
		i++;
	}
}