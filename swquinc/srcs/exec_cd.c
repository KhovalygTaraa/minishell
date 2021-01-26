/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 19:39:55 by swquinc           #+#    #+#             */
/*   Updated: 2021/01/26 18:47:47 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cd(t_main *main, t_cmd *cmd)
{
	char	*path;
	
	path = ft_strjoin(main->pwd, cmd->cmd[1]);
	printf("%s\n", path);
	if (!chdir(path))
		printf("bl\n");
	main->pwd = path;
	printf("exec_cd\n");
	exit(EXIT_SUCCESS);
}
