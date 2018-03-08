/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 10:20:13 by lumenthi          #+#    #+#             */
/*   Updated: 2018/03/08 10:03:10 by lumenthi         ###   ########.fr       */
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

void	ft_print_error(char *ft, int error, char *arg)
{
	if (error == EMPTY)
	{
		ft_putstr(RED);
		ft_putstr(ft);
		ft_putstr(BLANK);
		ft_putstr(": ");
		ft_putendl("no more environment variables");
	}
	if (error == ARGS)
	{
		ft_putstr(RED);
		ft_putstr(ft);
		ft_putstr(BLANK);
		ft_putstr(": ");
		ft_putendl("arguments problem");
	}
	if (error == FOUND)
	{
		ft_putstr(RED);
		ft_putstr(ft);
		ft_putstr(BLANK);
		ft_putstr(": ");
		ft_putstr(arg);
		ft_putendl(" no such a variable");
	}
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
//		printf("env: %s\n", env);
//		printf("var: %s\n", var);
//		printf("result: %s\n", *(environ + i) + ft_strlen(var));
		if (!(ft_strcmp(env, var)))
			return (*(environ + i) + ft_strlen(var));
		i++;
	}
	return (NULL);
}
