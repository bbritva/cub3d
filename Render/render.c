/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 13:08:11 by grvelva           #+#    #+#             */
/*   Updated: 2021/01/17 13:12:36 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <mlx.h>


void		my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char    *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
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

void 	render(t_params	*params)
{
	void *mlx;
	void *mlx_win;
	t_data img;


	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, params->res_h, params->res_v, "cub3d");
	img.img = mlx_new_image(mlx, params->res_h, params->res_v);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								 &img.endian);
	draw_map(&img, params->map);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}

