/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 16:39:55 by lumenthi          #+#    #+#             */
/*   Updated: 2018/03/01 11:59:10 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	cd_error(char *path)
{
	ft_putstr("cd: no such file or directory: ");
	ft_putendl(path);
}

void		ft_cd(char ***environ, char *args)
{
	char	*abs_path;
	char	*old_path;
	char	**arg;

	arg = ft_strsplit(args, ' ');
	old_path = ft_strdup(get_var(*environ, "OLDPWD="));
	abs_path = NULL;
	abs_path = getcwd(abs_path, 99);
	set_var(environ, "OLDPWD=", abs_path);
	if (arg[1] && ft_strcmp(arg[1], "-") == 0)
	{
		if (chdir(old_path) == -1)
			cd_error(old_path);
		else
		{
			abs_path = getcwd(abs_path, 99);
			set_var(environ, "PWD=", abs_path);
			ft_putendl(abs_path);
		}
	}
	else if (arg[1] == NULL || ft_strcmp(arg[1], "~") == 0 ||
		ft_strcmp(arg[1], "--") == 0)
	{
		if (chdir(get_var(*environ, "HOME=")) == -1)
			args[1] ? cd_error(arg[1]) : cd_error("$HOME");
		else
		{
			abs_path = getcwd(abs_path, 99);
			set_var(environ, "PWD=", abs_path);
		}
	}
	else if (arg[1][0] == '/')
	{
		if (chdir(arg[1]) == -1)
			cd_error(arg[1]);
		else
		{
			abs_path = getcwd(abs_path, 99);
			set_var(environ, "PWD=", abs_path);
		}
	}
	else
	{
		if (chdir(arg[1]) == -1)
			cd_error(arg[1]);
		else
		{
			abs_path = getcwd(abs_path, 99);
			set_var(environ, "PWD=", abs_path);
		}
	}
	free(abs_path);
	free(old_path);
	ft_tabdel(&arg);
	free(arg);
}
