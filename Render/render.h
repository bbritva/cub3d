/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 13:09:00 by grvelva           #+#    #+#             */
/*   Updated: 2021/02/02 10:34:14 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef RENDER_H
# define RENDER_H

# include <math.h>
# define SCALE 20
# define SCALE2 20
//# define SPEED 0.02f
# define SPEED 1.0f
# define FORWARD 0b100000
# define BACKWARD 0b10000
# define MV_LEFT 0b1000
# define MV_RIGHT 0b100
# define RT_LEFT 0b10
# define RT_RIGHT 0b1

typedef struct	s_win //структура для окна
{
	void			*mlx;
	void			*win;
	void			*img;
	void			*addr;
	int				line_l;
	int				bpp;
	int				en;
	unsigned int	move_mask;
	t_params		*prms;
}					t_win;

void		my_pixel_put(t_win *win, int x, int y, unsigned int	color);
int			get_height2(t_win *win, double angle);


#endif
