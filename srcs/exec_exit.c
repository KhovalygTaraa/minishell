/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 19:41:42 by swquinc           #+#    #+#             */
/*   Updated: 2021/03/04 03:04:38 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_array(char *str)
{
	int		i;

	i = 0;
	while (str[i] != 0)
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

void		exec_exit(t_main *main, t_cmd *cmd)
{
	int		i;
	int		a;

	a = 0;
	i = 1;
	(void)main;
	ft_putendl_fd("exit", 1);
	if (cmd && cmd->cmd[i] != NULL)
	{
		while (cmd->cmd[a] != NULL)
			a++;
		if (check_array(cmd->cmd[i]) == 0)
		{
			error_handler(EXIT_ERROR2, cmd->cmd[i]);
			exit(255);
		}
		else if (a > 2)
		{
			error_handler(EXIT_ERROR, "too many arguments");
			return ;
		}
		exit(ft_atoi(cmd->cmd[i]));
	}
	exit(EXIT_SUCCESS);
}
