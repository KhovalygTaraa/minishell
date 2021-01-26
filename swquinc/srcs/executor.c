/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 15:52:49 by swquinc           #+#    #+#             */
/*   Updated: 2021/01/26 18:50:06 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cmd_selector(t_main *main, t_cmd *cmd)
{
	if (ft_strcmp(cmd->cmd[0], "="))
		create_variable(main, cmd);
	else if (ft_strcmp(cmd->cmd[0], "echo"))
		exec_echo(main, cmd);
	else if (ft_strcmp(cmd->cmd[0], "cd"))
		exec_cd(main, cmd);
	else if (ft_strcmp(cmd->cmd[0], "pwd"))
		exec_pwd(main, cmd);
	else if (ft_strcmp(cmd->cmd[0], "export"))
		exec_export(main, cmd);
	else if (ft_strcmp(cmd->cmd[0], "unset"))
		exec_unset(main, cmd);
	else if (ft_strcmp(cmd->cmd[0], "env"))
		exec_env(main, cmd);
	else if (ft_strcmp(cmd->cmd[0], "exit"))
		exec_exit(main, cmd);
	else
		exec(main, cmd);
	return (0);
}

int		executor(t_main *main)
{
	t_cmd	*cmd;
	t_list	*tmp;
	int		status;

	tmp = main->cmds;
	while (tmp != NULL)
	{
		cmd = tmp->content;
		main->pid = fork();
		if (main->pid == 0)
			cmd_selector(main, cmd);
		else
		{
			if (wait(&status) == -1)
			{
				perror("wait");
			}
		}
		tmp = tmp->next;
	}
	return (1);
}