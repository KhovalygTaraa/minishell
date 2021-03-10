/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 22:55:23 by swquinc           #+#    #+#             */
/*   Updated: 2021/03/10 20:08:33 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_lvl(t_main *main)
{
	int		i;
	int		a;
	int		res;
	char	*str;

	str = NULL;
	a = 0;
	i = 0;
	while (main->env[i] != NULL)
	{
		if (ft_strncmp("SHLVL=", main->env[i], 6) == 0)
		{
			res = ft_atoi(main->env[i] + 6);
			res++;
			free(main->env[i]);
			str = ft_itoa(res);
			main->env[i] = ft_strjoin("SHLVL=", str);
			free(str);
		}
		i++;
	}
}

int		check_non_pipe_cmd(char **cmd)
{
	if (ft_strcmp(cmd[0], "export") == 0 || ft_strcmp(cmd[0], "unset") == 0)
		return (0);
	if (ft_strcmp(cmd[0], "exit") == 0 || ft_strcmp(cmd[0], "cd") == 0)
		return (0);
	return (1);
}

int		is_valid(char *str)
{
	int		i;
	int		a;

	a = 0;
	i = 0;
	while (str[a] != '=')
		a++;
	while (str[i] != '\0' && a != i)
	{
		if (!ft_isalnum(str[i]))
			return (0);
		i++;
	}
	return (1);
}
