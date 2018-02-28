/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 10:15:47 by lumenthi          #+#    #+#             */
/*   Updated: 2018/02/28 13:57:04 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	set_var(char ***environ, char *var, char *value)
{
	char	*str;
	int		i;

	str = NULL;
	i = 0;
	while (*(*environ + i))
	{
		if ((str = ft_strstr(*(*environ + i), var)))
			break ;
		i++;
	}
	value = ft_strjoin(var, value);
	*(*environ + i) = ft_strdup(value);
	str == NULL ? 0 : free(str);
	free(value);
}

char	**get_args(char *line)
{
	char	**args;
	char	**values;

	args = ft_strsplit(line, ' ');
	values = ft_strsplit(args[1], '=');
	values[0] ? args[0] = ft_strdup(values[0]) : 0;
	values[1] ? args[1] = ft_strdup(values[1]): 0;
	ft_tabdel(&values);
	args[0] = ft_strjoin(args[0], "=");
	return (args);
}

char	**new_env(char **cpy, char **args)
{
	int i;

	i = 0;
	while (*(cpy + i))
		i++;
	cpy = (char **)ft_realloc(cpy, sizeof(char*) * (i + 2));
	args[0] = ft_strjoin(args[0], args[1]);
	*(cpy + i) = ft_strdup(args[0]);
	i++;
	*(cpy + i) = NULL;
	return (cpy);
}

void	ft_setenv(char ***cpy, char *line)
{
	char	**args;

	args = get_args(line);
	if (get_var(*cpy, args[0]) != NULL)
	{
		if (args[2] && ft_strcmp(args[2], "1") == 0)
			set_var(cpy, args[0], args[1]);
		else
			return ;
	}
	else
		*cpy = new_env(*cpy, args);
	ft_tabdel(&args);
	free(args);
}
