#include "minishell.h"
#include "libft.h"

size_t		len_to_equal(char *str)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(str) && str[i] != '=')
		i++;
	return (i + 1);
}

size_t		nb_env(char **env)
{
	size_t	i;

	i = 0;
	while (env && env[i])
		i++;
	return (i);
}

t_bool		env_exist(char *name, char **env)
{
	t_bool	b;
	size_t	i;
	size_t	len;
	size_t	nbenv;
	char	*tmp;

	nbenv = nb_env(env);
	b = FALSE;
	i = 0;
	while (!b && i < nbenv)
	{
		len = len_to_equal(env[i]);
		if ((tmp = ft_strsub(env[i], 0, len - 1)) == NULL)
			return (FALSE);
		if (ft_strcmp(tmp, name) == 0)
			b = TRUE;
		ft_strdel(&tmp);
		i++;
	}
	return (b);
}

void		print_env(char **env)
{
	size_t	i;
	size_t	nb;

	i = 0;
	nb = nb_env(env);
	while (i < nb)
	{
		ft_putendl(env[i]);
		i++;
	}
}
