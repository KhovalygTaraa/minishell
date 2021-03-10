/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 22:34:42 by swquinc           #+#    #+#             */
/*   Updated: 2021/03/10 23:07:27 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <sys/errno.h>
# include <stdio.h>
# include <limits.h>
# include "libft.h"
# include "structures.h"

int		parser(t_cmd **cmd, char *line);
int		lexer(char *line);
int		parse_env(t_main *main);
int		parse_redir(t_main *main);
int		executor(t_main *main);
int		exec_cd(t_main *main, t_cmd *cmd);
void	exec_echo(t_cmd *cmd);
void	exec_env(t_main *main, t_cmd *cmd);
void	exec_exit(t_main *main, t_cmd *cmd);
int		exec_export(t_main *main, t_cmd *cmd);
int		exec_pwd(t_main *main, t_cmd *cmd);
int		exec_unset(t_main *main, t_cmd *cmd);
void	exec(t_main *main, t_cmd *cmd);
void	ft_perror(const char *str);
int		error_handler(int code, char *str);
void	ignore_squit(int code);
void	ignore_sint(int code);
void	ignore_squit2(int code);
void	ignore_sint2(int code);
char	**ft_2arraydup(char **array);
char	**ft_stradd(char **array, char *str);
int		ft_strchr_index(const char *s, int c);
int		var_handler(t_main *main, char **src, int a);
void	ft_free_2array(char **array);
void	put(char **s, char c);
void	push(char ***cmd, char **s);
int		terminate_handler(char **s, char **p, t_cmd **cmd);
void	shell_lvl(t_main *main);
int		check_non_pipe_cmd(char **cmd);
int		is_valid(char *str);

#endif
