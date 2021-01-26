/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 17:00:49 by swquinc           #+#    #+#             */
/*   Updated: 2021/01/26 18:33:18 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		parse_home(t_main *main)
{
	int		i;
	char	*path_line;

	i = 0;
	while (main->env[i] != NULL)
	{
		if (ft_strncmp(main->env[i], "HOME", 3) == 0)
			path_line = main->env[i] + 4;
		i++;
	}
	if (!(path_line = ft_strjoin(path_line, "/")))
		ft_putendl_fd("Error: malloc error", 1);
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
		ft_putendl_fd("Error: malloc error", 1);
	main->pwd = path_line;
	return (0);
}

static int		parse_path(t_main *main)
{
	int		i;
	char	*path_line;
	char	**path;

	path = NULL;
	i = -1;
	while (main->env[++i])
		if (ft_strncmp(main->env[i], "PATH", 4) == 0)
			path_line = main->env[i] + 5;
	if (path_line)
	{
		if (!(path = ft_split_upd(path_line, ":")))
			ft_putendl_fd("Error: malloc error", 1);
	}
	else
		ft_putendl_fd("Error: PATH didn't exist", 1);
	i = -1;
	while (path[++i])
	{
		if (!(path[i] = ft_strjoin_free(path[i], "/")))
			ft_putendl_fd("Error: malloc error", 1);
	}
	main->path = path;
	return (0);
}

int			parse_env(t_main *main)
{
	parse_path(main);
	parse_pwd(main);
	return (0);
}