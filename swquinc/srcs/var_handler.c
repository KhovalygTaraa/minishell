/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 19:25:34 by swquinc           #+#    #+#             */
/*   Updated: 2021/02/09 16:12:40 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// echo "$ PWD"
// echo $ PWD
// echo "$PWD"
// echo $PWD
// echo \$PWD
// echo '$PWD'

// структура хендлера такова, если находим $, то проверяем переменная это или нет, если да, то вырезаем все что до $ в отдельный одномерный массив и добавляем его в двумерный массив res. 
// вторым шагом ищем конец переменной, конец обозначается символами '\0', '$' и ' ';  Если мы встретили эти символы, то вырезаем название переменной в отдельный одномерный массив и добавляем в двумерный массив res
// третьим шагом мы должны передать новое начало строки (то есть конец перменной + 1) для поиска следующего $.



static char		*put_var(t_main *main, char *var, char **origin)
{
	char	*res;
	int		i;
	int		a;

	i = 0;
	a = 0;
	res = NULL;
	while (var[i] != '\0' && var[i] != '$' && var[i] != ' ')
		i++;
	*origin = var + i;
	var = ft_substr(var, 0, i);
	while (main->env[a] != NULL)
	{
		if (ft_strncmp(var, main->env[a], i) == 0 && main->env[a][i] == '=')
			res = ft_strdup(main->env[a] + i + 1);
		a++;
	}
	return (res);
}

static char		**var_seeker(t_main *main, char *src)
{
	char	**res;
	char	*dollar;
	char	*origin;
	int		i;
	int		a;
	int		b;

	res = malloc(sizeof(char*));
	res[0] = NULL;
	i = 0;
	b = 0;
	a = 0;
	while (src[i] != NULL)
	{
		origin = src[i];
		dollar = src[i];
		while ((a = ft_strchr_index(origin, '$')) != INT_MAX)
		{
			b = b + a + 2;
			if (origin[++a] == ' ')
			{
				res = ft_stradd(res, ft_substr(dollar, 0, b - 2));
				res = ft_stradd(res, put_var(main, origin + a + 1, &dollar));
				b = 0;
				origin = dollar;
			}
			else
				origin = origin + a + 1;
		}
		i++;
	}
	return (res);
}

int		var_handler(t_main *main)
{
	int		i;
	char	**res;

	i = 0;
	res = var_seeker(main, main->cmd->cmd);
	while (main->cmd->cmd[i] != NULL)
	{
		var_seeker(main, main->cmd->cmd[i]);
		i++;
	}
	i = 0;
	while (main->cmd->red[i] != NULL)
	{
		i++;
	}
	while (res[i] != NULL)
	{
		ft_putstr_fd(res[i], 1);
		ft_putchar_fd('$', 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
	return (0);
}