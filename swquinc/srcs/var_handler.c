/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 19:25:34 by swquinc           #+#    #+#             */
/*   Updated: 2021/02/09 18:45:13 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*put_var(t_main *main, char *var, char **origin)
{
	char	*res;
	int		i;
	int		a;

	i = 0;
	a = -1;
	res = NULL;
	while (var[i] != '\0' && var[i] != '$' && var[i] != ' ')
		i++;
	*origin = var + i;
	if (!(var = ft_substr(var, 0, i)))
		return (NULL);
	while (main->env[++a] != NULL)
		if (ft_strncmp(var, main->env[a], i) == 0 && main->env[a][i] == '=')
			res = main->env[a] + i + 1;
	free(var);
	return (res);
}

static char		**var_seeker(t_main *main, char *src, char *origin, char **res)
{
	int		a;
	int		b;
	char	*dollar;

	dollar = origin;
	b = 0;
	a = 0;
	while ((a = ft_strchr_index(origin, '$')) != INT_MAX)
	{
		b = b + a + 2;
		if (origin[++a] == ' ')
		{
			if (!(res = ft_stradd(res, ft_substr(dollar, 0, b - 2))))
				error_handler(MALLOC, "var_seeker");
			if (!(res = ft_stradd(res, put_var(main, origin + a + 1, &dollar))))
				error_handler(MALLOC, "var_seeker");
			b = 0;
			origin = dollar;
		}
		else
			origin = origin + a + 1;
	}
	return (res);
}

static void		replace_cmd(char **str, char **new_str)
{
	int		i;
	char	*res;

	i = 0;
	res = new_str[i];
	while (new_str[i + 1] != NULL)
	{
		res = ft_strjoin(res, new_str[i + 1]);
		free(new_str[i]);
		i++;
	}
	free (new_str);
	// free(str); // выдает free error так как в моем заменителе парсера я не аллоцирую память.
	*str = res;
}

int		var_handler(t_main *main)
{
	int		i;
	char	**res;
	char	*origin;
	char	*dollar;

	i = -1;
	while (main->cmd->cmd[++i] != NULL)
	{
		if (!(res = malloc(sizeof(char*))))
			error_handler(MALLOC, "var_handler");
		res[0] = NULL;
		origin = main->cmd->cmd[i];
		dollar = main->cmd->cmd[i];
		res = var_seeker(main, main->cmd->cmd[i], origin, res);
		if (res[0] != NULL)
			replace_cmd(&main->cmd->cmd[i], res);
	}
	i = 0;
	while (main->cmd->cmd[i] != NULL)
	{
		ft_putstr_fd(main->cmd->cmd[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
	return (0);
}