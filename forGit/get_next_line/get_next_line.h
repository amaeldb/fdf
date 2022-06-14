/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-beta <ade-beta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 14:57:42 by ade-beta          #+#    #+#             */
/*   Updated: 2022/06/14 12:58:31 by ade-beta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 20000
# endif

# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
int		gnl_strlen(char *s);
char	*gnl_strchr(char *s, int c);
char	*gnl_strdup(char *src);
char	*gnl_strjoin(char *s1, char *s2);
void	*gnl_calloc(int nmemb, int size);

#endif
