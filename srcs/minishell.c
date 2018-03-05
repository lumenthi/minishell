/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/08 11:24:59 by lumenthi          #+#    #+#             */
/*   Updated: 2018/03/05 14:24:52 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
#include <fcntl.h>

void	print_error(char *args, int error)
{
	if (error == FOUND)
	{
		ft_putstr(RED);
		ft_putstr(args);
		ft_putstr(BLANK);
		ft_putstr(": ");
		ft_putendl("command not found");
	}
	else if (error == QUOTES)
	{
		ft_putstr(RED);
		ft_putstr(args);
		ft_putstr(BLANK);
		ft_putstr(": ");
		ft_putendl("quote error");
	}
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

int		quote_invalid(char *line)
{
	int c;
	int i;

	c = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '"')
			c++;
		i++;
	}
	return (c % 2 ? 1 : 0);
}

char	**get_a(char *line)
{
	char	**args;
	int		i;
	int		j;
	int		w;
	int		c = 0;
	int		lim = ft_strlen(line);

	if (line && quote_invalid(line))
		return (NULL);
//	ft_putnbr(quote_invalid(line));
	i = 0;
	j = 0;
	w = 0;
	args = NULL;
	args = malloc(0);
	while (c < lim)
	{
		if (line[c] == '"')
		{
			c++;
			if (line[c] == '"')
			{
				args = (char **)ft_realloc(args, sizeof(char *) * (i + 1));
				args[i] = ft_strdup("");
				w = 1;
			}
			else
			{
				while (c < lim && line[c] != '"')
				{
					if (w == 0)
					{
						args = (char **)ft_realloc(args, sizeof(char *) * (i + 1));
						args[i] = malloc(0);
	//					printf("create args[%d]\n", i);
					}
					args[i] = (char *)ft_realloc(args[i], sizeof(char) * (j + 1));
					args[i][j] = line[c];
	//				printf("create args[%d][%d]: %c\n", i, j, args[i][j]);
					j++;
					w = 1;
					c++;
	//				ft_putnbr(c);
				}
			}
		}
		else
		{
			while (c < lim && !ft_is_space(line[c]))
			{
				if (w == 0)
				{
					args = (char **)ft_realloc(args, sizeof(char *) * (i + 1));
					args[i] = malloc(0);
//					printf("create args[%d]\n", i);
				}
				args[i] = (char *)ft_realloc(args[i], sizeof(char) * (j + 1));
				args[i][j] = line[c];
//				printf("create args[%d][%d]: %c\n", i, j, args[i][j]);
				j++;
				w = 1;
				c++;
//				ft_putnbr(c);
			}
		}
		w ? args[i][j] = '\0' : 1;
//		ft_putendl(args[i]);
		w ? i++ : 1;
		j = 0;
		w = 0;
		c++;
	}
	args = (char **)ft_realloc(args, sizeof(char *) * i + 1);
	args[i] = NULL;
	return (args);
}

void	print_tab(char **args)
{
	int i = 0;
	while (args[i] != NULL)
	{
		printf("args[%d]: '%s'\n", i, args[i]);
		i++;
	}
	ft_putendl("___________");
}

int		main(void)
{
	extern char **environ;
	char	**cpy;
	char	*line;
	char	**args;

	line = NULL;
	environ_cpy(environ, &cpy);
	args = NULL;
	while (1)
	{
		print_prompt(cpy);
		line = gnl();
		args = get_a(line);
//		print_tab(args);
		if (line)
		{
			if (!args)
				print_error(line, QUOTES);
			else if (ft_strcmp(line, "exit") == 0 || ft_strcmp(line, "q") == 0)
				break ;
			else if (ft_strncmp(line, "echo", 4) == 0)
				ft_echo(args, cpy);
			else if (ft_strncmp(line, "cd", 2) == 0)
				ft_cd(&cpy, line);
			else if (ft_strncmp(line, "setenv", 6) == 0)
				ft_setenv(&cpy, line);
			else if (ft_strncmp(line, "unsetenv", 8) == 0)
				ft_unsetenv(&cpy, line);
			else if (ft_strcmp(line, "env") == 0)
				ft_env(cpy);
			else
				ft_execve(args, cpy);
			free(line);
		}
		if (args)
		{
			ft_tabdel(&args);
			free(args);
		}
	}
	ft_tabdel(&cpy);
	free(cpy);
	free(line);
	return (0);
}
