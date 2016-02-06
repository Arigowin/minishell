#include "minishell.h"
#include "libft.h"
#include <dirent.h>
#include <stdio.h>

int		len_to_equal(char *str)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(str) && str[i] != '=')
		i++;
	return (i + 1);
}

char	**get_env(char *name, char **env)
{
	char	**ret;
	char	*tmp;
	int		i;
	int		len;
	bool	b;

	i = 0;
	ret = NULL;
	b = FALSE;
	while (env[i])
	{
		len = len_to_equal(env[i]);
		tmp = ft_strsub(env[i], 0, len - 1);
		if (ft_strcmp(tmp, name) == 0)
		{
			b = TRUE;
			ft_strdel(&tmp);
			if ((tmp = ft_strsub(env[i], len, ft_strlen(env[i]))) == NULL)
				b = ft_error("ERROR : sub get_env", env[i], FALSE);
			if ((ret = ft_strsplit(tmp, ':')) == NULL)
				b = ft_error("ERROR : split get_env", env[i], FALSE);
			break ;
		}
		ft_strdel(&tmp);
		i++;
	}
	if (b == FALSE)
		return (NULL);
	ft_strdel(&tmp);
	return (ret);
}

char	*format_path_exe(char *path, char *cmd)
{
	char	*tmp;
	char	*ret;

	ret = NULL;
	tmp = NULL;
	if (path[ft_strlen(path) - 1] != '/')
	{
		if ((tmp = ft_strjoin(path, "/")) == NULL)
			ft_error("ERROR : join format_path_exe", path, FALSE);
	}
	if ((ret = ft_strjoin(tmp, cmd)) == NULL)
		ft_error("ERROR : join2 format_path_exe", path, FALSE);
	ft_strdel(&tmp);
	return (ret);
}

char	*search_exe(char **paths, char *exe)
{
	struct dirent	*dp;
	DIR				*dir;
	int				i;
	bool			b;

	i = 0;
	b = FALSE;
	while (paths[i] != NULL && !b)
	{
		if ((dir = opendir(paths[i])) != NULL)
		{
			while ((dp = readdir(dir)) != NULL && !b)
			{
				if (ft_strequ(dp->d_name, exe))
					b = TRUE;
			}
			closedir(dir);
		}
		i++;
	}
	if (b)
		return (paths[i - 1]);
	return (NULL);
}
