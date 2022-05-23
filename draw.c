#include "fdf.h"

#include <stdio.h>

void	find_dir(t_fdf *fdf, t_vect start, t_vect end)
{
	int	delt_x;
	int	delt_y;

	delt_x = end.x - start.x;
	delt_y = end.y - start.y;
	//printf("start (%d,%d), end (%d,%d), dx = %d, dy = %d\n", start.x, start.y, end.x, end.y, delt_x, delt_y);
	if (delt_x >= delt_y && delt_x > -1 && delt_y > -1) // OK
		bres_ur(fdf, start, end);
	else if (delt_x <= delt_y && delt_x < 1 && delt_y < 1) // OK
		bres_ur(fdf, end, start);
	else if (delt_x < delt_y && delt_x > -1 && delt_y > -1) // OK
		bres_uu(fdf, start, end);
	else if (delt_x > delt_y && delt_x < 1 && delt_y < 1) // OK
		bres_uu(fdf, end, start);
	else if (delt_x >= delt_y && delt_x > -1 && delt_y < 1 && delt_x > (delt_y * -1)) // OK
		bres_dr(fdf, start, end);
	else if (delt_x <= delt_y && delt_x < 1 && delt_y > -1 && (delt_x * -1) > delt_y) // OK
		bres_dr(fdf, end, start);
	else if (delt_x >= delt_y && delt_x > -1 && delt_y < 1 && (delt_y * -1) > delt_x) // 
		bres_dd(fdf, start, end);
	else if (delt_x <= delt_y && delt_x < 1 && delt_y > -1) // OK
		bres_dd(fdf, end, start);
}

void	draw_line(t_fdf *fdf, t_vect start, t_vect end)
{
	t_vect	z;
	t_vect	n_start;
	t_vect	n_end;

	z.x = fdf->step / 33 * fdf->mat[start.y][start.x];
	z.y = fdf->step / 33 * fdf->mat[end.y][end.x];
	n_start.x = (int)((cos(fdf->ang) * (fdf->start.x + fdf->step * start.x - 500)) -
		(sin(fdf->ang) * (fdf->start.y + fdf->step * start.y - 500)) + 500);
	n_start.y = (int)((cos(fdf->ang) * (fdf->start.y + fdf->step * start.y - 500)) +
		(sin(fdf->ang) * (fdf->start.x + fdf->step * start.x - 500)) + 500) + z.x;
	n_end.x = (int)((cos(fdf->ang) * (fdf->start.x + fdf->step * end.x - 500)) -
		(sin(fdf->ang) * (fdf->start.y + fdf->step * end.y - 500)) + 500);
	n_end.y = (int)((cos(fdf->ang) * (fdf->start.y + fdf->step * end.y - 500)) +
		(sin(fdf->ang) * (fdf->start.x + fdf->step * end.x - 500)) + 500) + z.y;
	find_dir(fdf, n_start, n_end);
	printf("\n");
}

void	draw(t_fdf *fdf)
{
	int	x;
	int	y;

	y = -1;
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
}