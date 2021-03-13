/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbritva <bbritva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 19:24:13 by grvelva           #+#    #+#             */
/*   Updated: 2021/03/13 11:39:32 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define ALLOC_ERR_MSG "Memory allocating error\n"

# include "parser.h"
# include "render.h"

void	render(t_params *prms, int argc);
int		parser(char *f_name, t_params *prms);

#endif
