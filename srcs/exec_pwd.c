/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 19:40:18 by swquinc           #+#    #+#             */
/*   Updated: 2021/02/06 14:59:37 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		exec_pwd(t_main *main, t_cmd *cmd)
{
	char	buf[PATH_MAX];
	int		ret;

	(void)main;
	(void)cmd;
	ret = 0;
	if (!(getcwd(buf, PATH_MAX)))
		ret = error_handler(PWD_ERROR, "getcwd");
	if (ret != -1)
		ft_putendl_fd(buf, 1);
	return (ret);
}
