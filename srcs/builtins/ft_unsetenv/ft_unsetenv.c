/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 10:57:23 by lumenthi          #+#    #+#             */
/*   Updated: 2018/03/08 09:59:13 by lumenthi         ###   ########.fr       */
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

void	ft_unsetenv(char ***cpy, char **args)
{
	int		i;
	char	*tmp;
	int		found;

	found = 0;
	i = 0;
	if (tab_size(args) > 2 || tab_size(args) == 1)
	{
		ft_print_error("unsetenv", ARGS, NULL);
		return ;
	}
	if (ft_strcmp(args[1], "*") == 0)
	{
		if (tab_size(*cpy) < 1)
			ft_print_error("unsetenv", EMPTY, NULL);
		else
			ft_tabdel(cpy);
		return ;
	}
	while (*(*cpy + i))
	{
		if (ft_strcmp(tmp = env_get(*(*cpy + i)), args[1]) == 0)
		{
			free(*(*cpy + i));
			while (*(*cpy + (i + 1)))
			{
				*(*cpy + i) = *(*cpy + (i + 1));
				i++;
			}
			*(*cpy + i) = NULL;
			free(tmp);
			found = 1;
			break ;
		}
		free(tmp);
		i++;
	}
	found ? 0 : ft_print_error("unsetenv", FOUND, args[1]);
}
