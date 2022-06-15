/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-beta <ade-beta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 13:14:45 by ade-beta          #+#    #+#             */
/*   Updated: 2022/06/14 13:21:53 by ade-beta         ###   ########.fr       */
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

void	set_col(t_fdf *fdf)
{
	int	base[7];
	int	inc[7];
	
	base = {65535, 255, 16711935, 16711680, 16776960, 65280, 0};
	inc = {65536, 65792, 256, 257, 1, 65537, 65793};
	if (++fdf->color.z == 7)
		fdf->color.z = 0;
	fdf->color.x = base[fdf->color.z];
	fdf->color.y = inc[fdf->color.z];
}
