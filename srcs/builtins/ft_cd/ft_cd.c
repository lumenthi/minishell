/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumenthi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 16:39:55 by lumenthi          #+#    #+#             */
/*   Updated: 2018/03/02 10:55:14 by lumenthi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	cd_error(char *path)
{
	ft_putstr(RED);
	ft_putstr("cd");
	ft_putstr(BLANK);
	if (ft_strcmp(path, "$HOME") == 0)
		ft_putendl(": no $HOME variable");
	else if (ft_strcmp(path, "$OLDPWD") == 0)
		ft_putendl(": no $OLDPWD variable");
	else
	{
		ft_putstr(": no such file or directory: ");
		ft_putendl(path);
	}
}

void		ft_cd(char ***environ, char *args)
{
	char	*abs_path;
	char	*old_path;
	char	**arg;

	arg = ft_strsplit(args, ' ');
	if (get_var(*environ, "OLDPWD=") == NULL)
		old_path = ft_strdup("");
	else
		old_path = ft_strdup(get_var(*environ, "OLDPWD="));
	abs_path = NULL;
	abs_path = getcwd(abs_path, 99);
	if (tab_size(arg) > 2)
		ft_print_error("cd", ARGS, NULL);
	else if (arg[1] && ft_strcmp(arg[1], "-") == 0)
	{
		if (chdir(old_path) == -1)
			cd_error("$OLDPWD");
		else
		{
			set_var(environ, "OLDPWD=", abs_path);
			abs_path = getcwd(abs_path, 99);
			set_var(environ, "PWD=", abs_path);
			ft_putendl(abs_path);
		}
	}
	else if (arg[1] == NULL || ft_strcmp(arg[1], "~") == 0 ||
		ft_strcmp(arg[1], "--") == 0)
	{
		if (chdir(get_var(*environ, "HOME=")) == -1)
			cd_error("$HOME");
		else
		{
			set_var(environ, "OLDPWD=", abs_path);
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
			set_var(environ, "OLDPWD=", abs_path);
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
			set_var(environ, "OLDPWD=", abs_path);
			abs_path = getcwd(abs_path, 99);
			set_var(environ, "PWD=", abs_path);
		}
	}
	free(abs_path);
	free(old_path);
	ft_tabdel(&arg);
	free(arg);
}
