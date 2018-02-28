/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 10:15:47 by lumenthi          #+#    #+#             */
/*   Updated: 2018/02/28 17:03:50 by lumenthi         ###   ########.fr       */
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
	char	*tmp;
	char	*tmp2;

	tmp = NULL;
	tmp2 = NULL;
	args = ft_strsplit(line, ' ');
	values = ft_strsplit(args[1], '=');
	values[0] ? tmp = ft_strdup(values[0]) : 0;
	values[1] ? tmp2 = ft_strdup(values[1]): 0;
	ft_tabdel(&values);
	free(values);
	free(args[0]);
	free(args[1]);
	args[1] = ft_strdup(tmp2);
	args[0] = ft_strjoin(tmp, "=");
	free(tmp);
	free(tmp2);
	return (args);
}

char	**new_env(char **cpy, char **args)
{
	int i;
	char *tmp;

	i = 0;
	while (*(cpy + i))
		i++;
	cpy = (char **)ft_realloc(cpy, sizeof(char*) * (i + 2));
	tmp = ft_strdup(args[0]);
	free(args[0]);
	args[0] = ft_strjoin(tmp, args[1]);
	free(tmp);
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
		{
			ft_tabdel(&args);
			free(args);
			return ;
		}
	}
	else
		*cpy = new_env(*cpy, args);
	ft_tabdel(&args);
	free(args);
}
