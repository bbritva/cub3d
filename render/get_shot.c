/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_shot.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 13:11:28 by grvelva           #+#    #+#             */
/*   Updated: 2021/03/24 10:43:13 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	get_clr(t_all *all, int x, int y)
{
	char	*src;
	int		color;

	src = all->win->addr + (y * all->win->line_l + x * (all->win->bpp / 8));
	color = *(int *)src;
	return (color);
}

static int	num_to_4bits(int size, int fd)
{
	unsigned char buff[4];

	buff[3] = (unsigned char)(size >> 24);
	buff[2] = (unsigned char)(size >> 16);
	buff[1] = (unsigned char)(size >> 8);
	buff[0] = (unsigned char)(size);
	return (write(fd, buff, 4));
}

static int	num_to_2bits(int size, int fd)
{
	unsigned char buff[2];

	buff[1] = (unsigned char)(size >> 8);
	buff[0] = (unsigned char)(size);
	return (write(fd, buff, 2));
}

static void	write_header(t_all *all, int fd)
{
	int	size;

	size = 54 + (all->prms->res_h * all->prms->res_v * 4);
	if (write(fd, "BM", 2) && num_to_4bits(size, fd) &&
		num_to_4bits(0, fd) && num_to_4bits(54, fd) &&
		num_to_4bits(40, fd) && num_to_4bits(all->prms->res_h, fd) &&
		num_to_4bits(all->prms->res_v, fd) && num_to_2bits(1, fd) &&
		num_to_2bits(32, fd) && num_to_4bits(0, fd) &&
		num_to_4bits(0, fd) && num_to_4bits(0, fd) &&
		num_to_4bits(0, fd) && num_to_4bits(0, fd) &&
		num_to_4bits(0, fd))
		ft_putstr("Write BMP-header done\n");
}

void		get_shot(t_all *all)
{
	int	fd;
	int	i;
	int	j;

	if ((fd = open("screenshot.bmp", O_CREAT | O_WRONLY | O_APPEND | O_TRUNC,
				0644)) > 0)
	{
		write_header(all, fd);
		i = 0;
		while (i < all->prms->res_v)
		{
			j = 0;
			while (j < all->prms->res_h)
				num_to_4bits(get_clr(all, j++, all->prms->res_v - i - 1), fd);
			i++;
		}
		ft_putstr("Write BMP-data done\n");
		close(fd);
	}
	else
		ft_putstr("Create/open file error\n");
}
