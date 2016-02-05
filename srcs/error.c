#include "libft.h"
#include "minishell.h"

bool	ft_error(char *str, char *exe, bool ret)
{
	ft_putstr_fd("minishell : ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(exe, 2);
	return (ret);
}
