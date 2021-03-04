/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 16:57:40 by swquinc           #+#    #+#             */
/*   Updated: 2021/03/04 05:00:43 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H
# define QUOTES_ERROR 49
# define MALLOC 50
# define EXECVE 51
# define STAT 52
# define STAT_DIR 53
# define CHDIR_ERROR 54
# define HOME_NOT_SET 55
# define PWD_ERROR 56
# define EXPORT_ERROR 57
# define UNSET_ERROR 58
# define OPEN_ERROR 59
# define DUP_ERROR 60
# define PIPE_ERROR 61
# define FORK_ERROR 62
# define SIGNAL_ERROR 63
# define WAIT_ERROR 64
# define LEXER_ERROR 65
# define OLDPWD_NOT_SET 66
# define LEXER_ERROR_FREE 67
# define EXIT_ERROR 68
# define EXIT_ERROR2 69

pid_t			g_pid;
int				g_error;

typedef struct	s_cmd
{
	char		**cmd;
	int			pipe;
	char		**red;
}				t_cmd;

typedef struct s_quote
{
	char		*line;
	int			quote;
}				t_quote;

typedef struct	s_main
{
	char		**env; // malloced -> main
	char		**path; //malloced -> parse_env
	char		*pwd; //malloced -> parse_env
	char		*oldpwd;
	char		*home; // malloced -> parse_env
	char		**export;
	int			exit; //  временная переменная, забыл для чего это
	int			fildes[2]; // for pipe
	int			is_stdout_taken; // for pipe
	int			is_stdin_taken; // for pipe
	int			stdout; // стандартный вывод нужно сохранить
	int			stdin; // стандартный ввод нужно сохранить
	int			relink_fd;
	t_list		*for_quotes;
	t_cmd		*cmd;
}				t_main;
#endif
