/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 11:24:59 by lumenthi          #+#    #+#             */
/*   Updated: 2018/03/09 12:30:02 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
#include <fcntl.h>

void	environ_cpy(char **environ, char ***cpy)
{
	int i;

	i = 0;
	while (*(environ + i))
		i++;
	*cpy = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (*(environ + i))
	{
		(*(*cpy + i)) = ft_strdup(*(environ + i));
		i++;
	}
	*(*cpy + i) = NULL;
}

void	print_prompt(char **cpy)
{
	char *path;
	char *tmp;

	tmp = NULL;
	path = NULL;
	if (cpy)
		tmp = get_var(cpy, "PWD=");
	if (tmp)
	{
		path = ft_strrchr(tmp, '/');
		ft_strlen(path) > 1 ? path = path + 1 : 0;
		!path ? path = tmp : 0;
	}
	ft_putstr(BLUE);
	ft_putstr("[42minishell]");
	ft_putstr(BLANK);
	ft_putstr(GREEN);
	path ? ft_putstr(path) : 0;
	ft_putstr("$ ");
	ft_putstr(BLANK);
}

char	*gnl(void)
{
	char	*line;
	char	buf;
	int		i;

	line = NULL;
	i = 0;
	buf = 0;
	while ((read(0, &buf, 1)) && buf != '\n' && buf != '\0')
	{
		line = (char*)ft_realloc(line, i + 2);
		*(line + i) = buf;
		i++;
	}
	if (i && line)
		*(line + i) = '\0';
	return (line);
}

int		g_error = 0;
char	**g_cpy;

void	INThandler(int sig)
{
	if (sig == 2)
		g_error = 1;
	ft_putstr("\b ");
	ft_putstr("\b\b ");
	ft_putstr("\b");
	ft_putchar('\n');
	print_prompt(g_cpy);
//	g_error = 0;
}

int		main(void)
{
	extern char **environ;
	char	*line;
	char	**args;

	environ_cpy(environ, &g_cpy);
	signal(SIGINT, INThandler);
	while (1)
	{
		args = NULL;
		line = NULL;
		if (!g_error)
			print_prompt(g_cpy);
		line = gnl();
		g_error = 0;
		if (line)
		{
			args = get_a(line, args);
			if (!args)
				ft_print_error(NULL, QUOTES, line);
			else if (args[0] &&
				(ft_strcmp(args[0], "exit") == 0 || ft_strcmp(args[0], "q") == 0))
				break ;
			else if (ft_strncmp(line, "echo", 4) == 0)
				ft_echo(args, g_cpy);
			else if (ft_strncmp(line, "cd", 2) == 0)
				ft_cd(&g_cpy, args);
			else if (ft_strncmp(line, "setenv", 6) == 0)
				ft_setenv(&g_cpy, args);
			else if (ft_strncmp(line, "unsetenv", 8) == 0)
				ft_unsetenv(&g_cpy, args);
			else if (ft_strcmp(line, "env") == 0)
				ft_env(g_cpy);
			else
				ft_execve(args, g_cpy);
			free(line);
		}
		if (args)
		{
			ft_tabdel(&args);
			free(args);
		}
	}
	ft_tabdel(&g_cpy);
	free(g_cpy);
	free(line);
	return (0);
}
