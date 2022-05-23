/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-beta <ade-beta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 11:47:17 by ade-beta          #+#    #+#             */
/*   Updated: 2021/12/01 15:14:51 by ade-beta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*ret;
	//int		i;

	//i = ft_lstsize(lst);
	if (!lst)
		return (NULL);
	//ret = (t_list *)malloc(sizeof(t_list));
	ret = NULL;
	//if (!ret)
	//	return (NULL);
	while (lst != NULL)
	{
		ft_lstadd_back(&ret, ft_lstnew((*f)(lst->content)));
		if (!ft_lstlast(ret) || !ret)
		{
			ft_lstclear(&ret, (*del));
			return (NULL);
		}
		lst = lst->next;
	}
	return (ret);
}
