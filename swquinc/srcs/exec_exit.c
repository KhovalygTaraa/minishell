/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 19:41:42 by swquinc           #+#    #+#             */
/*   Updated: 2021/02/13 16:20:22 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_exit(t_main *main, t_cmd *cmd)
{
	(void)main;
	(void)cmd;
	ft_putendl_fd("exit", 1);
	exit(EXIT_SUCCESS);
}
