/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-beta <ade-beta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 16:47:49 by ade-beta          #+#    #+#             */
/*   Updated: 2022/05/25 16:49:33 by ade-beta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	count_lines(int fd, char **strs)
{
	int		i;
	char	*str;

	if (fd)
	{
		i = 0;
		str = get_next_line(fd);
		while (str)
		{
			i++;
			free(str);
			str = get_next_line(fd);
		}
		return (i);
	}
	i = -1;
	while (strs[++i] && strs[i][0] != '\n')
		continue ;
	return (i);
}

int	set_mat(char *str, t_fdf *fdf, int y, int x)
{
	int	i;

	i = -1;
	while (str[++i])
		if (((i == 0 && str[i] != '-') && !ft_isdigit(str[i]))
			&& str[i] != '\n')
			return (1);
	fdf->mat[y][x] = ft_atoi((const char *)str);
	if (fdf->mat[y][x] < fdf->min_z)
		fdf->min_z = fdf->mat[y][x];
	else if (fdf->mat[y][x] > fdf->max_z)
		fdf->max_z = fdf->mat[y][x];
	return (0);
}

int	freee(char **temp, t_fdf *fdf, int y, int x)
{
	int	i;
	int	j;

	i = -1;
	while (temp[++i])
		free(temp[i]);
	free(temp);
	if (y != -1)
	{
		i = -1;
		while (++i <= y)
			free(fdf->mat[i]);
		free(fdf->mat);
		// {
		// 	j = -1;
		// 	while (++j <= x)
		// 		free(fdf->mat[i][j]);
		// 	free(fdf->mat[i]);
		// }
		// free(fdf->mat[i]);
	}
	return (1);
}

int	check_too(int fd, t_fdf *fdf)
{
	int		i;
	char	**temp;
	int		y;

	temp = ft_split(get_next_line(fd), ' ');
	if (!temp)
		return (1);
	fdf->min_z = ft_atoi((const char *)temp[0]);
	fdf->dim.x = count_lines(0, temp);
	y = -1;
	while (temp)
	{
		i = -1;
		fdf->mat[++y] = calloc(fdf->dim.x, sizeof(int));
		while (temp[++i] && temp[i][0] != '\n')
			if (i == fdf->dim.x || set_mat(temp[i], fdf, y, i))
				return (freee(temp, fdf, y, i));
		if (i != fdf->dim.x)
			return (freee(temp, fdf, y, i));
		freee(temp, fdf, -1, -1);
		temp = ft_split(get_next_line(fd), ' ');
	}
	return (0);
}

int	check_arg(char *argv, t_fdf *fdf)
{
	int		fd;

	fd = open(argv, O_RDWR);
	if (fd == -1)
		return (1);
	fdf->dim.y = count_lines(fd, NULL);
	close(fd);
	fdf->dim.x = 0;
	fdf->mat = ft_calloc(1, sizeof(int *) * fdf->dim.y);
	fd = open(argv, O_RDWR);
	if (check_too(fd, fdf))
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}
