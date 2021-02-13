/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 12:59:25 by swquinc           #+#    #+#             */
/*   Updated: 2021/02/13 13:15:04 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>



static void		init(t_main *main, char **env)
{
	ft_bzero(main, sizeof(t_main));
	if (!(main->env = ft_2arraydup(env)))
		error_handler(MALLOC, "init");
	if (!(main->stdout = dup(1)))
		error_handler(DUP_ERROR, "init2");
	if (!(main->stdin = dup(0)))
		error_handler(DUP_ERROR, "init3");
	g_error = 0;
	g_pid = 0;
}

static int		minishell(t_main *main, char *line, int argc, char **argv)
{
	(void)argv;
	(void)argc;
	int		i;
	int		a;

	i = 1;
	a = 0;
	if (!(main->cmd = malloc(sizeof(t_cmd))))
		error_handler(MALLOC, "minishell");
	ft_bzero(main->cmd, sizeof(t_cmd));
	parse_env(main);
	while(i != 0)
	{
		free(main->cmd);
		if (line[0] == '\0')
			break ;
		if (lexer(line) == -1)
		{
			ft_putendl_fd("ne ok", 1);
			break ;
		}
		// if (parser(&main->cmd, line) == 0)
		// {
		// 	ft_putstr_fd("2", 1);
		// 	break ;
		// }
		i = parser(&main->cmd, line);
		// while (main->cmd->cmd[a] != NULL)
		// {
		// 	ft_putendl_fd(main->cmd->cmd[a], 1);
		// 	a++;
		// }
		// if (i != 0)
		// ft_putstr_fd("3", 1);
		if (main->cmd->red)
			parse_redir(main);
		if (main->cmd->cmd)
			var_handler(main, main->cmd->cmd, 1);
		if (main->cmd->red)
			var_handler(main, main->cmd->red, 0);
		// ft_putstr_fd("4", 1);
		executor(main); // выполнение
	}
	return (0);
}

/*
** lsof -c - для проверки утечки файловых дескрипторов
**
**
*/

int     main(int argc, char **argv, char **env)
{
	char    *line;
	t_main  main;
	// int		status;

	init(&main, env);
	while (main.exit == 0)
	{
		signal(SIGQUIT, ignore_squit);
		ft_putstr_fd("minishell> ", 1);
		signal(SIGINT, SIG_DFL); //ctrl + c  вывод -  ^C код ошибки - 130
		get_next_line(1, &line); // чтение
		// ft_putstr_fd("main\n", 1);
		minishell(&main, line, argc, argv);
		free(line);
	}
	return (0);
}
