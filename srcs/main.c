/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/21 12:48:03 by dolewski          #+#    #+#             */
/*   Updated: 2016/02/21 12:48:03 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void		print_path(char *path, char **env, char *color)
{
	char	*home;
	char	*tmp;
	size_t	i;
	t_bool	b;

	b = TRUE;
	if ((home = get_env("HOME", env)) != NULL)
	{
		i = 0;
		while (path[i] && home[i] && path[i] == home[i])
			i++;
		if (i == ft_strlen(home))
		{
			ft_putstr_color(color, "~");
			tmp = ft_strsub(path, i, ft_strlen(path));
			ft_putstr_color(color, tmp);
			free(tmp);
			b = FALSE;
		}
		free(home);
	}
	if (b)
		ft_putstr_color(color, path);
}

void		verif_env(char ***env)
{
	char	buff[BUFF_S];

	if (getcwd(buff, BUFF_S) == NULL)
		exit(-1);
	if (env_exist("PWD", *env) == FALSE)
		set_env("PWD", env, buff);
	if (env_exist("OLDPWD", *env) == FALSE)
		set_env("OLDPWD", env, buff);
}

static void	init_start(char ***env, char **env2)
{
	char		*tmp;
	char		*tmp2;
	size_t		i;

	i = 0;
	tmp2 = NULL;
	while (env2 && env2[i])
		i++;
	ft_copyt2d(env, env2, i, i);
	verif_env(env);
	if ((tmp = get_env("SHLVL", *env)) != NULL)
		tmp2 = ft_itoa(ft_atoi(tmp) + 1);
	else
		tmp2 = ft_strdup("1");
	if (tmp2 != NULL)
		set_env("SHLVL", env, tmp2);
	ft_strdel(&tmp2);
	free(tmp);
}

static int	start(char **envarg)
{
	char		**env;
	t_bool		b;

	env = NULL;
	init_start(&env, envarg);
	b = TRUE;
	while (b)
	{
		print_prompt(env);
		b = body(&env);
	}
	ft_freetstring(&env);
	return (b);
}

int			main(int ac, char **av, char **env)
{
	if (ac == 1)
		return (start(env));
	ac = 1;
	(void)av;
	return (0);
}
