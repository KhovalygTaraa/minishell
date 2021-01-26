/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 16:57:40 by swquinc           #+#    #+#             */
/*   Updated: 2021/01/26 18:43:17 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H
# define MALLOC 50
# define EXECVE 51 // возможно valgrind будет ругаться на утечку.
# define STAT 52
# define STAT_DIR 53

typedef struct	s_cmd
{
	char		**cmd;
	int			var;
	int			pipe;
	char		**red;
}				t_cmd;

typedef struct	s_var
{
	char		*name;
	char		*value;
}				t_var;

typedef struct	s_main
{
	char		**env;
	char		**path; //malloc parse_env
	char		*pwd; //malloc parse_env
	char		*home; // malloc parse_env
	pid_t		pid;
	t_list		*vars;
	t_list		*cmds;
}				t_main;
#endif
