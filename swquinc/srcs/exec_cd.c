/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 19:39:55 by swquinc           #+#    #+#             */
/*   Updated: 2021/02/26 01:43:39 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*set_pwd(t_main *main)
{
	char	*oldpwd;
	char	buf[PATH_MAX];
	int		i;

	i = 0;
	oldpwd = NULL;
	while (main->env[i] != NULL)
	{
		if (ft_strncmp(main->env[i], "PWD=", 4) == 0)
		{
			if (!(getcwd(buf, PATH_MAX)))
				if (error_handler(PWD_ERROR, "getcwd") == -1)
					return (NULL);
			oldpwd = main->env[i];
			if (!(main->env[i] = ft_strjoin("PWD=", buf)))
				error_handler(MALLOC, "cd_set_pwd");
			return (oldpwd);
		}
		i++;
	}
	return (oldpwd);
}

static void		create_oldpwd(t_main *main, char *oldpwd)
{
	t_cmd	cmd;

	if (!(cmd.cmd = malloc(sizeof(char*) * 3)))
		error_handler(MALLOC, "create_oldpwd");
	cmd.cmd[0] = "export";
	if (!(cmd.cmd[1] = ft_strjoin("OLD", oldpwd)))
		error_handler(MALLOC, "create_oldpwd");
	cmd.cmd[2] = NULL;
	exec_export(main, &cmd);
	free(cmd.cmd);
}

static int		set_oldpwd(t_main *main, char *oldpwd)
{
	int			i;
	static int	flag;

	i = 0;
	while (main->env[i] != NULL)
	{
		if (ft_strncmp(main->env[i], "OLDPWD=", 7) == 0)
		{
			free(main->env[i]);
			if (!(main->env[i] = ft_strjoin("OLD", oldpwd)))
				error_handler(MALLOC, "set_pwd");
			free(oldpwd);
			return (0);
		}
		i++;
	}
	if (flag == 0)
	{
		create_oldpwd(main, oldpwd);
		flag = 1;
	}
	free(main->oldpwd);
	main->oldpwd = oldpwd;
	return (0);
}

static char		*cd_minus(t_main *main)
{
	char	*oldpwd;

	if (main->oldpwd == NULL)
	{
		error_handler(OLDPWD_NOT_SET, "cd: ");
		return (NULL);
	}
	if (chdir(main->oldpwd + 4) == -1)
	{
		error_handler(CHDIR_ERROR, main->oldpwd + 4);
		return (NULL);
	}
	if ((oldpwd = set_pwd(main)) == NULL)
		return (NULL);
	ft_putstr_fd(main->oldpwd + 4, 1);
	ft_putchar_fd('\n', 1);
	return (oldpwd);
}

/*
** This command change current work directory to specifiend directory.
** If command without args, than change directory to $HOME.
** If chdir() was succesfull, we change PWD in our main->env.
** Also we change OLDPWD, if don't exist we create it.
**
** chdir() принимает относительнй и абсолютный путь.
** Для того, чтобы поменять наши PWD и OLDPWD используем программу
** getcwd(), он записывает в буффер curent work directory. В виде
** абсолютного пути.
*/

int				exec_cd(t_main *main, t_cmd *cmd)
{
	char	*oldpwd;

	if (cmd->cmd[1] == NULL || ft_strlen(cmd->cmd[1]) == 0)
	{
		if (main->home == NULL)
			return (error_handler(HOME_NOT_SET, "cd: "));
		if (chdir(main->home) == -1)
			return (error_handler(CHDIR_ERROR, main->home));
		if ((oldpwd = set_pwd(main)) == NULL)
			return (-1);
	}
	else if (cmd->cmd[1] != NULL && ft_strcmp(cmd->cmd[1], "-") == 0)
		oldpwd = cd_minus(main);
	else
	{
		if (chdir(cmd->cmd[1]) == -1)
			return (error_handler(CHDIR_ERROR, cmd->cmd[1]));
		if ((oldpwd = set_pwd(main)) == NULL)
			return (-1);
	}
	set_oldpwd(main, oldpwd);
	return (0);
}
