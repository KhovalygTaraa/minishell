/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 19:14:11 by swquinc           #+#    #+#             */
/*   Updated: 2021/03/10 00:42:59 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		exec_bin_path(t_main *main, t_cmd *cmd)
{
	struct stat		buf;
	int				i;
	char			**path;

	i = 0;
	if (!main->path)
		return (-1);
	while (main->path[i])
		i++;
	if (!(path = malloc(sizeof(char*) * (i + 1))))
		error_handler(MALLOC, "exec_bin_path");
	i = -1;
	while (main->path[++i])
		if (!(path[i] = ft_strjoin(main->path[i], cmd->cmd[0])))
			error_handler(MALLOC, "exec_bin_path2");
	path[i] = NULL;
	i = -1;
	while (path[++i])
		if (stat(path[i], &buf) == 0)
		{
			if (execve(path[i], cmd->cmd++, main->env) == -1)
				error_handler(EXECVE, path[i]);
		}
	ft_free_2array(path);
	return (-1);
}

static int		exec_relative_path(t_main *main, t_cmd *cmd)
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

static void		exec_absolute_path(t_main *main, t_cmd *cmd)
{
	char			*path;
	struct stat		buf;

	buf.st_mode = 0;
	path = cmd->cmd[0];
	if (stat(path, &buf) == -1)
	{
		if (S_ISDIR(buf.st_mode))
			error_handler(STAT_DIR, path);
		else if (!main->path)
			error_handler(STAT + 1, path);
		else
			error_handler(STAT, path);
	}
	if (execve(path, ++cmd->cmd, main->env) == -1)
		error_handler(EXECVE, path);
}

static void		wait_child(void)
{
	int		status;

	if (signal(SIGQUIT, ignore_squit2) == SIG_ERR)
		error_handler(SIGNAL_ERROR, "exec");
	if (signal(SIGINT, ignore_sint2) == SIG_ERR)
		error_handler(SIGNAL_ERROR, "exec");
	if (wait(&status) == -1)
		error_handler(WAIT_ERROR, "exec");
	if (WIFEXITED(status) != 0)
		g_error = WEXITSTATUS(status);
	if (WIFSIGNALED(status) != 0)
	{
		if (WTERMSIG(status) == 2)
			ft_putchar_fd('\n', 1);
		if (WTERMSIG(status) == 3)
			ft_putendl_fd("Quit: 3", 1);
	}
}

void			exec(t_main *main, t_cmd *cmd)
{
	int		i;

	if ((g_pid = fork()) == 0)
	{
		i = exec_relative_path(main, cmd);
		if (i == -1)
			i = exec_bin_path(main, cmd);
		if (i == -1)
			exec_absolute_path(main, cmd);
	}
	else if (g_pid == -1)
		error_handler(FORK_ERROR, "exec");
	else
	{
		wait_child();
	}
}
