//
// Created by Gregorio Velva on 1/17/21.
//

#include "cub3d.h"

void		draw_line(t_data *data, int x0, int y0, int x1, int y1, int color)
{
	int deltax = x1 - x0;
	int deltay = y1 - y0;
	int error = 0;
	int deltaerr = deltay + 1;
	int y = y0;
	int x = x0;
	int diry = y1 - y0;
	if (diry > 0)
		diry = 1;
	if (diry < 0)
		diry = -1;
	while (x <= x1)
	{
		my_mlx_pixel_put(data, x, y, color);
		error = error + deltaerr;
		if (error >= (deltax + 1))
		{
			y = y + diry;
			error = error - (deltax + 1);
		}
		x++;
	}
}

void		draw_circle(t_data *data, int X1, int Y1, int r, int color)
{
	int x = 0;
	int y = r;
	int delta = 1 - 2 * r;
	int error;

	(void) color;
	while (y >= 0)
	{
		my_mlx_pixel_put(data, X1 + x, Y1 + y, color);
		my_mlx_pixel_put(data, X1 + x, Y1 - y, color);
		my_mlx_pixel_put(data, X1 - x, Y1 + y, color);
		my_mlx_pixel_put(data, X1 - x, Y1 - y, color);

		error = 2 * (delta + y) - 1;
		if ((delta < 0) && (error <= 0))
			delta += 2 * ++x + 1;
		else
		if ((delta > 0) && (error > 0))
			delta -= 2 * --y + 1;
		else
			delta += 2 * (++x - --y);
	}
}

void 	draw_rainbow(t_data *data)
{
	int i;
	int j;
	int color;

	i = 0;
	while (i < 255)
	{
		j = 0;
		while (j < 255)
		{
			color = 0x00000000;
			color = color | ((j) << 8);
			color = color | ((255 - j) << 16);
			color = color | (255 - i);
			my_mlx_pixel_put(data, j, i, color);
			j++;
		}
		i++;
	}
}



void		draw_player(t_all *all)
{
	t_player	p;
	double		angle;
	int 		i;

	i = 0;
	while (i < 50)
	{
		angle = all->plr.ang_h + M_PI / 6 - i * (M_PI / (3 * 50));
		p.pos_x = all->plr.pos_x * SCALE2;
		p.pos_y = all->plr.pos_y * SCALE2;
		while (all->prms->map[(int) (p.pos_y / SCALE2)][(int) (p.pos_x / SCALE2)] != '1')
		{
			p.pos_x += SPEED * cos(angle);
			p.pos_y -= SPEED * sin(angle);
			my_pixel_put(all->win, (int) p.pos_x, (int) p.pos_y, 0x00FFFFFF);
		}
		i++;
	}
}

void 		draw_line(t_all *all, int x_pos, int h)
{
	int i;
	int color;

	color = 0x00FFFFFF;
	if (h & NORTH)
		color = 0x000000FF;
	if (h & SOUTH)
		color = 0x00FF0000;
	if (h & WEST)
		color = 0x0000FF00;
	if (h & EAST)
		color = 0x00999999;
	h = h & ~(0b1111 << 12);
	if (h > all->prms->res_v)
		h = all->prms->res_v;
	i = (all->prms->res_v - h) / 2;
	while (i < (all->prms->res_v + h) / 2)
		my_pixel_put(all->win, x_pos, i++, color);
}