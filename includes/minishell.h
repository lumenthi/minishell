/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 11:22:09 by lumenthi          #+#    #+#             */
/*   Updated: 2018/03/09 15:46:50 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#define GREEN	"\033[1;32m"
#define BLUE	"\033[4;34m"
#define BLANK	"\033[0m"
#define RED		"\033[1;31m"

# include "../libft/libft.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>

enum {ARGS, VAR_FOUND, FT_FOUND, QUOTES, EMPTY};

pid_t	new_process(void);
void	ft_tabdel(char ***tab);
char	*get_var(char **environ, char *var);
void	set_var(char ***environ, char *var, char *value);
void	ft_cd(char ***environ, char **arg);
void	print_env(char **environ);
void	ft_unsetenv(char ***cpy, char **args);
void	ft_setenv(char ***cpy, char **args);
void	environ_cpy(char **environ, char ***cpy);
void	ft_env(char **environ);
void	ft_execve(char **arg, char **env);
void	ft_echo(char **tabs, char **cpy);
int		tab_size(char **tab);
void	ft_print_error(char *ft, int error, char *arg);
char	*var_conv(char *arg, char **env);
char	**get_a(char *line, char **args);

#endif
