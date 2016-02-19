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

void			lexer2(size_t (*j)[], char *sc, t_lstcmd **lst, char tmp[])
{
	if (ft_strchr(sc, (*j)[0]))
	{
		if (tmp[0] != '\0')
		{
			lstcmdadd(lst, tmp);
			ft_bzero(tmp, BUFF_S);
			(*j)[1] = 0;
			(*j)[2]++;
		}
	}
	else
	{
		tmp[(*j)[1]] = (*j)[0];
		(*j)[1]++;
	}
}

char			**lexer(char *str, char *sc)
{
	char		tmp[BUFF_S];
	t_lstcmd	*lst;
	size_t		i;
	size_t		j[3];

	i = 0;
	j[1] = 0;
	j[2] = 0;
	lst = NULL;
	ft_bzero(tmp, BUFF_S);
	while (str && str[i])
	{
		j[0] = str[i];
		lexer2(&j, sc, &lst, tmp);
		i++;
	}
	if (tmp[0] != '\0')
	{
		lstcmdadd(&lst, tmp);
		j[2]++;
	}
	return (lst_to_tstring(&lst, j[2]));
}
