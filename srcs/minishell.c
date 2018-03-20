/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 11:24:59 by lumenthi          #+#    #+#             */
/*   Updated: 2018/03/20 13:43:47 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	inthandler(int sig)
{
	if (sig == 2)
		g_error = 1;
	ft_putstr("\b ");
	ft_putstr("\b\b ");
	ft_putstr("\b");
	ft_putchar('\n');
	print_prompt(g_cpy);
}

static void	ft_apply(char **line, char **args)
{
	if (args[0] && ft_strcmp(args[0], "echo") == 0)
		ft_echo(args, g_cpy);
	else if (args[0] && ft_strcmp(args[0], "cd") == 0)
		ft_cd(&g_cpy, args);
	else if (args[0] && ft_strcmp(args[0], "setenv") == 0)
		ft_setenv(&g_cpy, args);
	else if (args[0] && ft_strcmp(args[0], "unsetenv") == 0)
		ft_unsetenv(&g_cpy, args);
	else if (args[0] && ft_strcmp(args[0], "env") == 0)
		ft_env(&g_cpy, args, line);
	else
		ft_execve(args, g_cpy);
}

int			ft_minishell(char **line)
{
	char **args;

	args = NULL;
	args = get_a(*line, args);
	if (!args)
		ft_print_error(NULL, QUOTES, *line);
	else if (args[0] &&
		(ft_strcmp(args[0], "exit") == 0 || ft_strcmp(args[0], "q") == 0))
	{
		ft_tabdel(&args);
		free(args);
		return (1);
	}
	else
		ft_apply(line, args);
	free(*line);
	if (args)
	{
		ft_tabdel(&args);
		free(args);
	}
	return (0);
}

int			main(void)
{
	extern char	**environ;
	char		*line;

	g_error = 0;
	environ_cpy(environ, &g_cpy);
	signal(SIGINT, inthandler);
	while (1)
	{
		line = NULL;
		if (!g_error)
			print_prompt(g_cpy);
		line = gnl();
		g_error = 0;
		if (line)
		{
			if (ft_minishell(&line))
				break ;
		}
	}
	ft_tabdel(&g_cpy);
	free(g_cpy);
	free(line);
	return (0);
}
