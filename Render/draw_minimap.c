/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 18:11:20 by grvelva           #+#    #+#             */
/*   Updated: 2021/02/27 18:18:25 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	draw_map(t_win *win, char **map)
{
	int i;
	int j;

	i = 0;
	while (map[i / SCALE2])
	{
		j = 0;
		while (map[i / SCALE2][j / SCALE2])
		{
			if (map[i / SCALE2][j / SCALE2] == '1')
				my_pixel_put(win, j, i, 0x000000FF);
			if (map[i / SCALE2][j / SCALE2] == '0')
				my_pixel_put(win, j, i, 0x00FF0000);
			if (map[i / SCALE2][j / SCALE2] == '2')
				my_pixel_put(win, j, i, 0x0000FF00);
			if (ft_strchr("NSEW", map[i / SCALE2][j / SCALE2]))
				my_pixel_put(win, j, i, 0x00FF0000);
			j++;
		}
		i++;
	}
}

static void	draw_player(t_all *all)
{
	t_player	p;
	int			i;

	i = 0;
	p = all->prms->plr;
	p.pos_x *= SCALE2;
	p.pos_y *= SCALE2;
	while (i < 10)
	{
		p.pos_x += cos(p.ang_h);
		p.pos_y -= sin(p.ang_h);
		my_pixel_put(all->win, (int)p.pos_x, (int)p.pos_y, 0x00FFFFFF);
		i++;
	}
}

static void	draw_player_on_map(t_all *all)
{
	t_player	p;
	int			x;
	int			y;
	int			a;
	int			b;

	p = all->prms->plr;
	p.pos_y *= SCALE2;
	p.pos_x *= SCALE2;
	x = (int)(p.pos_x - SCALE2);
	while (x < p.pos_x + SCALE2)
	{
		y = (int)(p.pos_y - SCALE2);
		while (y < p.pos_y + SCALE2)
		{
			a = (int)pow(SCALE2, 2) / 8;
			b = (int)(pow(p.pos_x - x, 2) + pow(p.pos_y - y, 2));
			if (b < a)
				my_pixel_put(all->win, x, y, 0x00FFFFFF);
			y++;
		}
		x++;
	}
}

void		draw_minimap(t_all *all)
{
	draw_map(all->win, all->prms->map);
	draw_player_on_map(all);
	draw_player(all);
}
