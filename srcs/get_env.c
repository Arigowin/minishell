#include "minishell.h"
#include "libft.h"

static t_bool		get_env_bis(int i, char **env, char *name, char **ret)
{
	size_t	len;
	size_t	nbenv;
	char	*tmp;
	t_bool	b;

	b = FALSE;
	nbenv = nb_env(env);
	len = len_to_equal(env[i]);
	if ((tmp = ft_strsub(env[i], 0, len - 1)) == NULL)
		return (FALSE);
	if (ft_strcmp(tmp, name) == 0)
	{
		b = TRUE;
		if ((*ret = ft_strsub(env[i], len, ft_strlen(env[i]))) == NULL)
			b = ft_error(0, "ERROR : strsub get_env", env[i], FALSE);
		i = nbenv;
	}
	ft_strdel(&tmp);
	return (b);
}

char				*get_env(char *name, char **env)
{
	char	*ret;
	size_t	i;
	t_bool	b;
	size_t	nbenv;

	nbenv = nb_env(env);
	i = 0;
	ret = NULL;
	b = FALSE;
	while (i < nbenv && !b)
	{
		b = get_env_bis(i, env, name, &ret);
		i++;
	}
	if (b == FALSE)
		return (NULL);
	return (ret);
}
