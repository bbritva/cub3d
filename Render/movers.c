/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movers.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 09:51:18 by grvelva           #+#    #+#             */
/*   Updated: 2021/02/09 11:55:14 by grvelva          ###   ########.fr       */
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

int			move_fwd(t_all *all)
{
	int i_cur;
	int j_cur;
	int i_new;
	int j_new;

	i_cur = (int)(all->prms->plr.pos_y / SCALE);
	j_cur = (int)(all->prms->plr.pos_x / SCALE);
	i_new = (int)((all->prms->plr.pos_y - (SPEED + D) * sin(all->prms->plr.ang_h)) / SCALE);
	j_new = (int)((all->prms->plr.pos_x + (SPEED + D) * cos(all->prms->plr.ang_h)) / SCALE);
	if (all->prms->map[i_new][j_cur] != '1')
		all->prms->plr.pos_y -= SPEED * sin(all->prms->plr.ang_h);
	if (all->prms->map[i_cur][j_new] != '1')
		all->prms->plr.pos_x += SPEED * cos(all->prms->plr.ang_h);
	return (0);
}

int			move_bwd(t_all *all)
{
	int i_cur;
	int j_cur;
	int i_new;
	int j_new;

	i_cur = (int)(all->prms->plr.pos_y / SCALE);
	j_cur = (int)(all->prms->plr.pos_x / SCALE);
	i_new = (int)((all->prms->plr.pos_y + (SPEED + D) * sin(all->prms->plr.ang_h)) / SCALE);
	j_new = (int)((all->prms->plr.pos_x - (SPEED + D) * cos(all->prms->plr.ang_h)) / SCALE);
	if (all->prms->map[i_new][j_cur] != '1')
		all->prms->plr.pos_y += SPEED * sin(all->prms->plr.ang_h);
	if (all->prms->map[i_cur][j_new] != '1')
		all->prms->plr.pos_x -= SPEED * cos(all->prms->plr.ang_h);
	return (0);
}

int			move_left(t_all *all)
{
	int		i_cur;
	int		j_cur;
	int		i_new;
	int		j_new;
	double	ang;

	ang = all->prms->plr.ang_h + M_PI_2;
	i_cur = (int)(all->prms->plr.pos_y / SCALE);
	j_cur = (int)(all->prms->plr.pos_x / SCALE);
	i_new = (int)((all->prms->plr.pos_y - (SPEED + D) * sin(ang)) / SCALE);
	j_new = (int)((all->prms->plr.pos_x + (SPEED + D) * cos(ang)) / SCALE);
	if (all->prms->map[i_new][j_cur] != '1')
		all->prms->plr.pos_y -= SPEED * sin(ang);
	if (all->prms->map[i_cur][j_new] != '1')
		all->prms->plr.pos_x += SPEED * cos(ang);
	return (0);
}

int			move_right(t_all *all)
{
	int		i_cur;
	int		j_cur;
	int		i_new;
	int		j_new;
	double	ang;

	ang = all->prms->plr.ang_h - M_PI_2;
	i_cur = (int)(all->prms->plr.pos_y / SCALE);
	j_cur = (int)(all->prms->plr.pos_x / SCALE);
	i_new = (int)((all->prms->plr.pos_y - (SPEED + D) * sin(ang)) / SCALE);
	j_new = (int)((all->prms->plr.pos_x + (SPEED + D) * cos(ang)) / SCALE);
	if (all->prms->map[i_new][j_cur] != '1')
		all->prms->plr.pos_y -= SPEED * sin(ang);
	if (all->prms->map[i_cur][j_new] != '1')
		all->prms->plr.pos_x += SPEED * cos(ang);
	return (0);
}