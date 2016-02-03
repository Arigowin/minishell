/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 10:40:40 by dolewski          #+#    #+#             */
/*   Updated: 2015/11/27 17:43:48 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alist, void (*del)(void *, size_t))
{
	t_list	*tmp;

	if (alist != NULL)
	{
		while (*alist != NULL)
		{
			tmp = NULL;
			if ((*alist)->next != NULL)
				tmp = (*alist)->next;
			ft_lstdelone(alist, del);
			*alist = tmp;
		}
		*alist = NULL;
	}
}
