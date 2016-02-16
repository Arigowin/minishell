/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 13:00:09 by dolewski          #+#    #+#             */
/*   Updated: 2016/02/16 18:25:00 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static size_t		nb_word(const char *s, char c)
{
	size_t	i;
	size_t	nb;

	nb = 0;
	i = 0;
	if (s != NULL)
	{
		while (s[i])
		{
			if ((i == 0 && s[i] != c) || (s[i] != c && s[i - 1] == c))
				nb++;
			i++;
		}
		return (nb + 1);
	}
	return (0);
}

char				**ft_strsplit(const char *s, char c)
{
	size_t	i;
	size_t	k;
	char	**tab;
	char	*tmp;
	size_t	j;

	i = 0;
	k = 0;
	j = 0;
	tab = (char **)malloc(sizeof(char *) * (nb_word(s, c) + 1));
	if (tab == NULL)
		return (NULL);
	while (j < nb_word(s, c) && s[i])
	{
		i = k;
		while (s[i] && k < ft_strlen(s) && s[k] != c)
			k++;
		tmp = ft_strsub(s, i, (k - i));
		if (tmp != NULL && k - i > 0)
			tab[j++] = tmp;
		i++;
		k++;
	}
	tab[j] = NULL;
	return (tab);
}
