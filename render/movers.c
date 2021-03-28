/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movers.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 09:51:18 by grvelva           #+#    #+#             */
/*   Updated: 2021/03/24 10:43:13 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
	return (1);
}

int				move(t_all *all, double angle)
{
	double i_cur;
	double j_cur;
	double i_new;
	double j_new;

	i_cur = all->prms->plr.pos_y / SCALE;
	j_cur = all->prms->plr.pos_x / SCALE;
	i_new = (all->prms->plr.pos_y - SPEED * sin(angle)) / SCALE;
	j_new = (all->prms->plr.pos_x + SPEED * cos(angle)) / SCALE;
	if (can_step(all, i_new, j_cur))
		all->prms->plr.pos_y -= SPEED * sin(angle);
	if (can_step(all, i_cur, j_new))
		all->prms->plr.pos_x += SPEED * cos(angle);
	return (0);
}
