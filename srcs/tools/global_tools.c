/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 10:20:13 by lumenthi          #+#    #+#             */
/*   Updated: 2018/03/13 12:06:44 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

pid_t	new_process(void)
{
	pid_t pid;

	pid = fork();
	return (pid);
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

int		tab_size(char **tab)
{
	int i;

	i = 0;
	while (*(tab + i))
		i++;
	return (i);
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
