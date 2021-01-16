/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 18:59:31 by grvelva           #+#    #+#             */
/*   Updated: 2021/01/16 15:16:55 by grvelva          ###   ########.fr       */
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
		draw_circle(&img, 300, 300, 250, 0x0000FF00);
		draw_line(&img, 400,300,400,900, 0x00FF0000);
		draw_map(&img, params->map);
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