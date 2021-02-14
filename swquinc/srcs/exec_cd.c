/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 19:39:55 by swquinc           #+#    #+#             */
/*   Updated: 2021/02/14 18:58:35 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*set_pwd(t_main *main)
{
	// char	*pwd;
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

static int		set_oldpwd(t_main *main, char *oldpwd)
{
	int		i;
	t_cmd	cmd;

	i = 0;
	while (main->env[i] != NULL)
	{
		if (ft_strncmp(main->env[i], "OLDPWD=", 7) == 0)
		{
			free(main->env[i]);
			main->env[i] = ft_strjoin("OLD", oldpwd);
			free(oldpwd);
			return (0);
		}
		i++;
	}
	if (!(cmd.cmd = malloc(sizeof(char*) * 4)))
		error_handler(MALLOC, "cd_set_oldpwd");
	cmd.cmd[0] = "export";
	cmd.cmd[1] = ft_strjoin("OLD", oldpwd);
	exec_export(main, &cmd);
	free(cmd.cmd[1]);
	free(cmd.cmd);
	return (0);
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
