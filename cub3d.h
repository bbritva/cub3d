/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbritva <bbritva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 19:24:13 by grvelva           #+#    #+#             */
/*   Updated: 2021/02/24 10:50:26 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define PUT_ALLOC_ERR_MSG ft_putstr("Memory allocating error\n");

# include "./Parser/parser.h"
# include "./Render/render.h"

void 				render(t_params *prms, int argc);
int					parser(char *f_name, t_params *prms);
void				ft_putstr(char *str);

#endif
