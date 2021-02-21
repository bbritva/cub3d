/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 18:59:31 by grvelva           #+#    #+#             */
/*   Updated: 2021/02/19 09:02:06 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	params_free(t_params *params)
{
	if (params->sprite)
		free(params->sprite);
	if (params->north)
		free(params->north);
	if (params->south)
		free(params->south);
	if (params->west)
		free(params->west);
	if (params->east)
		free(params->east);
	free(params);
}

void	ft_putstr(char *str)
{
		write(1, str, ft_strlen(str));
}

int		check_main_input(int argc, char *argv[])
{
	if (argc == 1)
	{
		ft_putstr(F_MISS_MSG);
		return (0);
	}
	if (argc == 2 && ft_strnstr(argv[1], ".cub", ft_strlen(argv[1])))
		return (1);
	if (argc == 3 && ft_strncmp("––save", argv[2], 6))
		if (ft_strlen(ft_strnstr(argv[1], ".cub", ft_strlen(argv[1]))) == 4)
			return (1);
	ft_putstr(M_ARGS_MSG);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_params	*prms;

	if ((prms = (t_params *)malloc(sizeof (t_params))))
	{
		if (check_main_input(argc, argv) && (parser(argv[1], prms)))
		{
			ft_putstr("prms - ok\n");
			render(prms);
			params_free(prms);
		} else
			ft_putstr("prms error\n");
		free(prms);
	}
	ft_putstr("end of cub3d\n");
}
