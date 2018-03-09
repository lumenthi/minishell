/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 10:20:13 by lumenthi          #+#    #+#             */
/*   Updated: 2018/03/09 16:02:26 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

pid_t	new_process(void)
{
	pid_t pid;

	pid = fork();
	return (pid);
}

int		tab_size(char **tab)
{
	int i;

	i = 0;
	while (*(tab + i))
		i++;
	return (i);
}

void	print_empty(char *ft)
{
	ft_putstr(RED);
	ft_putstr(ft);
	ft_putstr(BLANK);
	ft_putstr(": ");
	ft_putendl("no environment variables");
}

void	print_quotes(char *arg)
{
	ft_putstr(RED);
	ft_putstr(arg);
	ft_putstr(BLANK);
	ft_putstr(": ");
	ft_putendl("quote error");
}

void	print_ft_found(char *ft)
{
	ft_putstr(RED);
	ft_putstr(ft);
	ft_putstr(BLANK);
	ft_putstr(": ");
	ft_putendl("command not found");
}

void	print_args(char *ft)
{
	ft_putstr(RED);
	ft_putstr(ft);
	ft_putstr(BLANK);
	ft_putstr(": ");
	ft_putendl("arguments problem");
}

void	print_var_found(char *ft, char *arg)
{
	ft_putstr(RED);
	ft_putstr(ft);
	ft_putstr(BLANK);
	ft_putstr(": ");
	ft_putstr(arg);
	ft_putendl(" no such a variable");
}

void	ft_print_error(char *ft, int error, char *arg)
{
	if (error == EMPTY)
		print_empty(ft);
	if (error == QUOTES)
		print_quotes(arg);
	if (error == FT_FOUND)
		print_ft_found(ft);
	if (error == ARGS)
		print_args(ft);
	if (error == VAR_FOUND)
		print_var_found(ft, arg);
}

char	*get_var(char **environ, char *var)
{
	int		i;
	char	*env;
	char	*tmp;


	i = 0;
	while (*(environ + i))
	{
		env = ft_strdup(*(environ + i));
		tmp = ft_strchr(env, '=');
		*(tmp + 1) = '\0';
		free(env);
		if (!(ft_strcmp(env, var)))
			return (*(environ + i) + ft_strlen(var));
		i++;
	}
	return (NULL);
}
