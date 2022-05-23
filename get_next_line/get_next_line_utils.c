/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-beta <ade-beta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 14:52:28 by ade-beta          #+#    #+#             */
/*   Updated: 2021/12/14 18:12:32 by ade-beta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	gnl_strlen(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*gnl_strchr(char *s, int c)
{
	int		i;
	char	*ret;

	i = -1;
	ret = (char *)s;
	while (ret[++i])
		if (ret[i] == (char)c)
			return (&ret[i]);
	if (!c)
		return (&ret[i]);
	return (NULL);
}

char	*gnl_strdup(char *src)
{
	char	*str;
	int		i;

	i = 0;
	while (src[i])
		i++;
	str = malloc(i + 1);
	if (!str)
		return (0);
	i = 0;
	while (src[i])
	{
		str[i] = (char)src[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	char	*ret;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	i = -1;
	ret = malloc(gnl_strlen(s1) + gnl_strlen(s2) + 1);
	if (!ret)
		return (NULL);
	while (s1[++i])
		ret[i] = (char)s1[i];
	i = -1;
	while (s2[++i])
		ret[gnl_strlen(s1) + i] = (char)s2[i];
	ret[i + gnl_strlen(s1)] = '\0';
	free(s1);
	return (ret);
}

void	*gnl_calloc(int nmemb, int size)
{
	unsigned char	*ret;
	int				i;

	ret = malloc(size * nmemb);
	if (!ret)
		return (NULL);
	i = 0;
	while (i < nmemb)
	{
		ret[i] = 0;
		i++;
	}
	return (ret);
}
