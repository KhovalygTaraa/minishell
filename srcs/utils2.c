/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 22:55:23 by swquinc           #+#    #+#             */
/*   Updated: 2021/03/10 00:29:15 by swquinc          ###   ########.fr       */
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
