/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 19:39:27 by swquinc           #+#    #+#             */
/*   Updated: 2021/01/25 18:33:34 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_echo(t_main *main, t_cmd *cmd)
{
	(void)main;
	(void)cmd;
	printf("exec_echo");
	exit(EXIT_SUCCESS);
}
