/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_movers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 09:51:18 by grvelva           #+#    #+#             */
/*   Updated: 2021/03/31 09:56:29 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d.h"

static int		is_z_near(t_all *all, double i, double j, int index)
{
	double dist;

	if (index == 0)
		return (0);
	dist = pow(i - all->prms->sprites[index - 1]->pos_y, 2) +
		pow(j - all->prms->sprites[index - 1]->pos_x, 2);
	return (dist < pow(0.4, 2) &&
			((all->prms->sprites[index - 1]->status_mask & Z_ALIVE) ||
			(all->prms->sprites[index - 1]->status_mask & Z_BARREL)));
}

static int		can_step(t_all *all, double i, double j, int index)
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
	return (!is_z_near(all, i, j, index));
}

static int		move_z(t_all *all, double ang, int index)
{
	double i_cur;
	double j_cur;
	double i_new;
	double j_new;

	i_cur = all->prms->sprites[index]->pos_y;
	j_cur = all->prms->sprites[index]->pos_x;
	i_new = (i_cur - SPEED_Z * sin(ang));
	j_new = (j_cur + SPEED_Z * cos(ang));
	if (can_step(all, i_new, j_cur, index))
		all->prms->sprites[index]->pos_y -= SPEED_Z * sin(ang);
	if (can_step(all, i_cur, j_new, index))
		all->prms->sprites[index]->pos_x += SPEED_Z * cos(ang);
	return (0);
}

static void		bite(t_all *all)
{
	all->win->move_mask = all->win->move_mask | IS_BITTEN;
	all->prms->plr.health -= (all->prms->plr.health > 0) ? 20 : 0;
	system("afplay resources/sounds/bite.mp3 &");
}

void			move_zombies(t_all *all)
{
	static int	count = 0;
	int			i;

	count++;
	all->win->move_mask = all->win->move_mask & ~(IS_BITTEN);
	if (!all->prms->sprites || !all->prms->sprites[0])
		return ;
	i = 0;
	while (all->prms->sprites[i])
	{
		if (all->prms->sprites[i]->dist > (0.5) &&
				all->prms->sprites[i]->status_mask & Z_GOING &&
				all->prms->sprites[i]->status_mask & Z_ALIVE &&
				!(all->prms->sprites[i]->status_mask & Z_DOOR))
			move_z(all, all->prms->sprites[i]->angle + M_PI, i);
		i++;
	}
	if (all->prms->sprites[0]->dist < 0.6 && count % 10 == 0 &&
		all->prms->plr.health && all->prms->sprites[0]->status_mask & Z_ALIVE &&
		!(all->prms->sprites[0]->status_mask & Z_DOOR))
		bite(all);
	count = (count > 10 || all->prms->sprites[0]->dist > 0.6) ? 0 : count;
}
