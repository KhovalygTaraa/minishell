/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 19:41:18 by swquinc           #+#    #+#             */
/*   Updated: 2021/02/06 15:19:26 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_env(t_main *main, t_cmd *cmd)
{
	int		i;

	(void)cmd;
	i = 0;
	while (main->env[i] != NULL)
	{
		ft_putendl_fd(main->env[i], 1);
		i++;
	}
}
