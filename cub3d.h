/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 19:24:13 by grvelva           #+#    #+#             */
/*   Updated: 2021/01/09 14:54:48 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include "./GNL/get_next_line.h"
# include "./libft/libft.h"

# define F_MISS_MSG "File name missing.\n"
# define M_ARGS_MSG "Too many arguments.\n"
# define NREAD_MSG "Cannot read file.\n"


typedef struct
{
	int				red;
	int				green;
	int				blue;
}					t_color;

typedef	struct
{
	int				res_v;
	int				res_h;
	char 			*north;
	char 			*south;
	char 			*west;
	char 			*east;
	char 			*sprite;
	char			**map;
	t_color			floor_color;
	t_color			ceil_color;
}					t_map;

t_map	*parser(char *f_name);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
t_color	get_color(char *line, t_color color);



#endif
