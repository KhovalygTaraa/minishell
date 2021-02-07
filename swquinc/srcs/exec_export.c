/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 19:40:35 by swquinc           #+#    #+#             */
/*   Updated: 2021/02/06 15:20:23 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Вывод отсортированного env с добавлением declare -x перед переменными
** и двойных кавычек для значений пермеменных.
*/

static void		print_mod_sorted_env(char **env)
{
	int		i;
	int		a;
	int		flag;

	i = 0;
	while (env[i] != 0)
	{
		a = 0;
		flag = 0;
		ft_putstr_fd("declare -x ", 1);
		while (env[i][a] != '\0')
		{
			ft_putchar_fd(env[i][a], 1);
			if (env[i][a] == '=' && flag == 0)
			{
				flag = 1;
				ft_putchar_fd('"', 1);
			}
			a++;
		}
		ft_putchar_fd('"', 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
}

/*
** Cортировка вставками (insert sort) переменных окружения (env) по алфавиту.
** По таблице ascii сортировать мы будем во возрастанию. От A(65) до z(122).
**
** Первым циклом проходимся по двумерному массиву, вторым циклом сдвигаем
** последнюю строку в начало двумерного массива до тех пор, пока строка
** не окажется в самом начале двумерного массива или пока она не встретит
** строку у к-ой первый элемент меньше (ascii), чем элемент сдвигаемой строки.
**
** Функцией ft_strcmp проверяем равны ли первые элементы строк.
** Если не равны, возвращается их разность. Если результат больше 0,
** то значит, что рассматриваемая строка сдвигается, так как она меньше.
*/

static void		sort_by_alphabet(char **env)
{
	int		i;
	int		k;
	int		a;
	char	*tmp;
	int		flag;

	a = 0;
	i = -1;
	while (env[++i] != NULL)
	{
		k = i;
		while (k > 0 && env[k - 1][a] >= env[k][a])
		{
			flag = ft_strcmp(env[k - 1], env[k]);
			if (flag > 0)
			{
				tmp = env[k];
				env[k] = env[k - 1];
				env[k - 1] = tmp;
			}
			k--;
		}
	}
}

/*
** This function check is a variable defined in main->env or not.
** If variable defined we redefined it. And return 1.
** Else we return 0. Also we return 1, if variable without '='.
** We do this bcause we haven't implement "set" builtin in our shell.
*/

static int		redefine_var(t_main *main, char *var)
{
	int		i;
	int		k;
	char	*link;

	i = 0;
	if (!(link = ft_strchr(var, '=')))
		return (1);
	while (var[i] != '=')
		i++;
	if (!(link = ft_substr(var, 0, i + 1)))
		error_handler(MALLOC, "export_redefine_var");
	k = -1;
	while (main->env[++k] != NULL)
	{
		if (ft_strncmp(link, main->env[k], i) == 0)
		{
			free(link);
			free(main->env[k]);
			if (!(main->env[k] = ft_strdup(var)))
				error_handler(MALLOC, "export_redefine_var");
			return (1);
		}
	}
	return (0);
}

/*
** This function add all variables in two-dimensional array **cmd to
** main->env array. Also this function check is a character a letter.
** We should ignore "_=".
*/

static int		add_vars(t_main *main, t_cmd *cmd)
{
	int		flag;
	int		i;
	int		is_defined;

	is_defined = 0;
	i = 0;
	while (cmd->cmd[++i] != NULL)
	{
		flag = 0;
		if (!ft_isalpha(cmd->cmd[i][0]) && cmd->cmd[i][0] != '_')
			flag = error_handler(EXPORT_ERROR, cmd->cmd[i]);
		else if (ft_strncmp(cmd->cmd[i], "_=", 2) != 0 && flag == 0)
		{
			is_defined = redefine_var(main, cmd->cmd[i]);
			if (!is_defined)
				if (!(main->env = ft_stradd(main->env, cmd->cmd[i])))
					error_handler(MALLOC, "exec_export");
		}
	}
	return (flag);
}

/*
** Export может создавать переменные и присваивать им значения одновременно.
** Переменная должны начинаться на букву или '_'.
** Пример: export var=value, export _var=value
**
** Команда export может переопределять значение переменных.
** Пример: export PWD=/Users/ или export var=value
**
** Команда export без аргументов и параметров выводит
** отсортированный список переменных окружения.
** Добавляет в начало каждой переменной "declare -x"
** и оборачивает значения переменных в двойные кавычки.
*/

int				exec_export(t_main *main, t_cmd *cmd)
{
	char	**sorted_env;
	int		res;

	res = 0;
	if (cmd->cmd[1] == NULL)
	{
		if (!(sorted_env = ft_2arraydup(main->env)))
			error_handler(MALLOC, "exec_export");
		sort_by_alphabet(sorted_env);
		print_mod_sorted_env(sorted_env);
	}
	else
		res = add_vars(main, cmd);
	return (res);
}
