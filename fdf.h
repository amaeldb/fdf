/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-beta <ade-beta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 16:47:58 by ade-beta          #+#    #+#             */
/*   Updated: 2022/06/13 10:45:14 by ade-beta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx_linux/mlx.h"
# include <fcntl.h>
# include <math.h>
# include "get_next_line/get_next_line.h"

typedef struct s_vect{
	int	x;
	int	y;
}	t_vect;

typedef struct s_vect_three{
	int	x;
	int	y;
	int	z;
}	t_vect_three;

typedef struct s_fdf{
	int		step;
	t_vect	start;
	t_vect	dim;
	int		**mat;
	double	ang;
	int		min_z;
	int		max_z;
	int		col_step;
	void	*img;
	char	*addr;
	int		bits_pp;
	int		line_len;
	int		endian;
	void	*mlx;
	void	*win;
}	t_fdf;

int		check_arg(char *argv, t_fdf *fdf);
void	draw(t_fdf *fdf);
void	bres_ur(t_fdf *fdf, t_vect_three start, t_vect_three end);
void	bres_uu(t_fdf *fdf, t_vect_three start, t_vect_three end);
void	bres_dr(t_fdf *fdf, t_vect_three start, t_vect_three end);
void	bres_dd(t_fdf *fdf, t_vect_three start, t_vect_three end);

void	*ft_calloc(size_t nmemb, size_t size);
char	**ft_split(const char *s, char c);
int		ft_isdigit(int c);
size_t	ft_strlen(const char *s);
int		ft_atoi(const char *nptr);
int		ft_printf(const char *str, ...);

#endif