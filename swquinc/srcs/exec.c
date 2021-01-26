/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 19:14:11 by swquinc           #+#    #+#             */
/*   Updated: 2021/01/26 17:26:42 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_bin_path(t_main *main, char **path, t_cmd *cmd)
{
	struct stat		buf;
	int				i;

	i = 0;
	while (path[i])
	{
		if (stat(path[i], &buf) == 0)
		{
			if (execve(path[i], cmd->cmd++, main->env) == -1)
				error_handler(EXECVE, path[i]);
		}
		i++;		
	}
	i = -1;
	while (path[++i])
		free(path[i]);
	return (-1);
}

static int	exec_relative_path(t_main *main, t_cmd *cmd)
{
	struct stat		buf;
	char			*path;

	if (!(path = ft_strjoin(main->pwd, cmd->cmd[0])))
		error_handler(MALLOC, "exec_relative_path");
	if (stat(path, &buf) == 0)
	{
			if (execve(path, cmd->cmd++, main->env) == -1)
				error_handler(EXECVE, path);
	}
	free(path);
	return (-1);
}

static void	exec_absolute_path(t_main *main, t_cmd *cmd)
{
	char	*path;
	struct stat		buf;

	path = cmd->cmd[0];
	if (!(stat(path, &buf)))
	{
		if (S_ISDIR(buf.st_mode))
			error_handler(STAT_DIR, path);
		else
			error_handler(STAT, path);
	}
	if (execve(path, cmd->cmd++, main->env) == -1)
			error_handler(EXECVE, path);
}

void		exec(t_main *main, t_cmd *cmd)
{
	int		i;
	char	**path;

	i = 0;
	while (main->path[i])
		i++;
	if (!(path = malloc(sizeof(char*) * i + 1)))
		error_handler(MALLOC, "exec");
	i = 0;
	while (main->path[i])
	{
		if (!(path[i] = ft_strjoin(main->path[i], cmd->cmd[0])))
			error_handler(MALLOC, "exec2");
		i++;
	}
	path[i] = NULL;
	i = exec_bin_path(main, path, cmd);
	if (i == -1)
		i = exec_relative_path(main, cmd);
	if (i == -1)
		exec_absolute_path(main, cmd);
}
