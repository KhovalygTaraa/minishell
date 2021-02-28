/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 19:43:38 by swquinc           #+#    #+#             */
/*   Updated: 2021/02/28 13:38:44 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	step(char **p, int flag)
{
	if (**p == '\\' && (!(flag & 1) || (flag & 2
		&& (*(*p + 1) == '\\' || *(*p + 1) == '\"' || *(*p + 1) == '$'))))
	{
		++*p;
		return (0);
	}
	if (((**p == '\'' || **p == '\"' || **p == '|' || **p == ';' || **p == '$'
		|| **p == '<' || **p == '>' || **p == ' ' || **p == '\0')
			&& !(flag & 1) && !(flag & 2))
		|| ((flag & 1) && **p == '\'')
		|| ((flag & 2) && (**p == '\"' || **p == '$')))
		return (1);
	return (0);
}

static void	quote_handler(char **s, char **p)
{
	int		type;

	if (**p == '\'')
	{
		++*p;
		while (**p != '\'')
			put(s, *(*p)++);
		++*p;
	}
	else if (*(*p)++ == '\"')
	{
		while (!(type = step(p, 2)) || **p != '\"')
		{
			put(s, *(*p)++);
			if (type && *(*p - 1) == '$')
				put(s, 1);
		}
		++*p;
	}
}

static void	redirect_handler(char **s, char **p, t_cmd **cmd)
{
	while ('0' <= **p && **p <= '9')
		put(s, *(*p)++);
	if (**p != '<' && **p != '>')
		return ;
	put(s, *(*p)++);
	if (**p == '>')
		put(s, *(*p)++);
	while (**p == ' ')
		++*p;
	while (!(**p == '|' || **p == ';' || **p == ' '
		|| **p == '<' || **p == '>' || **p == '\0'))
	{
		if (!step(p, 0))
			put(s, *(*p)++);
		else if (**p == '\'' || **p == '\"')
			quote_handler(s, p);
		else if (**p == '$')
		{
			put(s, *(*p)++);
			put(s, 1);
		}
	}
	push(&((*cmd)->red), s);
}

static int	parser_switch(char **s, char **p, t_cmd **cmd)
{
	int		type;

	if (*(*p) == '$' || **p == '~')
	{
		put(s, *(*p)++);
		put(s, 1);
	}
	else if (*(*p) == '<' || *(*p) == '>' || ('1' <= *(*p) && *(*p) <= '9')
		|| (*(*p) == '0' && (*(*p + 1) == '<' || *(*p + 1) == '>')))
		redirect_handler(s, p, cmd);
	else if (*(*p) == '\'' || *(*p) == '\"')
		quote_handler(s, p);
	else if (!(type = terminate_handler(s, p, cmd)))
	{
		*p = NULL;
		return (0);
	}
	else if (type == 1)
		return (1);
	return (-1);
}

int			parser(t_cmd **cmd, char *line)
{
	char		*s;
	static char	*p;
	int			type;

	if (!p)
		p = line;
	s = 0;
	if (!(*cmd = (t_cmd *)malloc(sizeof(t_cmd))))
		error_handler(MALLOC, "parser");
	ft_bzero(*cmd, sizeof(t_cmd));
	while (1)
	{
		if (step(&p, 0))
		{
			type = parser_switch(&s, &p, cmd);
			if (type == 0)
				return (0);
			else if (type == 1)
				return (1);
		}
		else
			put(&s, *p++);
	}
}
