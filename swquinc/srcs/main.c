/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 12:59:25 by swquinc           #+#    #+#             */
/*   Updated: 2021/03/04 03:44:25 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void		init(t_main *main, char **env, int argc, char **argv)
{
	t_cmd	cmd;

	(void)argc;
	(void)argv;
	ft_bzero(main, sizeof(t_main));
	if (!(main->env = ft_2arraydup(env)))
		error_handler(MALLOC, "init");
	if (!(main->stdout = dup(1)))
		error_handler(DUP_ERROR, "init2");
	if (!(main->stdin = dup(0)))
		error_handler(DUP_ERROR, "init3");
	cmd.cmd = malloc(sizeof(char *) * 3);
	cmd.cmd[0] = "unset";
	cmd.cmd[1] = "OLDPWD";
	cmd.cmd[2] = NULL;
	exec_unset(main, &cmd);
	free(cmd.cmd);
	g_error = 0;
	g_pid = 0;
	// if (signal(SIGCHLD, SIG_DFL) == SIG_ERR)
	// 	error_handler(SIGNAL_ERROR, "init");
	// if (signal(SIGCHLD, SIG_DFL) == SIG_ERR)
	// 	error_handler(SIGNAL_ERROR, "init");
}

static int		minishell(t_main *main, char *line)
{
	int		i;
	int		a;

	a = 0;
	i = 1;
	if (line == NULL || line[0] == '\0')
		return (0);
	if (!(main->cmd = malloc(sizeof(t_cmd))))
		error_handler(MALLOC, "minishell");
	ft_bzero(main->cmd, sizeof(t_cmd));
	while(i != 0)
	{
		parse_env(main);
		if (lexer(line) == -1)
			break ;
		i = parser(&main->cmd, line);
		if (main->cmd->red)
			parse_redir(main);
		if (main->cmd->cmd)
			var_handler(main, main->cmd->cmd, 1);
		if (main->cmd->red)
			var_handler(main, main->cmd->red, 0);
		if (main->cmd)
			executor(main);
	}
	if (main->cmd->cmd)
		ft_free_2array(main->cmd->cmd);
	if (main->cmd->red)
		ft_free_2array(main->cmd->red);
	free(main->cmd);
	return (0);
}

/*
** lsof -c - для проверки утечки файловых дескрипторов
*/

static char		*get_line(int *fildes, int i)
{
	char	*line;
	int		status;

	if (i == 1)
	{
		signal(SIGINT, SIG_DFL);
		close(fildes[0]);
		if ((get_next_line(0, &line)) <= 0)
			exit(0);
		ft_putendl_fd(line, fildes[1]);
		close(fildes[1]);
		free(line);
		exit(1);
	}
	else
	{
		wait(&status);
		if (WIFEXITED(status) != 0)
			if (WEXITSTATUS(status) == 0)
				exec_exit(NULL, NULL);
		close(fildes[1]);
		if (get_next_line(fildes[0], &line) <= 0)
			return (NULL);
		return (line);
	}
}

int     main(int argc, char **argv, char **env)
{
	char    *line;
	t_main  main;
	int		fildes[2];

	init(&main, env, argc, argv);
	while (main.exit == 0)
	{
		if (signal(SIGQUIT, ignore_squit) == SIG_ERR)
			error_handler(SIGNAL_ERROR, "main");
		if (signal(SIGINT, ignore_sint) == SIG_ERR)
			error_handler(SIGNAL_ERROR, "main");
		ft_putstr_fd("minishell> ", 1);
		if (pipe(fildes) == -1)
			error_handler(PIPE_ERROR, "main");
		if ((g_pid = fork()) == 0)
			get_line(fildes, 1);
		else if (g_pid == -1)
			error_handler(FORK_ERROR, "main");
		else
			line = get_line(fildes, 0);
		close (fildes[0]);
		minishell(&main, line);
		free(line);
	}
	sleep(100);
	return (0);
}
