/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 14:32:27 by grvelva           #+#    #+#             */
/*   Updated: 2021/02/06 15:42:45 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

double		get_h_intersect(t_player *plr, double angle)
{
	t_player	p;

	p = *plr;
	if (angle > 0 && angle < M_PI)
	{
		if (p.pos_y == floor(p.pos_y))
			p.pos_y--;
		else
			p.pos_y = floor(p.pos_y);
		p.pos_x += (p.pos_y - plr->pos_y) / tan(angle);
	}
	else
	{
		if (p.pos_y == ceil(p.pos_y))
			p.pos_y++;
		else
			p.pos_y = ceil(p.pos_y);
		p.pos_x += (p.pos_y - plr->pos_y) / tan(angle);
	}
	return (p.pos_x - plr->pos_x);
}

double		get_v_intersect(t_player *plr, double angle)
{
	t_player	p;

	p = *plr;
	if (angle > 3 * M_PI_2 || angle < M_PI_2)
	{
		if (p.pos_x == ceil(p.pos_x))
			p.pos_x++;
		else
			p.pos_x = ceil(p.pos_x);
		p.pos_y += (p.pos_x - plr->pos_x) * tan(angle);
	}
	else
	{
		if (p.pos_x == floor(p.pos_x))
			p.pos_x--;
		else
			p.pos_x = floor(p.pos_x);
		p.pos_y += (p.pos_x - plr->pos_x) * tan(angle);
	}
	return (p.pos_y - plr->pos_y);
}


int		get_height2(t_win *win, double angle)
{
	int 		h;
	double		v_intesect;
	double		h_intesect;
	double		dist;
	t_player	p;
	double		dX;
	double		dY;
//	double		first_step_X;
//	double		first_step_Y;

	p = *(win->prms->plr);
	while (ft_strchr("02NSWE", win->prms->map[(int) p.pos_y][(int) p.pos_x]))
	{
		v_intesect = get_v_intersect(&p, angle);
		h_intesect = get_h_intersect(&p, angle);
		if (h_intesect > v_intesect)
		{
			p.pos_x += v_intesect;
			p.pos_y -= h_intesect * tan(angle);
		}
		else
		{
			p.pos_y += h_intesect;
			p.pos_x -= v_intesect * tan(angle);
		}
	}
	dX = p.pos_x - win->prms->plr->pos_x;
	dY = p.pos_y - win->prms->plr->pos_y;
	dist = dX * cos(angle) + dY * sin(angle);
	dist *= cos(angle - win->prms->plr->ang_h);
	h = (int) (250 * SCALE / dist);
	return (h);
}