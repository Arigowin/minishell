/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/21 12:48:04 by dolewski          #+#    #+#             */
/*   Updated: 2016/02/21 12:48:04 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

static char		*rev_start(char **cmd, int i, int *j)
{
	char	*start;

	*j = 0;
	while (cmd[i][*j] != '\0' && cmd[i][*j] != '$')
		(*j)++;
	if ((start = ft_strsub(cmd[i], 0, *j)) == NULL)
		return (NULL);
	return (start);
}

static t_bool	rev_var_end(char **cmd, int i, int j, char *var[])
{
	int		k;

	k = j;
	while (cmd[i][k] != '\0' && cmd[i][k] != '/')
		k++;
	if (((var)[1] = ft_strsub(cmd[i], j + 1, k - j - 1)) == NULL)
		return (ft_error(0, "ERROR : SUB", NULL, FALSE));
	if (((var)[2] = ft_strsub(cmd[i], k, ft_strlen(cmd[i]))) == NULL)
		return (ft_error(0, "ERROR : SUB", NULL, FALSE));
	return (TRUE);
}

static t_bool	replace_env_var_bis(int i, char **cmd, char *tmp2, char *var[])
{
	char	*tmp;

	if (tmp2 != NULL)
	{
		if ((tmp = ft_strjoin(var[0], tmp2)) == NULL)
			return (ft_error(0, "ERROR : JOIN", NULL, FALSE));
		if ((cmd[i] = ft_strjoin(tmp, var[2])) == NULL)
			return (ft_error(0, "ERROR : JOIN", NULL, FALSE));
		free(tmp2);
		free(tmp);
	}
	else
	{
		if ((cmd[i] = ft_strjoin(var[0], var[2])) == NULL)
			return (ft_error(0, "ERROR : JOIN", NULL, FALSE));
	}
	return (TRUE);
}

t_bool			replace_env_var(char **cmd, char **env)
{
	char	*var[3];
	char	*tmp2;
	int		i;
	int		j;

	i = 0;
	while (cmd[i])
	{
		if (ft_strchr(cmd[i], '$'))
		{
			var[0] = rev_start(cmd, i, &j);
			if (rev_var_end(cmd, i, j, var) == FALSE)
				return (FALSE);
			tmp2 = get_env(var[1], env);
			free(cmd[i]);
			if (replace_env_var_bis(i, cmd, tmp2, var) == FALSE)
				return (FALSE);
			ft_strdel(&(var[1]));
			ft_strdel(&(var[0]));
			ft_strdel(&(var[2]));
		}
		else
			i++;
	}
	return (TRUE);
}
