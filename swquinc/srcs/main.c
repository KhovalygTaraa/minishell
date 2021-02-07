/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 12:59:25 by swquinc           #+#    #+#             */
/*   Updated: 2021/02/06 17:41:57 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int		minishell(t_main *main, char *line, int argc, char **argv)
{
	(void)argv;
	(void)argc;
	main->cmd = malloc(sizeof(t_cmd));
	while(main->cmd != NULL)
	{
		parser(line, main); // парсинг
		// if (main->cmd)
		// 	executor(main); // выполнение
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

	error = 0;
	main.exit = 0;
	main.env = ft_2arraydup(env);
	main.stdout = dup(1);
	main.stdin = dup(0);
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
