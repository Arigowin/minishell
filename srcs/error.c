#include "libft.h"
#include "minishell.h"

t_bool	ft_error(char *str, char *exe, t_bool ret)
{

#ifdef DEBUG
	ft_putendl("DEBUG : ft_error");
#endif

	ft_putstr_fd("minishell : ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(exe, 2);
	return (ret);
}
