/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 18:59:31 by grvelva           #+#    #+#             */
/*   Updated: 2021/01/16 14:17:38 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <mlx.h>
#include <stdio.h>

void	show_parse_res(t_params * params);

void	params_free(t_params *params)
{
	if (params->sprite)
		free(params->sprite);
	if (params->north)
		free(params->north);
	if (params->south)
		free(params->south);
	if (params->west)
		free(params->west);
	if (params->east)
		free(params->east);
	if (params->map)
		free(params->map);
	free(params);
}

void	ft_putstr(char *str)
{
	while (*str != 0)
	{
		write(1, str, 1);
		str++;
	}
}

int		check_main_input(int argc)
{
	if (argc == 1)
	{
		ft_putstr(F_MISS_MSG);
		return (0);
	}
	if (argc > 2)
	{
		ft_putstr(M_ARGS_MSG);
		return (0);
	}
	return (1);
}

void		my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char    *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void		draw_circle(t_data *data, int x_c, int y_c, int r, int color)
{
	int cur_x;
	int cur_y;
	int k;

	(void) data;
	cur_x = x_c - r;
	while (cur_x < x_c + r)
	{
		cur_y = y_c - r;
		while (cur_y < y_c + r)
		{
			k = ((cur_y - y_c) * (cur_y - y_c) + (cur_x - x_c) * (cur_x - x_c))
					/ (r * r);
			printf("x = %d, y = %d, r= %d, k = %d\n", (cur_x - x_c), (cur_y -
			y_c), r, k);
			if (k < 1 && cur_y > 0 && cur_x > 0)
			{
				my_mlx_pixel_put(data, cur_x, cur_y, color);
			}
			cur_y++;
		}
		cur_x++;
	}
}

void		draw_circle2(t_data *data, int X1, int Y1, int r, int color)
{
	int x = 0;
	int y = r;
	int delta = 1 - 2 * r;
	int error;
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

int	main(int argc, char *argv[])
{
	t_params	*params;
	void		*mlx;
	void		*mlx_win;
	t_data		img;

	if (check_main_input(argc) && (params = parser(argv[1])))
	{
		printf("params - ok\n");
//		show_parse_res(params);
		mlx = mlx_init();
		mlx_win = mlx_new_window(mlx, params->res_h, params->res_v, "cub3d");
		img.img = mlx_new_image(mlx, params->res_h, params->res_v);
		img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
									 &img.endian);
//		my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
		draw_circle2(&img, 300, 300, 250, 0x0000FF00);
		mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
		mlx_loop(mlx);
		params_free(params);
	}
	else
		printf("params error\n");
}

void	show_parse_res(t_params * params)
{
	printf("hrez = %d\n", params->res_h);
	printf("vrez = %d\n", params->res_v);
	printf("north = \"%s\"\n", params->north);
	printf("south = \"%s\"\n", params->south);
	printf("west = \"%s\"\n", params->west);
	printf("east = \"%s\"\n", params->east);
	printf("sprite = \"%s\"\n", params->sprite);
	printf("f_color_r = %d\n", params->floor_color.red);
	printf("f_color_g = %d\n", params->floor_color.green);
	printf("f_color_b = %d\n", params->floor_color.blue);
	printf("c_color_r = %d\n", params->ceil_color.red);
	printf("c_color_g = %d\n", params->ceil_color.green);
	printf("c_color_b = %d\n", params->ceil_color.blue);
	printf("map:\n%s\n", params->map);
}