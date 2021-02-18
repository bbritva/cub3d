/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbritva <bbritva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 19:24:13 by grvelva           #+#    #+#             */
/*   Updated: 2021/02/18 14:28:48 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./Parser/parser.h"
# include "./Render/render.h"
# include "./libft/libft.h"
# include "./GNL/get_next_line.h"

typedef struct
{
	t_player 		plr;
	t_params		*prms;
	t_win			*win;
	int
}					t_all;

void 				render(t_all	*all);
int					parser(char *f_name, t_all *all);
void				show_parse_res(t_all *all);
int					map_parser(int fd, t_all *all, char **line);
void				ft_putstr(char *str);
void				my_pixel_put(t_win *win, int x, int y, unsigned int	color);
int					get_player(t_all *all);
int				 	get_sprites(t_all *all);
int					get_height(t_all *all, double angle);
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



#endif
