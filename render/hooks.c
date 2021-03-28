/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 09:40:19 by grvelva           #+#    #+#             */
/*   Updated: 2021/03/24 10:43:13 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int			key_press(int keycode, t_all *all)
{
	if (keycode == 13)
		all->win->move_mask = all->win->move_mask | FORWARD;
	if (keycode == 0)
		all->win->move_mask = all->win->move_mask | MV_LEFT;
	if (keycode == 1)
		all->win->move_mask = all->win->move_mask | BACKWARD;
	if (keycode == 2)
		all->win->move_mask = all->win->move_mask | MV_RIGHT;
	if (keycode == 124)
		all->win->move_mask = all->win->move_mask | RT_LEFT;
	if (keycode == 123)
		all->win->move_mask = all->win->move_mask | RT_RIGHT;
	if (keycode == 53)
		all->win->move_mask = all->win->move_mask | ESC;
	return (0);
}

int			key_release(int keycode, t_all *all)
{
	if (keycode == 13)
		all->win->move_mask = all->win->move_mask & ~FORWARD;
	if (keycode == 0)
		all->win->move_mask = all->win->move_mask & ~MV_LEFT;
	if (keycode == 1)
		all->win->move_mask = all->win->move_mask & ~BACKWARD;
	if (keycode == 2)
		all->win->move_mask = all->win->move_mask & ~MV_RIGHT;
	if (keycode == 124)
		all->win->move_mask = all->win->move_mask & ~RT_LEFT;
	if (keycode == 123)
		all->win->move_mask = all->win->move_mask & ~RT_RIGHT;
	return (0);
}

int			render_next_frame(t_all *all)
{
	mlx_destroy_image(all->win->mlx, all->win->img);
	if (all->win->move_mask & FORWARD)
		move(all, all->prms->plr.ang_h);
	if (all->win->move_mask & MV_LEFT)
		move(all, all->prms->plr.ang_h + M_PI_2);
	if (all->win->move_mask & BACKWARD)
		move(all, all->prms->plr.ang_h + M_PI);
	if (all->win->move_mask & MV_RIGHT)
		move(all, all->prms->plr.ang_h - M_PI_2);
	if (all->win->move_mask & RT_LEFT)
		all->prms->plr.ang_h -= 0.06f;
	if (all->win->move_mask & RT_RIGHT)
		all->prms->plr.ang_h += 0.06f;
	if (all->win->move_mask & ESC)
		exit(0);
	all->prms->plr.ang_h -= (all->prms->plr.ang_h > M_PI * 2) ? M_PI * 2 : 0;
	all->prms->plr.ang_h += (all->prms->plr.ang_h < 0) ? M_PI * 2 : 0;
	create_img(all);
	mlx_put_image_to_window(all->win->mlx, all->win->win, all->win->img, 0, 0);
	return (1);
}

int			my_exit(t_all *all)
{
	(void)all;
	exit(0);
}
