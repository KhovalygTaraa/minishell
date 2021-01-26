/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 11:43:38 by swquinc           #+#    #+#             */
/*   Updated: 2021/01/26 17:24:49 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		ft_perror2(const char *str, const char *strerror)
{
	size_t	i;

	if (strerror == NULL)
		return ;
	write(2, "minishell: ", 11);
	if (str != NULL && (i = ft_strlen(str)) != 0)
	{
		write(2, str, i);
		write(2, ": ", 2);
	}
	i = ft_strlen(strerror);
	write(2, strerror, i);
	write(2, "\n", 1);
}

static void		error_printer(int code, char *str)
{
	if (code == MALLOC || code == EXECVE || code == STAT)
		ft_perror(str);
	else if (code == STAT_DIR)
		ft_perror2(str, "is a directory");
} 

void	error_handler(int code, char *str)
{
	error_printer(code, str);
	exit(code);
}