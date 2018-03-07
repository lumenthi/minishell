/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 14:12:13 by lumenthi          #+#    #+#             */
/*   Updated: 2018/03/07 15:38:31 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*make_string(char *fullpath)
{
	char *tmp;
	char *str;

	if (!fullpath)
		return (NULL);
	str = ft_strdup(fullpath);
	tmp = ft_strchr(str, ':');
	if (!tmp)
	{
		free(str);
		return (NULL);
	}
	*(tmp) = '\0';
	return (str);
}

int		do_execve(char **arg, char **env)
{
	pid_t pid = new_process();
	char	*cmd;
	char	*path;
	int		status;

	path = get_var(env, "PATH=");
	path = ft_strjoin(path, "/");
	if (arg[0][0] != '/')
		cmd = ft_strjoin(path, arg[0]);
	else
		cmd = ft_strdup(arg[0]);
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		execve(cmd, arg, env);
		exit(42);
	}
	else
	{
		waitpid(-1, &status, WIFEXITED(status));
		free(path);
		free(cmd);
		return (status);
	}
}

char	**tab_conv(char **args, char **env)
{
	int		i;

	i = 0;
	while (args[i])
	{
		if (args[i][0] == '$' && var_conv(args[i], env))
		{
			free(args[i]);
			args[i] = ft_strdup(var_conv(args[i], env));
		}
		i++;
	}
	return (args);
}

void	ft_execve(char **arg, char **env)
{
	char *fullpath;
	char *path;
	char *BU;
	char *old;
	int ret;

	if (tab_size(arg) == 0)
		return ;
	arg = tab_conv(arg, env);
	if (arg[0][0] == '/')
	{
		if (((ret = do_execve(arg, env))) && ret != 256 && g_error == 0)
			print_error(arg[0], FOUND);
		return ;
	}
	else if (!get_var(env, "PATH="))
	{
		ft_print_error(arg[0], FOUND, "$PATH");
		return ;
	}
	fullpath = ft_strdup(get_var(env, "PATH="));
	BU = ft_strdup(fullpath);
	while ((path = make_string(fullpath)))
	{
		set_var(&env, "PATH=", path);
		free(path);
		if ((!(ret = do_execve(arg, env))) || ret == 256)
			break ;
		old = ft_strdup(fullpath);
		free(fullpath);
		fullpath = ft_strdup(ft_strchr(old, ':'));
		free(old);
		free(fullpath);
		fullpath = ft_strdup(fullpath + 1);
	}
	free(fullpath);
	if (!path && g_error == 0)
		print_error(arg[0], FOUND);
	set_var(&env, "PATH=", BU);
	free(BU);
}
