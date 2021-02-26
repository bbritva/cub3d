/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_shot.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 13:11:28 by grvelva           #+#    #+#             */
/*   Updated: 2021/02/26 12:39:07 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

int 		num_to_bits(int size, int fd)
{
	unsigned char buff[4];

	buff[0] = (unsigned char) (size >> 24);
	buff[1] = (unsigned char) (size >> 16);
	buff[2] = (unsigned char) (size >> 8);
	buff[3] = (unsigned char) (size);
	return (write(fd, buff, 4));
}

int 		color_to_bits(int size, int fd)
{
	unsigned char buff[3];

	buff[0] = (unsigned char) (size >> 16);
	buff[1] = (unsigned char) (size >> 8);
	buff[2] = (unsigned char) (size);
	return (write(fd, buff, 3));
}

void 		get_shot(t_all *all)
{
	int		fd;
	int 	size;
	int 	i;
	int 	j;

	if ((fd = open("screenshot.bmp", O_CREAT | O_WRONLY | O_APPEND | O_TRUNC,
				0644)) > 0)
	{
		ft_putstr("open OK\n");
		size = 54 + (all->prms->res_h * all->prms->res_v * 3);
		if(write(fd, "BM", 2)) //записали тип файла
			ft_putstr("write type OK\n");
		if (num_to_bits(size, fd)) //записали размер файла
			ft_putstr("write size OK\n");
		if (num_to_bits(0, fd)) // записали 4 нуля
			ft_putstr("write 0000 OK\n");
		if (num_to_bits(54, fd)) // записали смещение до пикселей
			ft_putstr("write offBits OK\n");
		if (num_to_bits(40, fd)) // записали размер заголовка
			ft_putstr("write biSize OK\n");
		if (num_to_bits(all->prms->res_h, fd)) // записали ширину
			ft_putstr("write biWidth OK\n");
		if (num_to_bits(all->prms->res_v, fd)) // записали высоту
			ft_putstr("write biHeight OK\n");
		if (num_to_bits(1 << 16 | 24, fd)) // записали плэйн и бит_пер_пиксель
			ft_putstr("write biPlanes & biBitCount OK\n");
		if (num_to_bits(0, fd)) // записали тип сжатия (0)
			ft_putstr("write biCompression OK\n");
		if (num_to_bits(0, fd)) // записали размер (для несжатых он 0)
			ft_putstr("write biSizeImage OK\n");
		if (num_to_bits(0, fd)) // записали пиксели на метр по горизонтали
			ft_putstr("write biXPelsPerMeter OK\n");
		if (num_to_bits(0, fd)) // записали пиксели на метр по вертикали
			ft_putstr("write biYPelsPerMeter OK\n");
		if (num_to_bits(0, fd)) // записали кол-во цветов (0 для полной палитры)
			ft_putstr("write biClrUsed OK\n");
		if (num_to_bits(0, fd)) // записали важные цвета (0 для всех)
			ft_putstr("write biClrImportant OK\n");

		i = 0;
		while (i < all->prms->res_h)
		{
			j = 0;
			while (j < all->prms->res_v)
			{
				color_to_bits(0xFF0000, fd);
				j++;
			}
			i++;
		}

		close(fd);
	}

	(void) all;
	ft_putstr("get_shot\n");
}
