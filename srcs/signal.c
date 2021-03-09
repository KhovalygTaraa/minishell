/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 19:15:00 by swquinc           #+#    #+#             */
/*   Updated: 2021/03/09 22:35:45 by swquinc          ###   ########.fr       */
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

void	ignore_sint2(int code)
{
	(void)code;
	g_error = 130;
}

void	ignore_squit2(int code)
{
	(void)code;
	g_error = 131;
}
