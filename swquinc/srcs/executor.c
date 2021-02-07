/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 15:52:49 by swquinc           #+#    #+#             */
/*   Updated: 2021/02/06 15:07:55 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cmd_selector(t_main *main, t_cmd *cmd)
{
	if (ft_strcmp(cmd->cmd[0], "echo") == 0)
		exec_echo(main, cmd);
	else if (ft_strcmp(cmd->cmd[0], "cd") == 0)
		exec_cd(main, cmd);
	else if (ft_strcmp(cmd->cmd[0], "pwd") == 0)
		exec_pwd(main, cmd);
	else if (ft_strcmp(cmd->cmd[0], "export") == 0)
		exec_export(main, cmd);
	else if (ft_strcmp(cmd->cmd[0], "unset") == 0)
		exec_unset(main, cmd);
	else if (ft_strcmp(cmd->cmd[0], "env") == 0)
		exec_env(main, cmd);
	else if (ft_strcmp(cmd->cmd[0], "exit") == 0)
		exec_exit(main, cmd);
	else
		exec(main, cmd);
	return (0);
}

static int	standart_output(t_main *main, int *i, char **red)
{
	int		fd;
	int		a;

	if (main->relink_fd == -1)
		main->relink_fd = 1;
	a = *i;
	if (ft_strcmp(red[a], ">") == 0)
	{
		a++;
		if ((fd = open(red[a], O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0)
			error_handler(OPEN_ERROR, red[a]);
		dup2(fd, main->relink_fd);
	}
	else
	{
		a++;
		if ((fd = open(red[a], O_WRONLY | O_CREAT | O_APPEND, 0644)) < 0)
			error_handler(OPEN_ERROR, red[a]);
		dup2(fd, main->relink_fd);
	}
	if (main->relink_fd == 1)
		main->is_stdout_taken = 1;
	*i = a;
	close(fd);
	return (0);
}

static int	standart_input(t_main *main, int *i, char **red)
{
	int		fd;
	int		a;

	if (main->relink_fd == -1)
		main->relink_fd = 0;
	a = *i;
	a++;
	if ((fd = open(red[a], O_RDONLY, 0644)) < 0)
		error_handler(OPEN_ERROR, red[a]);
	dup2(fd, main->relink_fd);
	if (main->relink_fd == 0)
		main->is_stdin_taken = 1;
	*i = a;
	close(fd);
	return (0);
}

static int	red_maker(t_main *main, t_cmd *cmd)
{
	int		i;
	int		res;

	i = 0;
	res = 0;
	while (cmd->red[i] != NULL)
	{
		if (ft_strcmp(cmd->red[i], ">") == 0)
			res = standart_output(main, &i, cmd->red);
		else if (ft_strcmp(cmd->red[i], ">>") == 0)
			res = standart_output(main, &i, cmd->red);
		else if (ft_strcmp(cmd->red[i], "<") == 0)
			res = standart_input(main, &i, cmd->red);
		else
		{
			main->relink_fd = ft_atoi(cmd->red[i]);
			i++;
		}
		i++;
	}
	return (res);
}

/*
** Executor определяет какую команду выполнить и выполняет ее.
**
** Executor должен перенаправить поток stdout одной команды, на
** поток stdin другой команды, если в аргументах команды есть пайп (|).
**
** Executor должен перенаправить поток stdout команды, в указаный
** fd, если в аргументах команды есть > или >>.
*/

int			executor(t_main *main)
{
	static int	ispipe;

	main->is_stdout_taken = 0;
	main->is_stdin_taken = 0;
	if (main->cmd->red)
		red_maker(main, main->cmd);
	if (ispipe == 1)
	{
		ispipe = 0;
		if (main->is_stdin_taken == 0)
			dup2(main->fildes[0], 0);
		close(main->fildes[1]);
	}
	if (main->cmd->pipe == 1)
	{
		pipe(main->fildes);
		ispipe = 1;
		if (main->is_stdout_taken == 0)
			dup2(main->fildes[1], 1);
	}
	cmd_selector(main, main->cmd);
	dup2(main->stdout, 1);
	dup2(main->stdin, 0);
	return (1);
}
