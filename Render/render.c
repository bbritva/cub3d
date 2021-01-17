/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 13:08:11 by grvelva           #+#    #+#             */
/*   Updated: 2021/01/17 18:45:41 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"


void		my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char    *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
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

void 		draw_map(t_data *data, char *in_map)
{
	char **map;
	int i;
	int j;
	int k = 20;

	map = ft_split(in_map, '\n');
	i = 0;
	while (map[i/k])
	{
		j = 0;
		while (map[i/k][j/k])
		{
			if (map[i/k][j/k] == '1')
				my_mlx_pixel_put(data, j, i, 0x000000FF);
			if (map[i/k][j/k] == '0')
				my_mlx_pixel_put(data, j, i, 0x00FF0000);
			if (map[i/k][j/k] == '2')
				my_mlx_pixel_put(data, j, i, 0x0000FF00);
			if (map[i/k][j/k] == 'N')
				my_mlx_pixel_put(data, j, i, 0x00FFFFFF);
			j++;
		}
		i++;
	}
}

int             key_hook(int keycode, t_vars *vars)
{
	(void) vars;
	ft_putstr("Hello from key_hook!\n");
	ft_putnbr_fd(keycode, 1);
	ft_putstr("\n");
	if (keycode == 53)
		mlx_destroy_window(vars->mlx, vars->win);
	return (0);
}

int             mouse_hook(int button,int x,int y,t_vars *vars)
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

int             mouse_move_hook(int x, int y,t_vars *vars)
{
	(void) vars;
	ft_putstr("Mouse_moved!\n");
	ft_putnbr_fd(x, 1);
	ft_putstr("\n");
	ft_putnbr_fd(y, 1);
	ft_putstr("\n");
	return (0);
}

int     render_next_frame(void *YourStruct)
{
	(void) YourStruct;
	ft_putstr("Hello from loop_hook!\n");
	return (0);
}


void 	render(t_params	*params)
{
	t_data		img;
	t_vars 		vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, params->res_h, params->res_v, "cub3d");
	img.img = mlx_new_image(vars.mlx, params->res_h, params->res_v);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								 &img.endian);
	draw_map(&img, params->map);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_mouse_hook(vars.win, mouse_hook, &vars);
	mlx_hook(vars.win, 6, 1L << 6, mouse_move_hook, &vars);
//	mlx_loop_hook(vars.mlx, render_next_frame, &vars);
	mlx_loop(vars.mlx);
}

