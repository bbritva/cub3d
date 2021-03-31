/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbritva <bbritva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 13:09:00 by grvelva           #+#    #+#             */
/*   Updated: 2021/03/24 10:43:16 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include <math.h>
# include "../minilibx_mms/mlx.h"
# include "cub3d.h"
# define INIT_ERR_MSG "Error\nIMG initialization error (wrong texture path)\n"
# define SCALE 1
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

typedef struct		s_tex
{
	void			*img;
	void			*addr;
	int				line_l;
	int				bpp;
	int				en;
	int				w_tex;
	int				h_tex;
}					t_tex;

typedef struct		s_win
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
int					is_wall(t_all *all, t_player p, double angle, char hv);
int					key_press(int keycode, t_all *all);
int					key_release(int keycode, t_all *all);
int					render_next_frame(t_all *all);
int					create_img(t_all *all);
void				get_shot(t_all *all);
int					move(t_all *all, double angle);
int					crop_resolution(t_all *all);
int					free_window(t_all *all);
void				draw_txtr_line(t_all *all, int x_pos, int h);
void				draw_sprites(t_all *all);
int					my_exit(t_all *all);

#endif
