/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbritva <bbritva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 13:09:00 by grvelva           #+#    #+#             */
/*   Updated: 2021/02/21 10:40:25 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef RENDER_H
# define RENDER_H

# include <math.h>
# include <mlx.h>
# include "../cub3d.h"
# define PUT_INIT_ERR_MSG ft_putstr("Initialization error\n");
# define SCALE 1
# define SCALE2 20
# define SPEED 0.1f
# define ESC 64
# define FORWARD 32
# define BACKWARD 16
# define MV_LEFT 8
# define MV_RIGHT 4
# define RT_LEFT 2
# define RT_RIGHT 1
# define D 0.1f
# define NORTH 1 << 26
# define SOUTH 1 << 27
# define WEST 1 << 28
# define EAST 1 << 29

typedef struct	s_tex //структура для текстуры
{
	void			*img;
	void			*addr;
	int				line_l;
	int				bpp;
	int				en;
	int 			w_tex;
	int 			h_tex;
}					t_tex;

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
	t_tex			*north;
	t_tex			*south;
	t_tex			*west;
	t_tex			*east;
	t_tex			*sprite;
}					t_win;

typedef struct		s_all
{
	t_params		*prms;
	t_win			*win;
}					t_all;

int					set_spr_prms(t_sprite *spr, t_player plr);
void				my_pixel_put(t_win *win, int x, int y, unsigned int	color);
int					get_height(t_all *all, int i);
int					mouse_move_hook(int x, int y, t_win *win);
int					is_wall(t_all *all, t_player p, double angle, char hv);
int					key_press(int keycode, t_all *all);
int					key_release(int keycode, t_all *all);
int					mouse_hook(int button, int x, int y, t_win *win);
int					mouse_move_hook(int x, int y, t_win *win);
int					render_next_frame(t_all *all);
int					create_img(t_all *all);
int					move_fwd(t_all *all);
int					move_bwd(t_all *all);
int					move_left(t_all *all);
int					move_right(t_all *all);
int					get_spr_prms(t_all *all, double angle);
int					is_sprite(t_all *all, t_player p, double angle, char hv);
double				get_wall_dist(t_all *all, double angle);
void 				get_shot(t_all *all);





#endif
