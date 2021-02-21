/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbritva <bbritva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 21:21:24 by grvelva           #+#    #+#             */
/*   Updated: 2021/02/08 10:44:09 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static size_t	map_calcsize(char *s, char c)
{
	size_t result;

	result = 1;
	if (!s)
		return (0);
	if (*s == 0)
		return (0);
	while (*(s + 1))
	{
		if (*s == c && *(s + 1) != c)
			result++;
		s++;
	}
	return (result);
}

static size_t	ft_wrdlen(const char *s, char c)
{
	size_t result;

	result = 0;
	while (*(s + result) && *(s + result) != c)
		result++;
	return (++result);
}

static void		ft_freeresult(char **res, size_t count)
{
	while (count > 0)
		free(res[count--]);
	free(res);
}

static void		ft_fillarr(char **result, char *str, size_t size, char c)
{
	size_t i;
	size_t wrd_len;

	i = 0;
	while (i < size)
	{
		if (*str != c)
		{
			wrd_len = ft_wrdlen(str, c);
			result[i] = (char *)ft_calloc(wrd_len, sizeof(char));
			if (result[i])
			{
				ft_strlcpy(result[i++], str, wrd_len);
				str = str + wrd_len - 1;
			}
			else
			{
				ft_freeresult(result, i);
				break ;
			}
		}
		str++;
	}
	result[i] = 0;
}

char			**map_split(char const *s, char c)
{
	size_t	res_size;
	char	**result;

	if (s == NULL)
		return (NULL);
	res_size = map_calcsize((char *)s, c);
	result = (char **)ft_calloc((res_size + 1), sizeof(char *));
	if (result)
	{
		ft_fillarr(result, (char *)s, res_size, c);
	}
	return (result);
}
