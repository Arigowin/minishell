/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/21 12:48:03 by dolewski          #+#    #+#             */
/*   Updated: 2016/02/21 12:48:03 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <dirent.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

static char		**take_path_in_file(void)
{
	char	buff[BUFF_S];
	int		ret_read;
	int		fd;

	fd = open("/etc/paths", O_RDONLY);
	ft_bzero(buff, BUFF_S);
	if ((ret_read = read(fd, buff, BUFF_S)) > 0)
		return (lexer(buff, "\n"));
	close(fd);
	return (NULL);
}

char			**take_path(char **env)
{
	char	**paths;
	char	*tmp;

	paths = NULL;
	tmp = NULL;
	if ((tmp = get_env("PATH", env)) == NULL)
		paths = take_path_in_file();
	else
	{
		if ((paths = lexer(tmp, ":")) == NULL)
			return (NULL);
		free(tmp);
	}
	return (paths);
}

char			*format_path_exe(char *path, char *cmd)
{
	char	*tmp;
	char	*ret;

	ret = NULL;
	tmp = NULL;
	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/') || path == NULL)
		return (ft_strdup(cmd));
	if (path[ft_strlen(path) - 1] != '/')
	{
		if ((tmp = ft_strjoin(path, "/")) == NULL)
			ft_error(0, "ERROR : join format_path_exe", path, FALSE);
	}
	if ((ret = ft_strjoin(tmp, cmd)) == NULL)
		ft_error(0, "ERROR : join2 format_path_exe", path, FALSE);
	ft_strdel(&tmp);
	return (ret);
}

char			*search_exe(char **paths, char *exe)
{
	struct dirent	*dp;
	DIR				*dir;
	int				i;
	t_bool			b;

	i = 0;
	b = FALSE;
	if (exe != NULL && (exe[0] == '/' || (exe[0] == '.' && exe[1] == '/')))
		return (ft_strdup(exe));
	while (exe != NULL && paths[i] != NULL && !b)
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
		return (ft_strdup(paths[i - 1]));
	return (NULL);
}
