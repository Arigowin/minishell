/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dolewski <dolewski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/21 12:48:04 by dolewski          #+#    #+#             */
/*   Updated: 2016/02/21 12:48:04 by dolewski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define TRUE 1
# define FALSE 0
# define BUFF_S 1024
# define SEP " \t\n\0"

# include <sys/types.h>

typedef char	t_bool;
typedef t_bool	(*t_ptfu) (char **, char ***);

typedef struct		s_lstcmd
{
	char			*data;
	struct s_lstcmd	*next;
}					t_lstcmd;

char				**lexer(char *str, char *sc);
t_bool				body(char ***env);
t_bool				builtins(char **t, char ***env);
t_bool				builtins_exit(char **t, char ***env);
t_bool				builtins_env(char **t, char ***env);
t_bool				builtins_setenv(char **t, char ***env);
t_bool				builtins_unsetenv(char **t, char ***env);
t_bool				change_directory(char **cmd, char ***env);
void				ft_tab_to_space(char **str);
t_bool				readline(char ***t);
t_bool				replace_tilde(char **paths, char **env);
t_bool				replace_env_var(char **path, char **env);
size_t				len_to_equal(char *str);
t_bool				env_exist(char *name, char **env);
char				*get_env(char *name, char **env);
t_bool				modif_env(char *name, char ***env, char *str);
t_bool				del_env(char *name, char ***env);
t_bool				add_env(char *name, char ***env, char *str);
t_bool				set_env(char *name, char ***env, char *str);
void				print_env(char **env);
size_t				nb_env(char **env);
t_bool				ft_error(int i, char *str, char *exe, t_bool ret);
int					execprog(char *cmd, char **arg, char **env);
void				verif_env(char ***env);
void				print_path(char *path, char **env, char *color);
char				*format_path_exe(char *path, char *cmd);
char				*search_exe(char **paths, char *exe);
char				**take_path(char **env);
void				print_prompt(char **env);
void				ft_freetstring(char ***tab);

#endif
