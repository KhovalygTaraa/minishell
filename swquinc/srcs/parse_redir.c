/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 12:14:22 by swquinc           #+#    #+#             */
/*   Updated: 2021/03/04 00:27:57 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*parse_filename(char *src)
{
	char	*res;
	int		a;
	int		i;

	i = ft_strlen(src);
	a = -1;
	while (src[++a] != '\0')
	{
		if (src[a] == '>' || src[a] == '<')
		{
			a++;
			if (src[a] == '>')
				a++;
			break ;
		}
	}
	if (!(res = ft_substr(src, a, i)))
		error_handler(MALLOC, "parse_filename");
	return (res);
}

static char		*parse_symb(char *src)
{
	int		a;
	char	*res;

	a = 0;
	res = NULL;
	while (src[a] != '>' && src[a] != '<')
		a++;
	if (src[a] == '>' && src[a + 1] == '>')
	{
		if (!(res = ft_strdup(">>")))
			error_handler(MALLOC, "parse_num4");
	}
	else if (src[a] == '>' || src[a] == '<')
	{
		if (!(res = ft_substr(src, a, 1)))
			error_handler(MALLOC, "parse_num5");
	}
	return (res);
}

static char		*parse_num(char *src)
{
	int		a;
	char	*res;

	a = 0;
	while(src[a] != '<' && src[a] != '>')
		a++;
	if (!(res = ft_substr(src, 0, a)))
		error_handler(MALLOC, "parse_num3");
	return (res);
}

static char		**add(t_main *main, int i, char **res)
{
	char *clean;

	if (main->cmd->red[i][0] >= '0' && main->cmd->red[i][0] <= '9')
	{
		if (!(res = ft_stradd(res, (clean = parse_num(main->cmd->red[i])))))
			error_handler(MALLOC, "parse_redir2");
		free(clean);
	}
	if (!(res = ft_stradd(res, (clean = parse_symb(main->cmd->red[i])))))
			error_handler(MALLOC, "parse_redir3");
	free(clean);
	if (!(res = ft_stradd(res, (clean = parse_filename(main->cmd->red[i])))))
			error_handler(MALLOC, "parse_redir2");
	free(clean);
	return (res);	
}

int		parse_redir(t_main *main)
{
	char	**res;
	int		i;
	int		a;

	a = 0;
	i = 0;
	if (!(res = malloc(sizeof(char*))))
		error_handler(MALLOC, "parse_redir1");
	res[0] = NULL;
	while (main->cmd->red[i] != NULL)
	{
		res = add(main, i, res);
		// if (main->cmd->red[i][0] >= '0' && main->cmd->red[i][0] <= '9')
		// 	if (!(res = ft_stradd(res, parse_num(main->cmd->red[i]))))
		// 		error_handler(MALLOC, "parse_redir2");
		// if (!(res = ft_stradd(res, parse_symb(main->cmd->red[i]))))
		// 		error_handler(MALLOC, "parse_redir3");
		// if (!(res = ft_stradd(res, parse_filename(main->cmd->red[i]))))
		// 		error_handler(MALLOC, "parse_redir2");
		i++;
	}
	ft_free_2array(main->cmd->red);
	main->cmd->red = res;
	return (0);
}