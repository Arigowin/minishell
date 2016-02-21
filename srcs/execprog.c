/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execprog.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/21 12:48:01 by dolewski          #+#    #+#             */
/*   Updated: 2016/02/21 12:48:01 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>
#include <unistd.h>

int		execprog(char *cmd, char **arg, char **env)
{
	pid_t	father;
	int		ret;

	ret = 0;
	father = fork();
	if (father == 0)
	{
		ret = execve(cmd, arg, env);
	}
	else
	{
		waitpid(father, NULL, 0);
	}
	return (ret);
}
