/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 19:25:34 by swquinc           #+#    #+#             */
/*   Updated: 2021/03/12 12:50:40 by hovalygta        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*put_var(t_main *main, char *var, char **origin)
{
	char	*res;
	int		i;
	int		a;
	char	*var1;

	i = 0;
	a = -1;
	res = NULL;
	while ((var[i] >= 48 && var[i] <= 57) || (var[i] >= 65 && var[i] <= 90)
		|| (var[i] >= 97 && var[i] <= 122) || var[i] == '?')
		i++;
	*origin = var + i;
	if (!(var1 = ft_substr(var, 0, i)))
		return (NULL);
	while (main->env[++a] != NULL)
		if (ft_strncmp(var1, main->env[a], i) == 0 && main->env[a][i] == '=')
			if (!(res = ft_strdup(main->env[a] + i + 1)))
				error_handler(MALLOC, "put_var");
	if (ft_strcmp(var1, "?") == 0 && !(res = ft_itoa(g_error)))
		error_handler(MALLOC, "put_var");
	free(var1);
	if (res == NULL)
		res = ft_strdup("");
	return (res);
}

static char	*var_seeker_ext(const int *a, int *b, char **origin, int i)
{
	char	*dollar;

	dollar = NULL;
	if (i == 1)
	{
		*b += *a + 1;
		*origin += *a + 1;
	}
	else
	{
		dollar = ft_strdup(*origin);
		if (dollar[0] == '$')
			dollar[0] = '\0';
	}
	return (dollar);
}

static void	var_seeker(t_main *main, char *dollar, char *or, char ***res)
{
	int		a;
	int		b;
	char	*tmp;
	char	*c;

	b = 0;
	while ((a = ft_strchr_index(or, '$')) != INT_MAX)
		if (or[++a] == 1)
		{
			b = b + a + 1;
			c = ft_substr(dollar, 0, b - 2);
			free(dollar);
			if (!(*res = ft_stradd(*res, c)))
				error_handler(MALLOC, "var_seeker");
			free(c);
			c = put_var(main, or + a + 1, &tmp);
			if (!(*res = ft_stradd(*res, c)))
				error_handler(MALLOC, "var_seeker");
			free(c);
			or = tmp;
			dollar = var_seeker_ext(&a, &b, &tmp, 2);
		}
		else
			var_seeker_ext(&a, &b, &or, 1);
	free(dollar);
}

static void	replace_cmd(char **str, char **new_str)
{
	int		i;
	char	*res;

	i = 0;
	res = new_str[i];
	while (new_str[i + 1] != NULL)
	{
		res = ft_strjoin_free(res, new_str[i + 1]);
		free(new_str[i + 1]);
		i++;
	}
	free(new_str);
	free(*str);
	*str = res;
}

int			var_handler(t_main *main, char **src, int a)
{
	int		i;
	char	**res;
	char	*tmp;

	i = -1;
	while (src[++i] != NULL)
	{
		if (!(res = malloc(sizeof(char*))))
			error_handler(MALLOC, "var_handler");
		tmp = ft_strdup(src[i]);
		res[0] = NULL;
		var_seeker(main, ft_strdup(tmp), tmp, &res);
		free(tmp);
		if (res[0] != NULL)
		{
			if (a == 1)
				replace_cmd(&main->cmd->cmd[i], res);
			else
				replace_cmd(&main->cmd->red[i], res);
		}
		else
			ft_free_2array(res);
	}
	g_error = 0;
	return (0);
}
