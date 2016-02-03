/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 20:31:58 by dolewski          #+#    #+#             */
/*   Updated: 2015/12/12 12:23:11 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstnew(const void *content, size_t content_size)
{
	t_list	*new;

	new = (t_list*)malloc(sizeof(t_list));
	if (new != NULL)
	{
		new->content = NULL;
		new->content_size = 0;
		new->next = NULL;
		if (content != NULL)
		{
			new->content = ft_memalloc(content_size);
			if (new->content != NULL)
				ft_memcpy(new->content, content, content_size);
		}
		if (!(content == NULL))
			new->content_size = content_size;
	}
	return (new);
}
