/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 10:32:01 by lumenthi          #+#    #+#             */
/*   Updated: 2018/03/08 10:34:19 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int		quote_invalid(char *line)
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
						args[i] = malloc(lim);
					}
					args[i][j] = line[c];
					j++;
					w = 1;
					c++;
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
					args[i] = malloc(lim);
				}
				args[i][j] = line[c];
				j++;
				w = 1;
				c++;
			}
		}
		if (w != 0)
		{
			args[i][j] = '\0';
			i++;
		}
		j = 0;
		w = 0;
		c++;
	}
	args = (char **)ft_realloc(args, sizeof(char *) * (i + 1));
	args[i] = NULL;
	return (args);
}
