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

int			move_fwd(t_all *all)
{
	int i_cur;
	int j_cur;
	int i_new;
	int j_new;

	i_cur = (int)(all->plr.pos_y / SCALE);
	j_cur = (int)(all->plr.pos_x / SCALE);
	i_new = (int)((all->plr.pos_y - (SPEED + D) * sin(all->plr.ang_h)) / SCALE);
	j_new = (int)((all->plr.pos_x + (SPEED + D) * cos(all->plr.ang_h)) / SCALE);
	if (all->prms->map[i_new][j_cur] != '1')
		all->plr.pos_y -= SPEED * sin(all->plr.ang_h);
	if (all->prms->map[i_cur][j_new] != '1')
		all->plr.pos_x += SPEED * cos(all->plr.ang_h);
	return (0);
}

int			move_bwd(t_all *all)
{
	int i_cur;
	int j_cur;
	int i_new;
	int j_new;

	i_cur = (int)(all->plr.pos_y / SCALE);
	j_cur = (int)(all->plr.pos_x / SCALE);
	i_new = (int)((all->plr.pos_y + (SPEED + D) * sin(all->plr.ang_h)) / SCALE);
	j_new = (int)((all->plr.pos_x - (SPEED + D) * cos(all->plr.ang_h)) / SCALE);
	if (all->prms->map[i_new][j_cur] != '1')
		all->plr.pos_y += SPEED * sin(all->plr.ang_h);
	if (all->prms->map[i_cur][j_new] != '1')
		all->plr.pos_x -= SPEED * cos(all->plr.ang_h);
	return (0);
}

int			move_left(t_all *all)
{
	int		i_cur;
	int		j_cur;
	int		i_new;
	int		j_new;
	double	ang;

	ang = all->plr.ang_h + M_PI_2;
	i_cur = (int)(all->plr.pos_y / SCALE);
	j_cur = (int)(all->plr.pos_x / SCALE);
	i_new = (int)((all->plr.pos_y - (SPEED + D) * sin(ang)) / SCALE);
	j_new = (int)((all->plr.pos_x + (SPEED + D) * cos(ang)) / SCALE);
	if (all->prms->map[i_new][j_cur] != '1')
		all->plr.pos_y -= SPEED * sin(ang);
	if (all->prms->map[i_cur][j_new] != '1')
		all->plr.pos_x += SPEED * cos(ang);
	return (0);
}

int			move_right(t_all *all)
{
	int		i_cur;
	int		j_cur;
	int		i_new;
	int		j_new;
	double	ang;

	ang = all->plr.ang_h - M_PI_2;
	i_cur = (int)(all->plr.pos_y / SCALE);
	j_cur = (int)(all->plr.pos_x / SCALE);
	i_new = (int)((all->plr.pos_y - (SPEED + D) * sin(ang)) / SCALE);
	j_new = (int)((all->plr.pos_x + (SPEED + D) * cos(ang)) / SCALE);
	if (all->prms->map[i_new][j_cur] != '1')
		all->plr.pos_y -= SPEED * sin(ang);
	if (all->prms->map[i_cur][j_new] != '1')
		all->plr.pos_x += SPEED * cos(ang);
	return (0);
}