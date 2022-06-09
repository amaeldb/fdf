/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bres.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-beta <ade-beta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 16:47:43 by ade-beta          #+#    #+#             */
/*   Updated: 2022/05/25 17:01:50 by ade-beta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

void	place_pixel(t_fdf *fdf, t_vect pos, t_vect_three end, t_vect col)
{
	char	*point;

	if (pos.x > -1 && pos.y > -1)
	{
		col.x += (float)col.y * ((float)(pos.y - end.x) / (float)(end.y - end.x));
		point = fdf->addr + ((1000 - pos.y * fdf->line_len)
				+ (pos.x * fdf->bits_pp / 8));
		*(unsigned int *)point = col.x + 65535;
	}
	//printf("%d / %d = %f\n", (y - end.x), (end.y - end.x), ((float)(y - end.x) / (float)(end.y - end.x)));
	//printf("(%d,%d,%X) ", x, y, col.x * 65536 + 0x0000FFFF);
}

void	bres_ur(t_fdf *fdf, t_vect_three start, t_vect_three end)
{
	t_vect	delt;
	t_vect	col;
	int		pk;

	delt.x = end.x - start.x;
	delt.y = end.y - start.y;
	pk = 2 * delt.y - delt.x;
	col.x = (start.z - fdf->min_z) * fdf->col_step;
	col.y = (end.z - fdf->min_z) * fdf->col_step - col.x;
	end.x = start.y;
	while (start.x <= end.x && start.y <= end.y)
	{
		if (pk > 0)
		{
			place_pixel(fdf, (t_vect){start.x++, start.y++}, end, col);
			pk += 2 * delt.y - 2 * delt.x;
		}
		else
		{
			place_pixel(fdf, (t_vect){start.x++, start.y}, end, col);
			pk += 2 * delt.y;
		}	
	}
	printf("\n");
}

void	bres_uu(t_fdf *fdf, t_vect_three start, t_vect_three end)
{
	t_vect	delt;
	t_vect	col;
	int		pk;

	delt.x = end.x - start.x;
	delt.y = end.y - start.y;
	pk = 2 * delt.x - delt.y;
	col.x = (start.z - fdf->min_z) * fdf->col_step;
	col.y = (end.z - fdf->min_z) * fdf->col_step - col.x;
	end.x = start.y;
	while (start.x <= end.x && start.y <= end.y)
	{
		if (pk > 0)
		{
			place_pixel(fdf, (t_vect){start.x++, start.y++}, end, col);
			pk += 2 * delt.x - 2 * delt.y;
		}
		else
		{
			place_pixel(fdf, (t_vect){start.x, start.y++}, end, col);
			pk += 2 * delt.x;
		}
	}
	printf("\n");
}

void	bres_dr(t_fdf *fdf, t_vect_three start, t_vect_three end)
{
	t_vect	delt;
	t_vect	col;
	int		pk;

	delt.x = end.x - start.x;
	delt.y = end.y - start.y;
	pk = 2 * delt.y + delt.x;
	col.x = (start.z - fdf->min_z) * fdf->col_step;
	col.y = (end.z - fdf->min_z) * fdf->col_step - col.x;
	end.x = start.y;
	while (start.x <= end.x && start.y >= end.y)
	{
		if (pk < 0)
		{
			place_pixel(fdf, (t_vect){start.x++, start.y--}, end, col);
			pk += 2 * delt.y + 2 * delt.x;
		}
		else
		{
			place_pixel(fdf, (t_vect){start.x++, start.y}, end, col);
			pk += 2 * delt.y;
		}
	}
	printf("\n");
}

void	bres_dd(t_fdf *fdf, t_vect_three start, t_vect_three end)
{
	t_vect	delt;
	t_vect	col;
	int		pk;

	delt.x = end.x - start.x;
	delt.y = end.y - start.y;
	pk = 2 * delt.x + delt.y;
	col.x = (start.z - fdf->min_z) * fdf->col_step;
	col.y = (end.z - fdf->min_z) * fdf->col_step - col.x;
	end.x = start.y;
	while (start.x <= end.x && start.y >= end.y)
	{
		if (pk > 0)
		{
			place_pixel(fdf, (t_vect){start.x++, start.y--}, end, col);
			pk += 2 * delt.x + 2 * delt.y;
		}
		else
		{
			place_pixel(fdf, (t_vect){start.x, start.y--}, end, col);
			pk += 2 * delt.x;
		}
	}
	printf("\n");
}
