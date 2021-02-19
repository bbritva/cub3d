/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 14:04:51 by grvelva           #+#    #+#             */
/*   Updated: 2021/02/19 08:57:33 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>

# define F_MISS_MSG "File name missing.\n"
# define M_ARGS_MSG "Wrong arguments.\n"
# define NREAD_MSG "Cannot read file.\n"

typedef struct
{
	double			pos_x;
	double			pos_y;
	double			ang_h;
	double			angle_v;
}					t_player;

typedef struct		s_sprite
{
	int 			pos_x;
	int 			pos_y;
	double			dist;
	double			angle;
}					t_sprite;

typedef	struct
{
	int				res_v;
	int				res_h;
	char 			*north;
	char 			*south;
	char 			*west;
	char 			*east;
	char 			*sprite;
	int				floor_color;
	int				ceil_color;
	int				i;
	char 			**map;
	t_sprite		**sprites;
	double			*dists;
}					t_params;

int					get_color(char *line, int color);
int					is_map_line(char *line);
t_params			*param_parser(int fd, t_params *params, char **line);
char				**map_split(char const *s, char c);



#endif
