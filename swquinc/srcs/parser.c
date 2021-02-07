/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 15:20:41 by swquinc           #+#    #+#             */
/*   Updated: 2021/02/07 14:58:15 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int  cmd_filler(t_main *main)
// {
// 	static int	i;
// 	t_cmd	*cmd;

// 	// if (!(cmd = malloc(sizeof(t_cmd))))
// 	// 	return (0);
// 	// cmd->cmd = malloc(sizeof(char*) * 3);
// 	// cmd->cmd[0] = "cd"; 
// 	// cmd->cmd[1] = "srcs/";
// 	// cmd->cmd[2] = NULL;
	
// 	// ft_lstadd_back(&main->cmds, ft_lstnew(cmd));
// 	if (i == 1)
// 	{
// 		if (!(cmd = malloc(sizeof(t_cmd))))
// 			return (0);
// 		cmd->cmd = malloc(sizeof(char*) * 3);
// 		cmd->cmd[0] = "cat"; 
// 		// cmd->cmd[1] = "PWD=HELLO";
// 		// cmd->cmd[2] = "var=value";
// 		// cmd->cmd[3] = "__hihi";
// 		// cmd->cmd[4] = "1=";
// 		cmd->cmd[1] = "-e";
// 		cmd->cmd[2] = NULL;
// 		main->cmd = cmd;
// 		cmd->red = NULL;
// 		// cmd->pipe = 2;
// 		i++;
// 	}
// 	else if (i == 0)
// 	{
// 		if (!(cmd = malloc(sizeof(t_cmd))))
// 			return (0);
// 		cmd->cmd = malloc(sizeof(char*) * 5);
// 		cmd->cmd[0] = "ls"; 
// 		cmd->cmd[1] = "-la";
// 		cmd->cmd[2] = NULL;
// 		cmd->cmd[3] = NULL;
// 		cmd->cmd[4] = NULL;
// 		main->cmd = cmd;
// 		cmd->pipe = 1;
// 		cmd->red = malloc(sizeof(char*) * 5);
// 		cmd->red[0] = "<";
// 		cmd->red[1] = "date";
// 		cmd->red[2] = NULL;
// 		cmd->red[3] = NULL;
// 		cmd->red[4] = NULL;
// 		i++;
// 	}
// 	else if (i == 2)
// 	{
// 		if (!(cmd = malloc(sizeof(t_cmd))))
// 			return (0);
// 		cmd->cmd = malloc(sizeof(char*) * 3);
// 		cmd->cmd[0] = "env"; 
// 		cmd->cmd[1] = NULL;
// 		cmd->cmd[2] = NULL;
// 		cmd->red = NULL;
// 		main->cmd = cmd;
// 		i++;
// 	}
// 	else if (i == 3)
// 	{
// 		if (!(cmd = malloc(sizeof(t_cmd))))
// 			return (0);
// 		cmd->cmd = malloc(sizeof(char*) * 4);
// 		cmd->cmd[0] = "cd"; 
// 		cmd->cmd[1] = NULL;
// 		cmd->cmd[2] = NULL;
// 		cmd->cmd[3] = NULL;
// 		cmd->red = NULL;
// 		main->cmd = cmd;
// 		i++;
// 	}
// 	else if (i == 4)
// 	{
// 		if (!(cmd = malloc(sizeof(t_cmd))))
// 			return (0);
// 		cmd->cmd = malloc(sizeof(char*) * 3);
// 		cmd->cmd[0] = "env"; 
// 		cmd->cmd[1] = NULL;
// 		cmd->cmd[2] = NULL;
// 		cmd->red = NULL;
// 		main->cmd = cmd;
// 	}
// 	return (0);
// }

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

static t_cmd	*cmd_filler(t_main *main, char *line)
{
	int		i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '$')
		{

		}
	}
	return (0);
}

/*
** парсер состоит из
** 1) lexer - первичная обработка строки
** 2) parser - вычленяет нужные элементы из строки, обрабатывает ошибочнные элементы.
** 3) 
*/


static char		*quotes(t_main *main, char *line)
{
	int		i;
	char	*res;
	int		index;
	int		index2;

	index = ft_strchr_index(line,'\'');
	index2 = ft_strchr_index(line, '\"');
	if (index < index2)
	{
		
	}
	return (res);
}

int     parser(char *line, t_main *main)
{
	static int 	i;
	char		*line_splitted_by_quotes;
	t_cmd		*cmd;

	// lexered_line = lexer(main, line);            // проходится единожды
	line_splitted_by_quotes = quotes(main, line);
	// ft_split_upd(quotes, ";");
	// put_var();
	// cmd = cmd_filler(main, lexered_line);
	main->cmd = NULL;
	// char    *cmd;
	// char    *trimmed_line;
	// trimmed_line = ft_strtrim(line, " "); //line lexer
	// parse_line(trimmed_line); // line parser
	// cmd = get_cmd(trimmed_line); // argv[1]
/*
	if (i == 0)
	{
		i = 1;
		parse_env(main); // path parser
		cmd_filler(main);
	}
	else
	{
		free(main->cmd);
		i = 0;
		main->cmd = NULL;
	}
*/
	return (0);
}