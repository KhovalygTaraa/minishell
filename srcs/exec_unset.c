/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 19:41:02 by swquinc           #+#    #+#             */
/*   Updated: 2021/03/04 19:46:16 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		defined(t_main *main, int i, int a)
{
	char	**new_env;
	int		k;

	k = 0;
	while (main->env[k] != NULL)
		k++;
	if (!(new_env = malloc(sizeof(char*) * (k))))
		error_handler(MALLOC, "unset_if_defined");
	a = -1;
	k = -1;
	while (main->env[++a] != NULL)
	{
		if (a == i)
			a++;
		new_env[++k] = ft_strdup(main->env[a]);
		if (main->env[a] == NULL)
			a--;
	}
	ft_free_2array(main->env);
	if (new_env[k] != NULL)
		new_env[++k] = NULL;
	main->env = new_env;
}

static void		remove_var(t_main *main, char *var)
{
	int		i;
	int		a;

	if (ft_strcmp(var, "OLDPWD") == 0)
	{
		free(main->oldpwd);
		main->oldpwd = NULL;
	}
	if (ft_strcmp(var, "PATH") == 0)
	{
		ft_free_2array(main->path);
		main->path = NULL;
	}
	if (!(var = ft_strjoin(var, "=")))
		error_handler(MALLOC, "unset_remove_var");
	a = ft_strlen(var);
	i = -1;
	while (main->env[++i] != NULL)
		if (ft_strncmp(var, main->env[i], a) == 0)
		{
			defined(main, i, a);
			break ;
		}
	free(var);
}

/*
** Данная команда удаляет из main->env переменную.
** Если переменной нет, то ничего не делает.
*/

int				exec_unset(t_main *main, t_cmd *cmd)
{
	int		i;
	int		flag;

	flag = 0;
	i = 1;
	while (cmd->cmd[i] != NULL)
	{
		if (!ft_isalpha(cmd->cmd[i][0]) && cmd->cmd[i][0] != '_')
			flag = error_handler(UNSET_ERROR, cmd->cmd[i]);
		else
			remove_var(main, cmd->cmd[i]);
		i++;
	}
	return (flag);
}
