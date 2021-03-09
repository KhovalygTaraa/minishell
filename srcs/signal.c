/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 19:15:00 by swquinc           #+#    #+#             */
/*   Updated: 2021/03/09 19:25:19 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ignore_squit(int code)
{
	(void)code;
	write(1, " \b\b \b", 5);
}

void	ignore_sint(int code)
{
	(void)code;
	g_error = 1;
	write(1, "\b\b  \b\b\n", 7);
}

void	quit_child(int code)
{
	(void)code;
	kill(g_pid, SIGQUIT);
	ft_putendl_fd("Quit: 3", 1);
	g_error = 131;
}

void	kill_child(int code)
{
	(void)code;
	kill(g_pid, SIGINT);
	write(1, "\n", 1);
	g_error = 130;
}
