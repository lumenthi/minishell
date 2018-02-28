/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 14:12:13 by lumenthi          #+#    #+#             */
/*   Updated: 2018/02/28 14:12:48 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_execve(char *args, char **env)
{
	pid_t pid = new_process();
	char	**arg;
	char	*cmd;

	arg = ft_strsplit(args, ' ');
	if (ft_strncmp(args, "/usr/bin/", 9) == 0)
		cmd = arg[0] + 4;
	else
		cmd = ft_strjoin("/bin/", arg[0]);
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		execve(cmd, arg, env);
		print_error(arg[0]);
		exit(0);
	}
	else
	{
		wait(NULL);
		ft_tabdel(&arg);
		free(arg);
		free(cmd);
	}
}
