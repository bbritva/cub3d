/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbritva <bbritva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 21:21:24 by grvelva           #+#    #+#             */
/*   Updated: 2021/02/06 13:51:03 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static size_t	ft_calcsize(char *s, char c)
{
	size_t result;

	result = 1;
	if (*s == 0)
		return (0);
	while (*(s + 1))
	{
		if (*s != c && *(s + 1) == c)
			result++;
		s++;
	}
	return (result);
}

static size_t	ft_wrdlen(char *s, char c)
{
	size_t result;

	result = 0;
	while (*(s + result) != c && *(s + result))
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
			result[i] = (char *)malloc(sizeof(char) * (wrd_len));
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
	char	*str;
	size_t	res_size;
	char	**result;

	if (s == NULL)
		return (NULL);
	str = ft_strtrim(s, &c);
	if (!str)
		return (NULL);
	res_size = ft_calcsize(str, c);
	result = (char **)malloc(sizeof(char *) * (res_size + 1));
	if (result)
	{
		ft_fillarr(result, str, res_size, c);
	}
	free(str);
	return (result);
}
