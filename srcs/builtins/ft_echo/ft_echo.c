/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 19:00:43 by lumenthi          #+#    #+#             */
/*   Updated: 2018/02/28 20:12:25 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*char	*get_in(char *line)
{
	char	*str;
	int		i;
	int		j;
	int		in;

	in = 0;
	i = 0;
	j = 0;
	str = malloc(ft_strlen(line));
	while (*(line + i))
	{
		if (*(line + i) == '"')
		{
			i++;
			while (*(line + i) && *(line + i) != '"')
			{
				str[j] = line[i];
				in = 1;
				i++;
				j++;
				str[j] = '\0';
			}
		}
		i++;
	}
	return (in ? str : line + 5);
}*/

void	ft_echo(char *line, char **cpy)
{
	char	**args;
	int		i;

	(void)cpy;
	i = 1;
	args = ft_strsplit(line, ' ');
	while (args[i])
	{
		ft_putstr(args[i++]);
		ft_putchar(' ');
	}
	ft_putchar('\n');
	ft_tabdel(&args);
	free(args);
	return ;
}
