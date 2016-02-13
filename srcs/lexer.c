#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

#include <stdio.h>
t_lstcmd	*lstcmdnew(char *value)
{
	t_lstcmd	*new;

	if ((new = (t_lstcmd *)malloc(sizeof(t_lstcmd))) == NULL)
		return (NULL);
	if ((new->data = ft_strdup(value)) == NULL)
		return (NULL);
	new->next = NULL;
	return (new);
}

void	lstcmdadd(t_lstcmd **alst, char *value)
{
	t_lstcmd	*tmp;
	t_lstcmd	*new;

	new = lstcmdnew(value);
	if (*alst != NULL)
	{
		tmp = *alst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		*alst = new;
}

char	**lexer(char *str, char *sc)
{
	char		tmp[BUFF_S];
	t_lstcmd	*lst;
	t_bool		b;
	size_t		i;
	size_t		j;
	size_t		k;
	char		**ret;

	i = 0;
	j = 0;
	ret = NULL;
	while (str && str[i])
	{
		b = TRUE;
		k = 0;
		while (sc && sc[k])
		{
			if (sc[k] == str[i])
			{
				tmp[j] = '\0';
				lstcmdadd(&lst, tmp);
				j = 0;
				b = FALSE;
			}
			k++;
		}
		if (b)
		{
			tmp[j] = str[i];
			j++;
		}
		i++;
	}
	while (lst)
	{
		printf("->%s\n", lst->data);
		lst = lst->next;
	}
	return (ret);
}
