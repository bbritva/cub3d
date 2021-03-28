/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 11:00:28 by grvelva           #+#    #+#             */
/*   Updated: 2021/03/28 12:04:10 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d.h"

void		draw_map(t_all *all, int x, int y, int scale)
{
	int i;
	int j;

	i = 0;
	while (all->prms->map[i / scale] && i < all->prms->res_h)
	{
		j = 0;
		while (all->prms->map[i / scale][j / scale] && j < all->prms->res_v)
		{
			if (all->prms->map[i / scale][j / scale] == '1')
				my_pixel_put(all->win, j + x, i + y, 0x000000FF);
			j++;
		}
		i++;
	}
}

void		draw_player_on_map(t_all *all, int x_pos, int y_pos, int scale)
{
	t_player	p;
	int			x;
	int			y;
	int			a;
	int			b;

	p = all->prms->plr;
	p.pos_y *= scale;
	p.pos_x *= scale;
	x = (int)(p.pos_x - scale);
	while (x < p.pos_x + scale)
	{
		y = (int)(p.pos_y - scale);
		while (y < p.pos_y + scale)
		{
			a = (int)pow(scale, 2) / 4;
			b = (int)(pow(p.pos_x - x, 2) + pow(p.pos_y - y, 2));
			if (b < a)
				my_pixel_put(all->win, x + x_pos, y + y_pos, 0x00FFFFFF);
			y++;
		}
		x++;
	}
}

static void	calc_map_size(char **map, int *h_size, int *v_size)
{
	int tmp;

	*h_size = 0;
	*v_size = 0;
	while (map[*v_size])
	{
		tmp = 0;
		while (map[*v_size][tmp])
		{
			tmp++;
			*h_size = (tmp > *h_size) ? tmp : *h_size;
		}
		(*v_size)++;
	}
}

void		draw_minimap(t_all *all)
{
	int h_size;
	int v_size;
	int scale;

	calc_map_size(all->prms->map, &h_size, &v_size);
	scale = (h_size > v_size) ? (all->prms->res_h / (4 * h_size)) :
		(all->prms->res_h / (4 * v_size));
	draw_map(all, all->prms->res_h - h_size * scale - 5 - scale,
		all->prms->res_v - v_size * scale - 5 - scale, scale);
	draw_player_on_map(all, all->prms->res_h - h_size * scale - 5 - scale,
		all->prms->res_v - v_size * scale - 5 - scale, scale);
}
