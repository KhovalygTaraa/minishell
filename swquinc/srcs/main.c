/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 12:59:25 by swquinc           #+#    #+#             */
/*   Updated: 2021/02/11 15:26:18 by swquinc          ###   ########.fr       */
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
		i = parser(&main->cmd, line); // парсинг
		// if (i != 0)
		// 	var_handler(main);
		if (i != 0)
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
