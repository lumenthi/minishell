/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 10:57:23 by lumenthi          #+#    #+#             */
/*   Updated: 2018/02/28 12:18:52 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*env_get(char *cpy)
{
	char *env;
	char *tmp;

	env = ft_strdup(cpy);
	tmp = ft_strchr(env, '=');
	*(tmp) = '\0';
	return (env);
}

void	ft_unsetenv(char ***cpy, char *line)
{
	char	**args;
	char	*found;
	int		i;

	i = 0;
	found = NULL;
	args = ft_strsplit(line, ' ');
	while (*(*cpy + i))
	{
		if (ft_strcmp(env_get(*(*cpy + i)), args[1]) == 0)
		{
			while (*(*cpy + (i + 1)))
			{
				*(*cpy + i) = *(*cpy + (i + 1));
				i++;
			}
			*(*cpy + i) = NULL;
			break ;
		}
		i++;
	}
	ft_tabdel(&args);
	free(args);
}
