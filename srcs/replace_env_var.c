#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

t_bool			replace_env_var(char **cmd, char **env)
{
	char	*var;
	char	*start;
	char	*end;
	char	*tmp2;
	char	*tmp;
	int		i;
	int		j;
	int		k;

	i = 0;
	while (cmd[i])
	{
		if (ft_strchr(cmd[i], '$'))
		{
			j = 0;
			while (cmd[i][j] != '\0' && cmd[i][j] != '$')
				j++;
			if ((start = ft_strsub(cmd[i], 0, j)) == NULL)
				return (ft_error(0, "ERROR : SUB", NULL, FALSE));
			k = j;
			while (cmd[i][k] != '\0' && cmd[i][k] != '/')
				k++;
			if ((var = ft_strsub(cmd[i], j + 1, k - j - 1)) == NULL)
				return (ft_error(0, "ERROR : SUB", NULL, FALSE));
			if ((end = ft_strsub(cmd[i], k, ft_strlen(cmd[i]))) == NULL)
				return (ft_error(0, "ERROR : SUB", NULL, FALSE));
			tmp2 = get_env(var, env);
			free(cmd[i]);
			if (tmp2 != NULL)
			{
				if ((tmp = ft_strjoin(start, tmp2)) == NULL)
					return (ft_error(0, "ERROR : JOIN", NULL, FALSE));
				if ((cmd[i] = ft_strjoin(tmp, end)) == NULL)
					return (ft_error(0, "ERROR : JOIN", NULL, FALSE));
				free(tmp2);
				free(tmp);
			}
			else
			{
				if ((cmd[i] = ft_strjoin(start, end)) == NULL)
					return (ft_error(0, "ERROR : JOIN", NULL, FALSE));
			}
			ft_strdel(&var);
			ft_strdel(&start);
			ft_strdel(&end);
		}
		else
			i++;
	}
	return (TRUE);
}
