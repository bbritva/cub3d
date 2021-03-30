/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movers.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 09:51:18 by grvelva           #+#    #+#             */
/*   Updated: 2021/03/28 16:22:26 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d.h"

static int		is_z_near(t_all *all, double i, double j)
{
	double dist;

	dist = pow(i - all->prms->sprites[0]->pos_y, 2) + pow(j -
			all->prms->sprites[0]->pos_x, 2);
	return (dist < pow(0.4, 2) && ((all->prms->sprites[0]->status_mask &
	Z_ALIVE) || (all->prms->sprites[0]->status_mask & Z_BARREL)));
}

static int		can_step(t_all *all, double i, double j)
{
	if (all->prms->map[(int)i][(int)j] == '1')
		return (0);
	if (all->prms->map[(int)(i + D)][(int)j] == '1')
		return (0);
	if (all->prms->map[(int)(i - D)][(int)j] == '1')
		return (0);
	if (all->prms->map[(int)i][(int)(j + D)] == '1')
		return (0);
	if (all->prms->map[(int)i][(int)(j - D)] == '1')
		return (0);
	if (all->prms->map[(int)i][(int)(j)] == '4')
		return (0);
	return (!is_z_near(all, i, j));
}

static int		move(t_all *all, double ang, double *pos_x, double
*pos_y)
{
	double i_cur;
	double j_cur;
	double i_new;
	double j_new;

	i_cur = *pos_y;
	j_cur = *pos_x;
	i_new = (i_cur - SPEED * sin(ang));
	j_new = (j_cur + SPEED * cos(ang));
	if (can_step(all, i_new, j_cur))
		*pos_y -= SPEED * sin(ang);
	if (can_step(all, i_cur, j_new))
		*pos_x += SPEED * cos(ang);
	return (0);
}

int				move_plr(t_all *all)
{
	if (all->win->move_mask & FORWARD)
		move(all, all->prms->plr.ang_h, &all->prms->plr.pos_x,
			&all->prms->plr.pos_y);
	if (all->win->move_mask & MV_LEFT)
		move(all, all->prms->plr.ang_h + M_PI_2, &all->prms->plr.pos_x,
			&all->prms->plr.pos_y);
	if (all->win->move_mask & BACKWARD)
		move(all, all->prms->plr.ang_h + M_PI, &all->prms->plr.pos_x,
			&all->prms->plr.pos_y);
	if (all->win->move_mask & MV_RIGHT)
		move(all, all->prms->plr.ang_h - M_PI_2, &all->prms->plr.pos_x,
			&all->prms->plr.pos_y);
	if (all->win->move_mask & RT_LEFT)
		all->prms->plr.ang_h -= 0.06f;
	if (all->win->move_mask & RT_RIGHT)
		all->prms->plr.ang_h += 0.06f;
	if (all->win->move_mask & ESC)
		my_exit(all);
	all->prms->plr.ang_h -= (all->prms->plr.ang_h > M_PI * 2) ? M_PI * 2 : 0;
	all->prms->plr.ang_h += (all->prms->plr.ang_h < 0) ? M_PI * 2 : 0;
	return (1);
}
