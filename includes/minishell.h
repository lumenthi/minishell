/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 11:22:09 by lumenthi          #+#    #+#             */
/*   Updated: 2018/02/28 14:09:46 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#define GREEN	"\033[1;32m"
#define BLUE "\033[4;34m"
#define BLANK	"\033[0m"
#define RED		"\033[1;31m"

# include "../libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <errno.h>
# include <dirent.h>

pid_t	new_process(void);
void	ft_tabdel(char ***tab);
void	print_error(char *args);
void	ft_execve(char *args, char **env);
char	*get_var(char **environ, char *var);
void	set_var(char ***environ, char *var, char *value);
void	ft_cd(char ***environ, char *args);
void	print_env(char **environ);
void	ft_unsetenv(char ***cpy, char *line);
void	ft_setenv(char ***cpy, char *line);
void	environ_cpy(char **environ, char ***cpy);
void	ft_env(char **environ);
void	ft_execve(char *args, char **env);

#endif
