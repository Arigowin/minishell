/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/21 12:48:00 by dolewski          #+#    #+#             */
/*   Updated: 2016/02/21 12:48:00 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "get_next_line.h"

t_bool			readline(char ***t)
{
	char	*line;
	int		ret;

	if ((ret = get_next_line(0, &line)) != -1)
	{
		if (line && line[0] != '\0')
		{
			if ((*t = lexer(line, SEP)) == NULL)
				return (FALSE);
			ft_strdel(&line);
		}
		else if (line == NULL)
			return (FALSE);
	}
	if (ret == -1)
		return (FALSE);
	return (TRUE);
}
