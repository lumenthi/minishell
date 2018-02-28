/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 10:20:13 by lumenthi          #+#    #+#             */
/*   Updated: 2018/02/28 12:35:30 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

pid_t	new_process(void)
{
	pid_t pid;

	pid = fork();
	return (pid);
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
