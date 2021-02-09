/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 09:59:41 by grvelva           #+#    #+#             */
/*   Updated: 2021/02/09 12:52:01 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int			is_wall(t_all *all, t_player p, double angle, char hv)
{
	int		x;
	int 	y;

	if (hv == 'h')
	{
		if (angle > 0 && angle < M_PI)
		{
			x = (int) p.pos_x;
			y = (int) (p.pos_y - 1);
		}
		else
		{
			x = (int) p.pos_x;
			y = (int) p.pos_y;
		}
	}
	else
	{
		if (angle > M_PI_2 && angle < 3 * M_PI_2)
		{
			x = (int) (p.pos_x - 1);
			y = (int) p.pos_y;
		}
		else
		{
			x = (int) p.pos_x;
			y = (int) p.pos_y;
		}
	}
	if (ft_strchr("02NSWE", all->prms->map[y][x]))
		return (0);
	return (1);
}

int			is_sprite(t_all *all, t_player p, double angle, char hv)
{
	int		x;
	int 	y;

	if (hv == 'h')
	{
		if (angle > 0 && angle < M_PI)
		{
			x = (int) p.pos_x;
			y = (int) (p.pos_y - 1);
		}
		else
		{
			x = (int) p.pos_x;
			y = (int) p.pos_y;
		}
	}
	else
	{
		if (angle > M_PI_2 && angle < 3 * M_PI_2)
		{
			x = (int) (p.pos_x - 1);
			y = (int) p.pos_y;
		}
		else
		{
			x = (int) p.pos_x;
			y = (int) p.pos_y;
		}
	}
	if (ft_strchr("10NSWE", all->prms->map[y][x]))
		return (0);
	return (1);
}