/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 13:08:11 by grvelva           #+#    #+#             */
/*   Updated: 2021/02/09 10:36:54 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void		my_pixel_put(t_win *win, int x, int y, unsigned int color)
{
	char    *dst;

	dst = win->addr + (y * win->line_l + x * (win->bpp / 8));
	*(unsigned int*)dst = color;
}

void		render(t_all *all)
{
	if ((all->win = (t_win *)malloc(sizeof(t_win))))
	{
		all->win->mlx = mlx_init();
		all->win->win = mlx_new_window(all->win->mlx, all->prms->res_h,
								 all->prms->res_v, "cub3d");
		all->win->north = malloc(sizeof (t_tex));
		all->win->north->img = mlx_xpm_file_to_image(all->win->mlx,
			all->prms->north,&all->win->north->w_tex, &all->win->north->h_tex);
		all->win->north->addr = mlx_get_data_addr(all->win->north->img,
			&all->win->north->bpp, &all->win->north->line_l,
			&all->win->north->en);

		all->win->south = malloc(sizeof (t_tex));
		all->win->south->img = mlx_xpm_file_to_image(all->win->mlx,
			all->prms->south,&all->win->south->w_tex, &all->win->south->h_tex);
		all->win->south->addr = mlx_get_data_addr(all->win->south->img,
			&all->win->south->bpp, &all->win->south->line_l,
			&all->win->south->en);

		all->win->west = malloc(sizeof (t_tex));
		all->win->west->img = mlx_xpm_file_to_image(all->win->mlx,
			all->prms->west,&all->win->west->w_tex, &all->win->west->h_tex);
		all->win->west->addr = mlx_get_data_addr(all->win->west->img,
			&all->win->west->bpp, &all->win->west->line_l,
			&all->win->west->en);

		all->win->east = malloc(sizeof (t_tex));
		all->win->east->img = mlx_xpm_file_to_image(all->win->mlx,
			all->prms->east,&all->win->east->w_tex, &all->win->east->h_tex);
		all->win->east->addr = mlx_get_data_addr(all->win->east->img,
			&all->win->east->bpp, &all->win->east->line_l,
			&all->win->east->en);

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

