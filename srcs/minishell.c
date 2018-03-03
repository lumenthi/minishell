/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 11:24:59 by lumenthi          #+#    #+#             */
/*   Updated: 2018/03/03 11:28:47 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
#include <fcntl.h>

void	print_error(char *args)
{
	ft_putstr(RED);
	ft_putstr(args);
	ft_putstr(BLANK);
	ft_putstr(": ");
	ft_putendl("command not found");
}

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

int		main(void)
{
	extern char **environ;
	char	**cpy;
	char	*line;

	line = NULL;
	environ_cpy(environ, &cpy);
	while (1)
	{
		print_prompt(cpy);
		line = gnl();
		if (line)
		{
			if (ft_strcmp(line, "exit") == 0 || ft_strcmp(line, "q") == 0)
				break ;
			else if (ft_strncmp(line, "echo", 4) == 0)
				ft_echo(line, cpy);
			else if (ft_strncmp(line, "cd", 2) == 0)
				ft_cd(&cpy, line);
			else if (ft_strncmp(line, "setenv", 6) == 0)
				ft_setenv(&cpy, line);
			else if (ft_strncmp(line, "unsetenv", 8) == 0)
				ft_unsetenv(&cpy, line);
			else if (ft_strcmp(line, "env") == 0)
				ft_env(cpy);
			else
				ft_execve(line, cpy);
			free(line);
		}
	}
	ft_tabdel(&cpy);
	free(cpy);
	free(line);
	return (0);
}
