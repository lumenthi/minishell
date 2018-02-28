/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 16:39:55 by lumenthi          #+#    #+#             */
/*   Updated: 2018/02/28 14:00:27 by lumenthi         ###   ########.fr       */
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
	char	*var;
	char	*path;
	char	*old_path;

	old_path = get_var(*environ, "OLDPWD=");
	abs_path = NULL;
	abs_path = getcwd(abs_path, 99);
	set_var(environ, "OLDPWD=", abs_path);
	if (ft_strcmp(args, "cd") == 0)
	{
		chdir(get_var(*environ, "HOME="));
		abs_path = getcwd(abs_path, 99);
		set_var(environ, "PWD=", abs_path);
		free(abs_path);
		return ;
	}
	path = args + 3;
	var = NULL;
	if (path[0] == '/')
	{
		if (chdir(path) == -1)
		{
			cd_error(path);
			free(abs_path);
			return ;
		}
		abs_path = getcwd(abs_path, 99);
		set_var(environ, "PWD=", abs_path);
		free(abs_path);
	}
	else
	{
		var = get_var(*environ, "PWD=");
		var = ft_strjoin(var, "/");
		free(var);
		if (chdir(path) == -1)
		{
			cd_error(path);
			free(abs_path);
			return ;
		}
		abs_path = getcwd(abs_path, 99);
		set_var(environ, "PWD=", abs_path);
		free(abs_path);
	}
}
