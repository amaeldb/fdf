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

void	place_pixel(int x, int y, t_vect_three end, t_vect col)
{
	col.x += (float)col.y * ((float)(y - end.x) / (float)(end.y - end.x));
	//printf("%d / %d = %f\n", (y - end.x), (end.y - end.x), ((float)(y - end.x) / (float)(end.y - end.x)));
	printf("(%d,%d, %d) ", x, y, col.x);
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
			place_pixel(start.x++, start.y++, end, col);
			pk += 2 * delt.y - 2 * delt.x;
		}
		else
		{
			place_pixel(start.x++, start.y, end, col);
			pk += 2 * delt.y;
		}	
	}
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
			place_pixel(start.x++, start.y++, end, col);
			pk += 2 * delt.x - 2 * delt.y;
		}
		else
		{
			place_pixel(start.x, start.y++, end, col);
			pk += 2 * delt.x;
		}
	}
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
			place_pixel(start.x++, start.y--, end, col);
			pk += 2 * delt.y + 2 * delt.x;
		}
		else
		{
			place_pixel(start.x++, start.y, end, col);
			pk += 2 * delt.y;
		}
	}
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
			place_pixel(start.x++, start.y--, end, col);
			pk += 2 * delt.x + 2 * delt.y;
		}
		else
		{
			place_pixel(start.x, start.y--, end, col);
			pk += 2 * delt.x;
		}
	}
}
