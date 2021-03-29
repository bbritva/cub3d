/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 11:21:21 by grvelva           #+#    #+#             */
/*   Updated: 2021/03/29 17:03:31 by grvelva          ###   ########.fr       */
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
	double		dist;

	(void)size;
	(void)n;
	tmp = *spr;
	tmp.pos_x -= 0.5;
	dx = tmp.pos_x - all->prms->plr.pos_x;
	dy = tmp.pos_y - all->prms->plr.pos_y;
	angle = atan2(-dy, dx);
	while (angle < 0)
		angle += 2 * M_PI;
	while (angle > 2 * M_PI)
		angle -= 2 * M_PI;
	n_start = (int)(angle * all->prms->res_h * 3 / M_PI);
	dx = tmp.pos_x + 1 - all->prms->plr.pos_x;
	angle = atan2(-dy, dx);
	while (angle < 0)
		angle += 2 * M_PI;
	while (angle > 2 * M_PI)
		angle -= 2 * M_PI;
	n_stop = (int)(angle * all->prms->res_h * 3 / M_PI);
	i = 0;
	while (n_start + i < n_stop)
	{
		angle = get_ang(all, n_start + i);
		dist = fabs(dy * cos(angle));
		if (dist < all->prms->dists[n_start + i])
		{
			h = (int)((double)all->prms->res_h / 2 / tan(M_PI / 6) / dist);
			x_c = i * 255 / (n_stop - n_start);
			draw_txtr_line(all, n_start + i, h | x_c << 16 | DOOR);
		}
		n_start++;
	}
}