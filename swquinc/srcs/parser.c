/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 15:20:41 by swquinc           #+#    #+#             */
/*   Updated: 2021/01/26 18:07:40 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int  cmd_filler(t_main *main)
{
	t_cmd	*cmd;

	if (!(cmd = malloc(sizeof(t_cmd))))
		return (0);
	cmd->cmd = malloc(sizeof(char*) * 3);
	cmd->cmd[0] = "cd"; 
	cmd->cmd[1] = "srcs/";
	cmd->cmd[2] = NULL;
	
	ft_lstadd_back(&main->cmds, ft_lstnew(cmd));
	if (!(cmd = malloc(sizeof(t_cmd))))
		return (0);
	cmd->cmd = malloc(sizeof(char*) * 3);
	cmd->cmd[0] = "ls"; 
	cmd->cmd[1] = NULL;
	cmd->cmd[2] = NULL;
	ft_lstadd_back(&main->cmds, ft_lstnew(cmd));
	
	// cmd->cmd[2] = 
	// cmd->cmd[3] = 

	return (0);
}

// get first argument - command name.
// static char    *get_cmd(char *line)
// {
// 	int     i;
// 	char    *arg;

// 	i = 0;
// 	while (line[i] != ' ' && line[i] != 0)
// 		i++;
// 	if (!(arg = malloc(sizeof(char) * i)))
// 		return (NULL);
// 	i = 0;
// 	while (line[i] != ' ' && line[i] != 0)
// 	{
// 		arg[i] = line[i];
// 		i++;
// 	}
// 	return (arg);
// }

int     parser(char *line, t_main *main)
{
	static int 	i;

	// char    *cmd;
	// char    *trimmed_line;
	line = NULL;
	// trimmed_line = ft_strtrim(line, " "); //line lexer
	// parse_line(trimmed_line); // line parser
	// cmd = get_cmd(trimmed_line); // argv[1]
	if (i == 0)
	{
		i = 1;
		parse_env(main); // path parser
		cmd_filler(main);
	}
	return (0);
}