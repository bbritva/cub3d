/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 13:08:11 by grvelva           #+#    #+#             */
/*   Updated: 2021/01/23 18:27:54 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"


void		my_mlx_pixel_put(t_win *win, int x, int y, int color)
{
	char    *dst;

	dst = win->addr + (y * win->line_l + x * (win->bpp / 8));
	*(unsigned int*)dst = color;
}

void 		draw_map(t_win *win, char **map)
{
	int i;
	int j;
	int k = 20;

	i = 0;
	while (map[i/k])
	{
		j = 0;
		while (map[i/k][j/k])
		{
			if (map[i/k][j/k] == '1')
				my_mlx_pixel_put(win, j, i, 0x000000FF);
			if (map[i/k][j/k] == '0')
				my_mlx_pixel_put(win, j, i, 0x00FF0000);
			if (map[i/k][j/k] == '2')
				my_mlx_pixel_put(win, j, i, 0x0000FF00);
			if (map[i/k][j/k] == 'N')
				my_mlx_pixel_put(win, j, i, 0x00FF0000);
			j++;
		}
		i++;
	}
}

void		draw_player(t_win *win, t_player *p)
{
	int k;
	int i;
	int j;

	k = 20;
	i = 0;
	while (i < k)
	{
		j = 0;
		while (j < k)
		{
			my_mlx_pixel_put(win, j + p->pos_x * k, i + p->pos_y * k,
					0x00FFFFFF);
			j++;
		}
		i++;
	}
}


int			key_hook(int keycode, t_vars *vars, t_player *p)
{
	(void) vars;
	ft_putstr("Hello from key_hook!\n");
	ft_putnbr_fd(keycode, 1);
	ft_putstr("\n");
	if (keycode == 126)
		p->pos_y--;
	if (keycode == 53)
		mlx_destroy_window(vars->mlx, vars->win);
	return (0);
}

int			mouse_hook(int button,int x,int y,t_vars *vars)
{
	(void) vars;
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

int			render_next_frame(t_win *win, t_params *params)
{
	draw_map(win->img, params->map);
	draw_player(win->img, params->player);
	mlx_put_image_to_window(win->mlx, win->win, win->img, 0, 0);
	ft_putstr("Hello from loop_hook!\n");
	return (0);
}


void		render(t_params	*params)
{
	t_win		*win;

	if ((win = (t_win *)malloc(sizeof(t_win))))
	{
		win->mlx = mlx_init();
		win->win = mlx_new_window(win->mlx, params->res_h, params->res_v,
								  "cub3d");
		win->img = mlx_new_image(win->mlx, params->res_h, params->res_v);
		win->addr = mlx_get_data_addr(win->img, &win->bpp,
									 &win->line_l, &win->en);
		draw_map(win, params->map);
		draw_player(win, params->player);
		mlx_put_image_to_window(win->mlx, win->win, win->img, 0, 0);
		mlx_key_hook(win->win, key_hook, win);
		mlx_mouse_hook(win->win, mouse_hook, win);
		mlx_hook(win->win, 6, 1L << 6, mouse_move_hook, win);
		mlx_loop_hook(win->mlx, render_next_frame, win);
		mlx_loop(win->mlx);
		free(win);
	}
}

