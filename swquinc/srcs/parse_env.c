/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 17:00:49 by swquinc           #+#    #+#             */
/*   Updated: 2021/03/04 05:08:34 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		parse_home(t_main *main)
{
	int		i;
	char	*path_line;

	path_line = NULL;
	i = 0;
	while (main->env[i] != NULL)
	{
		if (ft_strncmp(main->env[i], "HOME=", 5) == 0)
			path_line = main->env[i] + 5;
		i++;
	}
	if (path_line == NULL)
	{
		main->home = path_line;
		return (0);
	}
	if (!(path_line = ft_strjoin(path_line, "/")))
		error_handler(MALLOC, "parse_path");
	main->home = path_line;
	return (0);
}

static int		parse_pwd(t_main *main)
{
	int		i;
	char	*path_line;

	i = 0;
	while (main->env[i] != NULL)
	{
		if (ft_strncmp(main->env[i], "PWD", 3) == 0)
			path_line = main->env[i] + 4;
		i++;
	}
	if (!(path_line = ft_strjoin(path_line, "/")))
		error_handler(MALLOC, "parse_path");
	main->pwd = path_line;
	return (0);
}

static int		parse_path(t_main *main)
{
	int		i;
	char	*path_line;
	char	**path;

	path_line = NULL;
	path = NULL;
	i = -1;
	while (main->env[++i])
		if (ft_strncmp(main->env[i], "PATH", 4) == 0)
			path_line = main->env[i] + 5;
	if (path_line)
	{
		if (!(path = ft_split_upd(path_line, ":")))
			error_handler(MALLOC, "parse_path");
	}
	else
		return (-1);
	i = -1;
	while (path[++i])
	{
		if (!(path[i] = ft_strjoin_free(path[i], "/")))
			error_handler(MALLOC, "parse_path");
	}
	main->path = path;
	return (0);
}

int			parse_env(t_main *main)
{
	if (main->path != NULL)
		ft_free_2array(main->path);
	free(main->pwd);
	free(main->home);
	parse_path(main);
	parse_pwd(main);
	parse_home(main);
	return (0);
}