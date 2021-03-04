/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 11:43:38 by swquinc           #+#    #+#             */
/*   Updated: 2021/03/04 05:00:55 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_perror2(const char *value, const char *command_name,
						const char *strerror)
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

static void	ft_perror3(const char *value, const char *command_name,
						const char *strerror)
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
		ft_putstr_fd(value, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(strerror, 2);
	ft_putchar_fd('\n', 2);
}

static void	error_printer_ext(int code, char *str)
{
	if (code == HOME_NOT_SET)
		ft_perror2(NULL, str, "HOME not set");
	else if (code == OLDPWD_NOT_SET)
		ft_perror2(NULL, str, "OLDPWD not set");
	else if (code == EXPORT_ERROR)
		ft_perror2(str, "export: ", "not a valid identifier");
	else if (code == UNSET_ERROR)
		ft_perror2(str, "unset: ", "not a valid identifier");
	else if (code == LEXER_ERROR || code == LEXER_ERROR_FREE)
		ft_perror2(NULL, "syntax error near unexpected token ", str);
	else if (code == EXIT_ERROR)
		ft_perror3(str, "exit: ", NULL);
	else if (code == EXIT_ERROR2)
		ft_perror3(str, "exit: ", "numeric argument required");
}

static void	error_printer(int code, char *str)
{
	if (code == MALLOC || code == EXECVE || code == CHDIR_ERROR || code ==
		OPEN_ERROR || code == DUP_ERROR || code == PIPE_ERROR || code ==
		FORK_ERROR || code == SIGNAL_ERROR || code == WAIT_ERROR)
	{
		g_error = 121;
		ft_perror(str);
	}
	else if (code == STAT)
	{
		g_error = 127;
		ft_perror2(NULL, str, ": command not found");
	}
	else if (code == STAT_DIR)
	{
		g_error = 126;
		ft_perror2(NULL, str, "is a directory");
	}
	else
		error_printer_ext(code, str);
}

int			error_handler(int code, char *str)
{
	error_printer(code, str);
	if (code == HOME_NOT_SET || code == CHDIR_ERROR || code == EXPORT_ERROR
	|| code == UNSET_ERROR || code == OLDPWD_NOT_SET || code == OPEN_ERROR
	|| code == EXIT_ERROR || code == EXIT_ERROR2)
	{
		g_error = 1;
		return (-1);
	}
	if (code == LEXER_ERROR_FREE || code == LEXER_ERROR)
	{
		g_error = 258;
		if (code == LEXER_ERROR_FREE)
			free(str);
		return (-1);
	}
	exit(g_error);
}
