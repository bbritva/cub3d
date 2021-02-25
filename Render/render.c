/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 13:08:11 by grvelva           #+#    #+#             */
/*   Updated: 2021/02/24 16:16:46 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void		my_pixel_put(t_win *win, int x, int y, unsigned int color)
{
	char    *dst;

	dst = win->addr + (y * win->line_l + x * (win->bpp / 8));
	*(unsigned int*)dst = color;
}

void 		*tex_init(t_all *all, char *path)
{
	t_tex *tex;

	if ((tex = ft_calloc(1, sizeof(t_tex))))
		if ((tex->img = mlx_xpm_file_to_image(all->win->mlx, path,
										&tex->w_tex, &tex->h_tex)))
		{
			tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_l,
										  &tex->en);
			return (tex);
		}
	return (NULL);
}

void 		start_game(t_all *all)
{
	//				mlx_mouse_hook(win->win, mouse_hook, win);
//				mlx_hook(win->win, 6, 1L << 6, mouse_move_hook, win);
	mlx_hook(all->win->win, 2, 1L << 0, key_press, all);
	mlx_hook(all->win->win, 3, 1L << 1, key_release, all);
	mlx_loop_hook(all->win->mlx, render_next_frame, all);
	mlx_loop(all->win->mlx);
}

int			free_tex(t_tex *tex, void *mlx)
{
	if (tex)
	{
		if (tex->img)
			mlx_destroy_image(mlx, tex->img);
		free(tex);
	}
	return (0);
}

int			free_window(t_all *all)
{
	if (all->win->north)
		free_tex(all->win->north, all->win->mlx);
	if (all->win->south)
		free_tex(all->win->south, all->win->mlx);
	if (all->win->west)
		free_tex(all->win->west, all->win->mlx);
	if (all->win->east)
		free_tex(all->win->east, all->win->mlx);
	if (all->win->sprite)
		free_tex(all->win->sprite, all->win->mlx);
	free(all);
	return (0);
}

int 		init_window(t_all * all)
{
	if ((all->win = (t_win *) ft_calloc(1, sizeof(t_win))) &&
		(all->win->mlx = mlx_init()) && (all->win->win = mlx_new_window
		(all->win->mlx, all->prms->res_h, all->prms->res_v, "cub3d")) &&
		(all->win->north = tex_init(all, all->prms->north)) &&
		(all->win->south = tex_init(all, all->prms->south)) &&
		(all->win->west = tex_init(all, all->prms->west)) &&
		(all->win->east = tex_init(all, all->prms->east)) &&
		(all->win->sprite = tex_init(all, all->prms->sprite)))
		return (1);
	return (0);
}

void		render(t_params *prms, int argc)
{
	t_all *all;

	if ((all = (t_all *)ft_calloc(1, sizeof(t_all))))
	{
		all->prms = prms;
		if (init_window(all))
		{
			create_img(all);
			all->win->move_mask = 0;
			if (argc == 2)
				start_game(all);
			else
				get_shot(all);
			free_window(all);
		free(all->win);
		} else
		{
			PUT_INIT_ERR_MSG
			free_window(all);
		}
	} else
		PUT_ALLOC_ERR_MSG
}
