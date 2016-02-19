#include "minishell.h"
#include "libft.h"

char	*get_env(char *name, char **env)
{
	char	*ret;
	char	*tmp;
	size_t	i;
	size_t	len;
	t_bool	b;
	size_t	nbenv;

	nbenv = nb_env(env);
	i = 0;
	ret = NULL;
	b = FALSE;
	while (i < nbenv)
	{
		len = len_to_equal(env[i]);
		if ((tmp = ft_strsub(env[i], 0, len - 1)) == NULL)
			return (NULL);
		if (ft_strcmp(tmp, name) == 0)
		{
			b = TRUE;
			if ((ret = ft_strsub(env[i], len, ft_strlen(env[i]))) == NULL)
				b = ft_error(0, "ERROR : strsub get_env", env[i], FALSE);
			i = nbenv;
		}
		ft_strdel(&tmp);
		i++;
	}
	if (b == FALSE)
		return (NULL);
	return (ret);
}
