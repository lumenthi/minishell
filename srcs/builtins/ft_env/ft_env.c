/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 14:08:43 by lumenthi          #+#    #+#             */
/*   Updated: 2018/03/09 16:03:30 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_env(char **environ)
{
	int i;

	i = 0;
	while (*(environ + i))
	{
		ft_putendl(*(environ + i));
		i++;
	}
	if (i == 0)
		ft_print_error("env", EMPTY, NULL);
}
