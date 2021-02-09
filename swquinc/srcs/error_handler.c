/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 11:43:38 by swquinc           #+#    #+#             */
/*   Updated: 2021/02/08 19:12:45 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		ft_perror2(const char *value, const char *command_name, const char *strerror)
{
	if (strerror == NULL)
		return ;
	ft_putstr_fd("minishell: ", 2);
	if (command_name != NULL)
	{
		ft_putstr_fd(command_name, 2);
	}
	if (value != NULL)
	{
		ft_putchar_fd('`', 2);
		ft_putstr_fd(value, 2);
		ft_putchar_fd('\'', 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(strerror, 2);
	ft_putchar_fd('\n', 2);
}

static void		error_printer(int code, char *str)
{
	if (code == MALLOC || code == EXECVE || code == STAT || code == CHDIR_ERROR || code == OPEN_ERROR)
		ft_perror(str);
	else if (code == STAT_DIR)
		ft_perror2(NULL, str, "is a directory");
	else if (code == HOME_NOT_SET)
		ft_perror2(NULL, str, "HOME not set");
	else if (code == EXPORT_ERROR)
		ft_perror2(str, "export: ", "not a valid identifier");
	else if (code == UNSET_ERROR)
		ft_perror2(str, "unset: ", "not a valid identifier");
} 

int		error_handler(int code, char *str)
{
	error_printer(code, str);
	if (code == HOME_NOT_SET || code == CHDIR_ERROR || code == EXPORT_ERROR || code == UNSET_ERROR)
	{
		g_error = 1;
		return (-1);
	}
	exit(code);
}