/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 12:59:25 by swquinc           #+#    #+#             */
/*   Updated: 2021/01/26 12:38:55 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int     main(int argc, char **argv, char **env)
{
	char    *line;
	t_main  main;
	int     status;
	pid_t	pid;

	status = 1;
	(void)argc;
	(void)argv;
	main.env = env;
	while (status)
	{
		if ((pid = fork()) == 0)
		{
			ft_putstr_fd("sh> ", 1);
			get_next_line(1, &line); // чтение
			parser(line, &main); // парсинг
			free(line);
			executor(&main); // выполнение
		}
		else
			wait(&status);
	}
	return (0);
}
