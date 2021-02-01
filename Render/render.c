/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 13:08:11 by grvelva           #+#    #+#             */
/*   Updated: 2021/02/01 18:35:15 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void		my_pixel_put(t_win *win, int x, int y, unsigned int color)
{
	char    *dst;

	dst = win->addr + (y * win->line_l + x * (win->bpp / 8));
	*(unsigned int*)dst = color;
}

unsigned int	ctoi(t_color color)
{
	return(color.red << 16 | color.green << 8 | color.blue);
}

void 		draw_fc(t_win *win)
{
	int i;
	int j;

	i = 0;
	while (i < win->prms->res_v / 2)
	{
		j = 0;
		while (j < win->prms->res_h)
			my_pixel_put(win, j++, i, ctoi(win->prms->ceil_color));
		i++;
	}
	while (i < win->prms->res_v)
	{
		j = 0;
		while (j < win->prms->res_h)
			my_pixel_put(win, j++, i, ctoi(win->prms->floor_color));
		i++;
	}
}

void 		draw_line(t_win *win, int x_pos, int h)
{
	int i;

	if (h > win->prms->res_v)
		h = win->prms->res_v;
	i = (win->prms->res_v - h) / 2;
	while (i < (win->prms->res_v + h) / 2)
		my_pixel_put(win, x_pos, i++, 0x00007864);
}

void 		draw_map(t_win *win, char **map)
{
	int i;
	int j;

	i = 0;
	while (map[i/SCALE2])
	{
		j = 0;
		while (map[i/SCALE2][j/SCALE2])
		{
			if (map[i/SCALE2][j/SCALE2] == '1')
				my_pixel_put(win, j, i, 0x000000FF);
			if (map[i/SCALE2][j/SCALE2] == '0')
				my_pixel_put(win, j, i, 0x00FF0000);
			if (map[i/SCALE2][j/SCALE2] == '2')
				my_pixel_put(win, j, i, 0x0000FF00);
			if (ft_strchr("NSEW", map[i/SCALE2][j/SCALE2]))
				my_pixel_put(win, j, i, 0x00FF0000);
			j++;
		}
		i++;
	}
}

void		draw_player(t_win *win, t_params *params)
{
	t_player	p;
	double		end_angle;
	double		angle;

	angle = params->plr->ang_h - 33 * (M_PI / 180);
	end_angle = params->plr->ang_h + 33 * (M_PI / 180);
	while (angle < end_angle)
	{
		p.pos_x = params->plr->pos_x;
		p.pos_y = params->plr->pos_y;
		while (params->map[(int) (p.pos_y / SCALE2)][(int) (p.pos_x / SCALE2)]
		&& params->map[(int) (p.pos_y / SCALE2)][(int) (p.pos_x / SCALE2)] != '1')
		{
			p.pos_x += cos(angle);
			p.pos_y -= sin(angle);
			my_pixel_put(win, (int) p.pos_x, (int) p.pos_y, 0x00FFFFFF);
		}
		angle += 66 * (M_PI / 180) / 640;
	}
}

int		get_height(t_win *win, double angle)
{
	t_player	p;
	int			h;
	double 		k;


	p = *(win->prms->plr);
	while (win->prms->map[(int) (p.pos_y / SCALE)][(int) (p.pos_x / SCALE)]
	!= '1' && win->prms->map[(int) (p.pos_y / SCALE)][(int) (p.pos_x /
															 SCALE)])
	{
		p.pos_x += 0.05f * cos(angle);
		p.pos_y -= 0.05f * sin(angle);
	}
	p.pos_x -= win->prms->plr->pos_x;
	p.pos_y -= win->prms->plr->pos_y;
	k = cos(angle - win->prms->plr->ang_h);
	h = (int) (100 / (sqrt((p.pos_x * p.pos_x) + (p.pos_y * p.pos_y)) * k));
	return (h);
}

void 		draw_view(t_win *win)
{
	int		i;
	double	angle;

	i = 0;
	while (i < win->prms->res_h)
	{
		angle = win->prms->plr->ang_h + M_PI_4 - i * (M_PI_2 /
													  win->prms->res_h);
		draw_line(win, i, get_height(win, angle));
		i += 10;
	}

}

int		create_img(t_params *params, t_win *win)
{
	win->img = mlx_new_image(win->mlx, params->res_h, params->res_v);
	win->addr = mlx_get_data_addr(win->img, &win->bpp,
								  &win->line_l, &win->en);
	draw_fc(win);
	draw_map(win, params->map);
//	draw_player(win, params);
	draw_view(win);
	return (0);
}

int			key_press(int keycode, t_win *win)
{
	if (keycode == 13)
		win->move_mask = win->move_mask | FORWARD;
	if (keycode == 0)
		win->move_mask = win->move_mask | MV_LEFT;
	if (keycode == 1)
		win->move_mask = win->move_mask | BACKWARD;
	if (keycode == 2)
		win->move_mask = win->move_mask | MV_RIGHT;
	if (keycode == 124)
		win->move_mask = win->move_mask | RT_LEFT;
	if (keycode == 123)
		win->move_mask = win->move_mask | RT_RIGHT;
	if (keycode == 53)
	{
		mlx_destroy_image(win->mlx, win->img);
		mlx_destroy_window(win->mlx, win->win);
	}
	return (0);
}

int			key_release(int keycode, t_win *win)
{
	if (keycode == 13)
		win->move_mask = win->move_mask - FORWARD;
	if (keycode == 0)
		win->move_mask = win->move_mask - MV_LEFT;
	if (keycode == 1)
		win->move_mask = win->move_mask - BACKWARD;
	if (keycode == 2)
		win->move_mask = win->move_mask - MV_RIGHT;
	if (keycode == 124)
		win->move_mask = win->move_mask - RT_LEFT;
	if (keycode == 123)
		win->move_mask = win->move_mask - RT_RIGHT;
	return (0);
}

int			mouse_hook(int button, int x, int y, t_win *win)
{
	(void) win;
	ft_putstr("Hello from mouse_hook!\n");
	ft_putnbr_fd(x, 1);
	ft_putstr("\n");
	ft_putnbr_fd(y, 1);
	ft_putstr("\n");
	ft_putnbr_fd(button, 1);
	ft_putstr("\n");
	return (0);
}

int			mouse_move_hook(int x, int y, t_win *win)
{
	(void) win;
	ft_putstr("Mouse_moved!\n");
	ft_putnbr_fd(x, 1);
	ft_putstr("\n");
	ft_putnbr_fd(y, 1);
	ft_putstr("\n");
	return (0);
}

int			move_fwd(t_win *win)
{
	int i_cur;
	int j_cur;
	int i_new;
	int j_new;
	t_player p;

	p = *(win->prms->plr);
	i_cur = (int)(p.pos_y / SCALE);
	j_cur = (int)(p.pos_x / SCALE);
	i_new = (int)((p.pos_y - SPEED * sin(p.ang_h)) / SCALE);
	j_new = (int)((p.pos_x + SPEED * cos(p.ang_h)) / SCALE);
	if (win->prms->map[i_new][j_cur] != '1')
		win->prms->plr->pos_y -= SPEED * sin(p.ang_h);
	if (win->prms->map[i_cur][j_new] != '1')
		win->prms->plr->pos_x += SPEED * cos(p.ang_h);
	return (0);
}

int			move_bwd(t_win *win)
{
	int i_cur;
	int j_cur;
	int i_new;
	int j_new;
	t_player p;

	p = *(win->prms->plr);
	i_cur = (int)(p.pos_y / SCALE);
	j_cur = (int)(p.pos_x / SCALE);
	i_new = (int)((p.pos_y + sin(p.ang_h)) / SCALE);
	j_new = (int)((p.pos_x - cos(p.ang_h)) / SCALE);
	if (win->prms->map[i_new][j_cur] != '1')
		win->prms->plr->pos_y += SPEED * sin(p.ang_h);
	if (win->prms->map[i_cur][j_new] != '1')
		win->prms->plr->pos_x -= SPEED * cos(p.ang_h);
	return (0);
}

int			move_left(t_win *win)
{
	int i_cur;
	int j_cur;
	int i_new;
	int j_new;
	t_player p;

	p = *(win->prms->plr);
	p.ang_h += M_PI_2;
	i_cur = (int)(p.pos_y / SCALE);
	j_cur = (int)(p.pos_x / SCALE);
	i_new = (int)((p.pos_y - sin(p.ang_h)) / SCALE);
	j_new = (int)((p.pos_x + cos(p.ang_h)) / SCALE);
	if (win->prms->map[i_new][j_cur] != '1')
		win->prms->plr->pos_y -= SPEED * sin(p.ang_h);
	if (win->prms->map[i_cur][j_new] != '1')
		win->prms->plr->pos_x += SPEED * cos(p.ang_h);
	return (0);
}

int			move_right(t_win *win)
{
	int i_cur;
	int j_cur;
	int i_new;
	int j_new;
	t_player p;

	p = *(win->prms->plr);
	p.ang_h -= M_PI_2;
	i_cur = (int)(p.pos_y / SCALE);
	j_cur = (int)(p.pos_x / SCALE);
	i_new = (int)((p.pos_y - sin(p.ang_h)) / SCALE);
	j_new = (int)((p.pos_x + cos(p.ang_h)) / SCALE);
	if (win->prms->map[i_new][j_cur] != '1')
		win->prms->plr->pos_y -= SPEED * sin(p.ang_h);
	if (win->prms->map[i_cur][j_new] != '1')
		win->prms->plr->pos_x += SPEED * cos(p.ang_h);
	return (0);
}

int			render_next_frame(t_win *win)
{
	mlx_destroy_image(win->mlx, win->img);
	if (win->move_mask & FORWARD)
		move_fwd(win);
	if (win->move_mask & MV_LEFT)
		move_left(win);
	if (win->move_mask & BACKWARD)
		move_bwd(win);
	if (win->move_mask & MV_RIGHT)
		move_right(win);
	if (win->move_mask & RT_LEFT)
		win->prms->plr->ang_h -= 0.03f;
	if (win->move_mask & RT_RIGHT)
		win->prms->plr->ang_h += 0.03f;
	win->prms->plr->ang_h -= (win->prms->plr->ang_h > M_PI * 2)	? M_PI * 2 : 0;
	win->prms->plr->ang_h += (win->prms->plr->ang_h < 0) ? M_PI * 2 : 0;
	create_img(win->prms, win);
	mlx_put_image_to_window(win->mlx, win->win, win->img, 0, 0);
	return (1);
}

void		render(t_params	*params)
{
	t_win		*win;

	if ((win = (t_win *)malloc(sizeof(t_win))))
	{
		win->mlx = mlx_init();
		win->win = mlx_new_window(win->mlx, params->res_h, params->res_v,
								  "cub3d");
		win->prms = params;
		create_img(params, win);
		win->move_mask = 0;
//		mlx_key_hook(win->win, key_hook, win);
//		mlx_mouse_hook(win->win, mouse_hook, win);
//		mlx_hook(win->win, 6, 1L << 6, mouse_move_hook, win);
		mlx_hook(win->win, 2, 1L << 0, key_press, win);
		mlx_hook(win->win, 3, 1L << 1, key_release, win);
		mlx_loop_hook(win->mlx, render_next_frame, win);
		mlx_put_image_to_window(win->mlx, win->win, win->img, 0, 0);
		mlx_loop(win->mlx);
	}
}

