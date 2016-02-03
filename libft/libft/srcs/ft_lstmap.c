/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 10:45:54 by dolewski          #+#    #+#             */
/*   Updated: 2015/11/27 17:43:57 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*pnew;

	new = NULL;
	pnew = NULL;
	while (lst != NULL)
	{
		if (new == NULL)
		{
			new = f(lst);
			pnew = new;
		}
		else
		{
			pnew->next = f(lst);
			pnew = new->next;
		}
		lst = lst->next;
	}
	return (new);
}
