/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-beta <ade-beta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 16:47:58 by ade-beta          #+#    #+#             */
/*   Updated: 2022/05/25 16:48:09 by ade-beta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

// # include "mlx_linux/mlx.h"
# include <fcntl.h>
# include <math.h>
# include "get_next_line/get_next_line.h"

typedef struct s_vect{
	int	x;
	int	y;
}	t_vect;

typedef struct s_fdf{
	int		step;
	t_vect	start;
	t_vect	dim;
	int		**mat;
	double	ang;
}	t_fdf;

int		check_arg(char *argv, t_fdf *fdf);

void	*ft_calloc(size_t nmemb, size_t size);
char	**ft_split(const char *s, char c);
int		ft_isdigit(int c);
size_t	ft_strlen(const char *s);
int		ft_atoi(const char *nptr);
int		ft_printf(const char *str, ...);

#endif