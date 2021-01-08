/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 18:59:31 by grvelva           #+#    #+#             */
/*   Updated: 2021/01/08 20:44:20 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include "cub3d.h"
#include <stdio.h>

int		get_next_line(int fd, char **line);

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

int		main(int argc, char *argv[])
{
	int		fd;
	char	*line;
	int		i;

	if (check_main_input(argc))
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{
			ft_putstr(NREAD_MSG);
			return (0);
		}
		while ((i = get_next_line(fd, &line)))
		{
			printf("GNL result = %d\nline =\n%s\n", i, line);
			free(line);
		}
		printf("GNL result = %d\nline =\n%s\n", i, line);
		free(line);
		close(fd);
	}
}
