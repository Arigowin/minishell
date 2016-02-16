#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

static t_lstcmd	*lstcmdnew(char *value)
{
	t_lstcmd	*new;

	if ((new = (t_lstcmd *)malloc(sizeof(t_lstcmd))) == NULL)
		return (NULL);
	if ((new->data = ft_strdup(value)) == NULL)
		return (NULL);
	new->next = NULL;
	return (new);
}

static int		lstcmdadd(t_lstcmd **alst, char *value)
{
	t_lstcmd	*tmp;
	t_lstcmd	*new;

	if ((new = lstcmdnew(value)) == NULL)
		return (0);
	if (*alst == NULL)
		*alst = new;
	else
	{
		tmp = *alst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (1);
}

static char		**lst_to_tstring(t_lstcmd **lst, int nbelem)
{

#ifdef DEBUG
	ft_putendl("DEBUG : lst_to_string");
#endif

	t_lstcmd	*tmp;
	char		**ret;
	int			i;

	if ((ret = (char **)malloc(sizeof(char *) * (nbelem + 1))) == NULL)
		return (NULL);
	i = 0;
	while (*lst)
	{
		tmp = NULL;
		if ((*lst)->next != NULL)
			tmp = (*lst)->next;
		if ((ret[i] = ft_strdup((*lst)->data)) == NULL)
			return (NULL);
		free((*lst)->data);
		free(*lst);
		*lst = tmp;
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

char			**lexer(char *str, char *sc)
{

#ifdef DEBUG
	ft_putendl("DEBUG : lexer");
#endif

	char		tmp[BUFF_S];
	t_lstcmd	*lst;
	size_t		i;
	size_t		j;
	size_t		k;

	i = 0;
	j = 0;
	k = 0;
	lst = NULL;
	ft_bzero(tmp, BUFF_S);
	while (str && str[i])
	{
		if (ft_strchr(sc, str[i]))
		{
			if (tmp[0] != '\0')
			{
				lstcmdadd(&lst, tmp);
				ft_bzero(tmp, BUFF_S);
				j = 0;
				k++;
			}
		}
		else
		{
			tmp[j] = str[i];
			j++;
		}
		i++;
	}
	if (tmp[0] != '\0')
	{
		lstcmdadd(&lst, tmp);
		k++;
	}
	return (lst_to_tstring(&lst, k));
}
