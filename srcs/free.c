#include "minishell.h"
#include <stdlib.h>

void		ft_freetstring(char ***tab)
{
	size_t		i;

	i = 0;
	if (tab && *tab)
	{
		while ((*tab)[i])
		{
			free((*tab)[i]);
			i++;
		}
		free(*tab);
	}
}
