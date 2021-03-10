/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 19:39:27 by swquinc           #+#    #+#             */
/*   Updated: 2021/03/10 23:07:18 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_echo(t_cmd *cmd)
{
	int		i;
	int		flag;

	flag = 0;
	i = 1;
	if (cmd->cmd && cmd->cmd[i])
	{
		if (cmd->cmd[i] == NULL)
			flag = 0;
		while (cmd->cmd[i] != NULL)
			if (ft_strcmp(cmd->cmd[i], "-n") == 0)
			{
				flag = 1;
				if (cmd->cmd[++i] == NULL)
					ft_putstr_fd("", 1);
			}
			else
			{
				ft_putstr_fd(cmd->cmd[i], 1);
				if (cmd->cmd[++i] != NULL)
					ft_putchar_fd(' ', 1);
			}
	}
	if (flag == 0)
		ft_putchar_fd('\n', 1);
}
