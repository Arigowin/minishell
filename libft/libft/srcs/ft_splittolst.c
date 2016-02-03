/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splittolst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 18:24:27 by dolewski          #+#    #+#             */
/*   Updated: 2015/11/29 20:29:39 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list				*ft_splittolst(const char *s, char c)
{
	size_t	i;
	size_t	k;
	t_list	*tab;
	char	*tmp;

	i = 0;
	k = 0;
	tmp = NULL;
	tab = NULL;
	while (s != NULL && s[i])
	{
		i = k;
		while (s[i] && k < ft_strlen(s) && s[k] != c)
			k++;
		tmp = ft_strsub(s, i, (k - i));
		if (tmp != NULL && (k - i) > 0)
		{
			if (tab == NULL)
				tab = ft_lstnew(tmp, ft_strlen(tmp) + 1);
			else
				ft_lstpushback(&tab, ft_lstnew(tmp, ft_strlen(tmp) + 1));
		}
		k++;
	}
	return (tab);
}
