/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 14:08:43 by lumenthi          #+#    #+#             */
/*   Updated: 2018/03/19 12:38:42 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int		set_env(char ***environ, char *env)
{
	char	*key;
	char	*value;
	char	*tmp;

	key = ft_strdup(env);
	tmp = ft_strchr(key, '=') + 1;
	value = ft_strdup(tmp);
	*tmp = '\0';
	set_var(environ, key, value);
	if (key[0] == '=')
		return (0);
	free(key);
	free(value);
	return (1);
}

void	ft_env(char ***environ, char **args, char **line)
{
	int		i;
	int		j;
	char	**fake_env;
	char	**bu;
	char	*line_cpy;
	
	environ_cpy(*environ, &fake_env);
	environ_cpy(*environ, &bu);
	i = 0;
	j = 1;
	if (tab_size(args) == 1)
	{
		while (*(*environ + i))
		{
			ft_putendl(*(*environ + i));
			i++;
		}
		if (i == 0)
			ft_print_error("env", EMPTY, NULL);
	}
	else
	{
		line_cpy = *line + 4;
		while (args[j])
		{
			if (ft_strchr(args[j], '='))
			{
				if (!set_env(&fake_env, args[j]))
				{
					ft_print_error("env", ARGS, NULL);
					return ;
				}
			}
			else
				break ;
			line_cpy = line_cpy + ft_strlen(args[j]) + 1;
			j++;
		}
		i = 0;
		ft_tabdel(environ);
		free(*environ);
		environ_cpy(fake_env, environ);
		if (j == tab_size(args))
		{
			while (*(*environ + i))
			{
				ft_putendl(*(*environ + i));
				i++;
			}
			if (i == 0)
				ft_print_error("env", EMPTY, NULL);
		}
		else
		{
			args = args + j;
			ft_apply(&line_cpy, args);
		}
		ft_tabdel(environ);
		free(*environ);
		environ_cpy(bu, environ);
	}
	ft_tabdel(&fake_env);
	free(fake_env);
	ft_tabdel(&bu);
	free(bu);
}
