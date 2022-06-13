/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-beta <ade-beta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 16:47:52 by ade-beta          #+#    #+#             */
/*   Updated: 2022/06/13 15:23:01 by ade-beta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#include <stdio.h>

void	find_dir(t_fdf *fdf, t_vect_three start, t_vect_three end)
{
	int	delt_x;
	int	delt_y;

	delt_x = end.x - start.x;
	delt_y = end.y - start.y;
	if (delt_x >= delt_y && delt_x > -1 && delt_y > -1)
		bres_ur(fdf, start, end);
	else if (delt_x <= delt_y && delt_x < 1 && delt_y < 1)
		bres_ur(fdf, end, start);
	else if (delt_x < delt_y && delt_x > -1 && delt_y > -1)
		bres_uu(fdf, start, end);
	else if (delt_x > delt_y && delt_x < 1 && delt_y < 1)
		bres_uu(fdf, end, start);
	else if (delt_x >= delt_y && delt_x > -1 && delt_y < 1
		&& delt_x > (delt_y * -1))
		bres_dr(fdf, start, end);
	else if (delt_x <= delt_y && delt_x < 1 && delt_y > -1
		&& (delt_x * -1) > delt_y)
		bres_dr(fdf, end, start);
	else if (delt_x >= delt_y && delt_x > -1 && delt_y < 1
		&& (delt_y * -1) > delt_x)
		bres_dd(fdf, start, end);
	else if (delt_x <= delt_y && delt_x < 1 && delt_y > -1)
		bres_dd(fdf, end, start);
}

void	draw_line(t_fdf *fdf, t_vect start, t_vect end)
{
	t_vect			z;
	t_vect_three	n_s;
	t_vect_three	n_e;

	z.x = fdf->step / 10 * fdf->mat[start.y][start.x];
	z.y = fdf->step / 10 * fdf->mat[end.y][end.x];
	n_s.z = fdf->mat[start.y][start.x];
	n_e.z = fdf->mat[end.y][end.x];
	n_s.x = (int)((cos(fdf->ang) * (fdf->start.x + fdf->step * start.x - 500
					)) - (sin(fdf->ang) * (fdf->start.y + fdf->step * start.y
					- 500)) + 500);
	n_s.y = (int)((cos(fdf->ang) * (fdf->start.y + fdf->step * start.y - 500
					)) + (sin(fdf->ang) * (fdf->start.x + fdf->step * start.x
					- 500)) + 500) + z.x * -5;
	n_e.x = (int)((cos(fdf->ang) * (fdf->start.x + fdf->step * end.x - 500))
			- (sin(fdf->ang) * (fdf->start.y + fdf->step * end.y - 500))
			+ 500);
	n_e.y = (int)((cos(fdf->ang) * (fdf->start.y + fdf->step * end.y - 500))
			+ (sin(fdf->ang) * (fdf->start.x + fdf->step * end.x - 500)) + 500)
		+ z.y * -5;
	// n_s = (t_vect_three){fdf->start.x + fdf->step * (n_s.x - n_s.y) * 2,
	// 		fdf->start.y + fdf->step * (n_s.x + n_s.y), n_s.z};
	// n_e = (t_vect_three){fdf->start.x + fdf->step * (n_e.x - n_e.y) * 2,
	// 		fdf->start.y + fdf->step * (n_e.x + n_e.y), n_e.z};
	// printf("start: x = %d, y = %d\n")
	find_dir(fdf, n_s, n_e);
}

void	draw(t_fdf *fdf)
{
	int	x;
	int	y;

	y = -1;

	fdf->img = mlx_new_image(fdf->mlx, 1000, 1000);
	fdf->addr = mlx_get_data_addr(fdf->img, &fdf->bits_pp,
				&fdf->line_len, &fdf->endian);
	while (++y < fdf->dim.y)
	{
		x = -1;
		while (++x < fdf->dim.x)
		{
			if (x > 0)
				draw_line(fdf, (t_vect){x - 1, y}, (t_vect){x, y});
			if (y > 0)
				draw_line(fdf, (t_vect){x, y - 1}, (t_vect){x, y});
		}
	}

	
	//int pos = 10, pos1 = 10, pos2 = 200, pos3 = 150;
	//bres_uu(fdf, (t_vect_three){pos,pos1,0}, (t_vect_three){pos2,pos3,0});
	//bres_ur(fdf, (t_vect_three){pos,pos1,0}, (t_vect_three){pos2,pos3,10});
	//bres_dd(fdf, (t_vect_three){pos,pos1,0}, (t_vect_three){pos2,pos3,0});
	//bres_dr(fdf, (t_vect_three){pos,pos1,0}, (t_vect_three){pos2,pos3,0});


	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
	mlx_destroy_image(fdf->mlx, fdf->img);
}
