#include "minishell.h"
#include "libft.h"

t_bool	modif_env(char *name, char ***env, char *str)
{
	char	*tmp;
	size_t	i;
	size_t	len;
	t_bool	b;
	size_t	nbenv;

	nbenv = nb_env(*env);
	i = 0;
	b = FALSE;
	while (i < nbenv && !b)
	{
		len = len_to_equal((*env)[i]);
		if ((tmp = ft_strsub((*env)[i], 0, len)) == NULL)
			return (ft_error(0, "ERROR : strsub modif_env", NULL, FALSE));
		if (ft_strcmp(tmp, name) == '=')
		{
			ft_strdel(&((*env)[i]));
			b = TRUE;
			if (str != NULL)
			{
				if (((*env)[i] = ft_strjoin(tmp, str)) == NULL)
					return (ft_error(0, "ERROR : strjoin modif_env", NULL, FALSE));
			}
			else
			{
				if (((*env)[i] = ft_strdup(tmp)) == NULL)
					return (ft_error(0, "ERROR : strdup modif_env", NULL, FALSE));
			}
		}
		ft_strdel(&tmp);
		i++;
	}
	if (!b)
	{
		ft_strdel(&((*env)[i]));
		if ((tmp = ft_strjoin(name, "=")) == NULL)
			return (ft_error(0, "ERROR : strjoin modif_env", NULL, FALSE));
		if (((*env)[i] = ft_strjoin(tmp, str)) == NULL)
			return (ft_error(0, "ERROR : strjoin modif_env", NULL, FALSE));
		ft_strdel(&tmp);
		b = TRUE;
	}
	return (b);
}
