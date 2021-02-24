/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movers.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 09:51:18 by grvelva           #+#    #+#             */
/*   Updated: 2021/02/24 19:41:38 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

double		min_wall_dist(t_all * all)
{
	int i;
	double min;

	i = 0;
	min = all->prms->dists[i++];
	while (i < all->prms->res_h)
	{
		if (all->prms->dists[i] < min)
			min = all->prms->dists[i];
		i++;
	}
	return min;
}

int			move(t_all *all, double angle);


int			move_fwd(t_all *all)
{
	move(all, all->prms->plr.ang_h);
	return (0);
}

int			move_bwd(t_all *all)
{
	double angle;

	angle = all->prms->plr.ang_h + M_PI;
	move(all, angle);
	return(0);
}

int			move_left(t_all *all)
{
	double angle;

	angle = all->prms->plr.ang_h + M_PI_2;
	move(all, angle);
	return(0);
}

int			move_right(t_all *all)
{
	double angle;

	angle = all->prms->plr.ang_h - M_PI_2;
	move(all, angle);
	return(0);
}

int			move(t_all *all, double angle)
{
	int i_cur;
	int j_cur;
	int i_new;
	int j_new;

	i_cur = (int)(all->prms->plr.pos_y / SCALE);
	j_cur = (int)(all->prms->plr.pos_x / SCALE);
//	i_new = (int)((all->prms->plr.pos_y - SPEED * sin(angle) - D * nearbyint(sin
//			(angle))) /	SCALE);
//	j_new = (int)((all->prms->plr.pos_x + SPEED * cos(angle) + D * nearbyint(cos
//			(angle))) / SCALE);
	i_new = (int)((all->prms->plr.pos_y - (SPEED + D) * sin(angle)) / SCALE);
	j_new = (int)((all->prms->plr.pos_x + (SPEED + D) * cos(angle)) / SCALE);
	if (all->prms->map[i_new][j_cur] != '1' && all->prms->map[i_new][j_new] !=
	'1')
		all->prms->plr.pos_y -= SPEED * sin(angle);
	if (all->prms->map[i_cur][j_new] != '1' && all->prms->map[i_new][j_cur] != '1')
		all->prms->plr.pos_x += SPEED * cos(angle);
//	if (all->prms->map[i_new][j_new] == '1')
//	{
//		all->prms->plr.pos_x -= SPEED * cos(angle);
//		all->prms->plr.pos_y += SPEED * sin(angle);
//	}
	return (0);
}