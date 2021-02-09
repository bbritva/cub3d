/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 13:08:11 by grvelva           #+#    #+#             */
/*   Updated: 2021/02/09 09:52:54 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <stdio.h>

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

void		render(t_all *all)
{
	if ((all->win = (t_win *)malloc(sizeof(t_win))))
	{
		all->win->mlx = mlx_init();
		all->win->win = mlx_new_window(all->win->mlx, all->prms->res_h,
								 all->prms->res_v, "cub3d");
		create_img(all);
		all->win->move_mask = 0;
//		mlx_mouse_hook(win->win, mouse_hook, win);
//		mlx_hook(win->win, 6, 1L << 6, mouse_move_hook, win);
		mlx_hook(all->win->win, 2, 1L << 0, key_press, all);
		mlx_hook(all->win->win, 3, 1L << 1, key_release, all);
		mlx_loop_hook(all->win->mlx, render_next_frame, all);
		mlx_loop(all->win->mlx);
//		free(all->win);
	}
}

