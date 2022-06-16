/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-beta <ade-beta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 16:47:52 by ade-beta          #+#    #+#             */
/*   Updated: 2022/06/16 13:50:47 by ade-beta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
		&& delt_x >= (delt_y * -1))
		bres_dr(fdf, start, end);
	else if (delt_x <= delt_y && delt_x < 1 && delt_y > -1
		&& (delt_x * -1) >= delt_y)
		bres_dr(fdf, end, start);
	else if (delt_x >= delt_y && delt_x > -1 && delt_y < 1
		&& (delt_y * -1) >= delt_x)
		bres_dd(fdf, start, end);
	else if (delt_x <= delt_y && delt_x < 1 && delt_y > -1)
		bres_dd(fdf, end, start);
}

void	draw_line(t_fdf *fdf, t_vect start, t_vect end)
{
	t_vect_three	n_s;
	t_vect_three	n_e;

	n_s.z = fdf->mat[start.y][start.x];
	n_e.z = fdf->mat[end.y][end.x];
	n_s = (t_vect_three){fdf->start.x + fdf->step * (start.x - start.y) * 2,
		fdf->start.y + fdf->step * (start.x + start.y)
		- fdf->mat[start.y][start.x] * fdf->step / 4, n_s.z};
	n_e = (t_vect_three){fdf->start.x + fdf->step * (end.x - end.y) * 2,
		fdf->start.y + fdf->step * (end.x + end.y)
		- fdf->mat[end.y][end.x] * fdf->step / 4, n_e.z};
	find_dir(fdf, n_s, n_e);
}

void	draw(t_fdf *fdf)
{
	int	x;
	int	y;

	y = -1;
	fdf->img = mlx_new_image(fdf->mlx, 1920, 1080);
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
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
	mlx_destroy_image(fdf->mlx, fdf->img);
	fdf->img = NULL;
}
