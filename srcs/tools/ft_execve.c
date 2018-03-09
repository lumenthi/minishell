/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 14:12:13 by lumenthi          #+#    #+#             */
/*   Updated: 2018/03/09 15:30:15 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_error;

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
	pid_t	pid;
	char	*cmd;
	char	*path;
	int		status;

	path = ft_strjoin(path = get_var(env, "PATH="), "/");
	if (arg[0][0] != '/')
		cmd = ft_strjoin(path, arg[0]);
	else
		cmd = ft_strdup(arg[0]);
	if ((pid = new_process()) == -1)
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

static int		error_exec(char ***arg, char **env, char **fullpath, char **BU)
{
	if (tab_size(*arg) == 0)
		return (1);
	*arg = tab_conv(*arg, env);
	if (!get_var(env, "PATH="))
	{
		ft_print_error(*arg[0], VAR_FOUND, "$PATH");
		return (1);
	}
	*fullpath = ft_strdup(get_var(env, "PATH="));
	*BU = ft_strdup(*fullpath);
	free(*fullpath);
	*fullpath = ft_strjoin(*BU, ":");
	return (0);
}

static void		make_fullpath(char **fullpath, char **old)
{
	*old = ft_strdup(*fullpath);
	free(*fullpath);
	*fullpath = ft_strdup(ft_strchr(*old, ':'));
	free(*old);
	free(*fullpath);
	*fullpath = ft_strdup(*fullpath + 1);
}

static void		end_execve(char *path, char **arg, char ***env, char **BU)
{
	if (!path && g_error == 0)
		ft_print_error(arg[0], FT_FOUND, "");
	set_var(env, "PATH=", *BU);
	free(*BU);
}

void	ft_execve(char **arg, char **env)
{
	char	*fullpath;
	char	*path;
	char	*BU;
	char	*old;
	int		ret;

	if (arg[0] && arg[0][0] == '/')
	{
		if (((ret = do_execve(arg, env))) && ret != 256 && g_error == 0)
			ft_print_error(arg[0], FT_FOUND, NULL);
		return ;
	}
	if (error_exec(&arg, env, &fullpath, &BU))
		return ;
	while ((path = make_string(fullpath)))
	{
		set_var(&env, "PATH=", path);
		free(path);
		if ((!(ret = do_execve(arg, env))) || ret == 256)
			break ;
		make_fullpath(&fullpath, &old);
	}
	free(fullpath);
	end_execve(path, arg, &env, &BU);
}
