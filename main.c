/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 18:59:31 by grvelva           #+#    #+#             */
/*   Updated: 2021/01/09 12:10:23 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

void	ft_putstr(char *str)
{
	while (*str != 0)
	{
		write(1, str, 1);
		str++;
	}
}

int		check_main_input(int argc)
{
	if (argc == 1)
	{
		ft_putstr(F_MISS_MSG);
		return (0);
	}
	if (argc > 2)
	{
		ft_putstr(M_ARGS_MSG);
		return (0);
	}
	return (1);
}

void 	parse_line(t_map *map, char *line)
{
	(void) map;
	(void) line;
}

t_map	*parser(char *f_name)
{
	int		fd;
	char	*line;
	int		i;
	t_map	*map;

	fd = open(f_name, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr(NREAD_MSG);
		return (NULL);
	}
	if ((map = (t_map *)malloc(sizeof(t_map))))
	{
		while ((i = get_next_line(fd, &line)))
		{
			parse_line(map, line);
			printf("GNL result = %d\nline =\n%s\n", i, line);
			free(line);
		}
		printf("GNL result = %d\nline =\n%s\n", i, line);
		free(line);
		return (map);
	}
	close(fd);
	return (map);
}


int	main(int argc, char *argv[])
{
	t_map	*map;

	if (check_main_input(argc) && (map = parser(argv[1])))
	{
		printf("map - ok\n");
		free(map);
	}
	else
		printf("map error\n");
}
