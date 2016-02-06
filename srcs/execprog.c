#include "minishell.h"
#include <sys/wait.h>
#include <unistd.h>

int		execprog(char *cmd, char **arg, char **env)
{

#ifdef DEBUG
#include "libft.h"
	ft_putendl("DEBUG : execprog");
#endif

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
