/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 14:32:27 by grvelva           #+#    #+#             */
/*   Updated: 2021/02/02 14:49:50 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

double		get_h_intersect(t_win *win, double angle)
{
	t_player	p;
	double		dist;
	double		dX;
	double		dY;

	p = *(win->prms->plr);
	if (angle > 0 && angle < M_PI)
	{
		p.pos_y = floor(p.pos_y / SCALE) * SCALE;
		p.pos_x += (p.pos_y - win->prms->plr->pos_y) / tan(angle);
		dY = 1 * SCALE;
	}
	else
	{
		p.pos_y = ceil(p.pos_y / SCALE) * SCALE;
		p.pos_x += (p.pos_y - win->prms->plr->pos_y) / tan(angle);
		dY = -1 * SCALE;
	}
	dX = dY / tan(angle);
	while (ft_strchr("02NSWE", win->prms->map[(int) (p.pos_y / SCALE)][(int)
	(p.pos_x / SCALE)]))
	{
		p.pos_x += dX;
		p.pos_y += dY;
	}
	dX = p.pos_x - win->prms->plr->pos_x;
	dY = p.pos_y - win->prms->plr->pos_y;
	dist = sqrt(dX * dX + dY * dY);
	return (dist);
}

double		get_v_intersect(t_win *win, double angle)
{
	t_player	p;
	double		dist;
	double		dX;
	double		dY;

	p = *(win->prms->plr);
	if (angle > 3 * M_PI_2 || angle < M_PI_2)
	{
		p.pos_x = ceil(p.pos_x / SCALE) * SCALE;
		p.pos_y += (p.pos_x - win->prms->plr->pos_x) * tan(angle);
		dX = 1 * SCALE;
	}
	else
	{
		p.pos_x = floor(p.pos_x / SCALE) * SCALE;
		p.pos_y += (p.pos_x - win->prms->plr->pos_x) * tan(angle);
		dX = -1 * SCALE;
	}
	dY = dX * tan(angle);
	while (ft_strchr("02NSWE", win->prms->map[(int) (p.pos_y / SCALE)][(int)
			(p.pos_x / SCALE)]))
	{
		p.pos_x += dX;
		p.pos_y += dY;
	}
	dX = p.pos_x - win->prms->plr->pos_x;
	dY = p.pos_y - win->prms->plr->pos_y;
	dist = sqrt(dX * dX + dY * dY);
	return (dist);
}


int		get_height2(t_win *win, double angle)
{
	int 		h;
	double		v_intesect;
	double		h_intesect;
	double		dist;

	v_intesect = get_v_intersect(win, angle);
	h_intesect = get_h_intersect(win, angle);
	dist = (h_intesect > v_intesect) ? v_intesect : h_intesect;
	dist *= cos(angle - win->prms->plr->ang_h);
	h = (int) (250 * SCALE / dist);
	return (h);
}