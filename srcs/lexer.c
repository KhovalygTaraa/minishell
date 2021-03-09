/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 19:43:38 by swquinc           #+#    #+#             */
/*   Updated: 2021/02/25 00:23:45 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*cpy(const char *p)
{
	char	*s;

	s = malloc(4);
	s[0] = '`';
	s[1] = *p;
	s[2] = '\'';
	s[3] = 0;
	return (s);
}

static int	step(char **p, int flag)
{
	if (**p == '\\' && (!(flag & 1)
		|| (flag & 2 && (*(*p + 1) == '\\' || *(*p + 1) == '\"'))))
	{
		++*p;
		return (!**p);
	}
	if (((**p == '\'' || **p == '\"' || **p == '|' || **p == ';'
		|| **p == '<' || **p == '>')
		&& !(flag & 1) && !(flag & 2))
		|| ((flag & 1) && **p == '\'')
		|| ((flag & 2) && **p == '\"'))
		return (1);
	return (0);
}

static int	conflicts(char **p, char **cur, int *n)
{
	if (**p == '|' && (!*cur && !*n))
		return (error_handler(LEXER_ERROR, "`|\'"));
	if (**p == ';' && *(*p + 1) == ';')
		return (error_handler(LEXER_ERROR, "`;;\'"));
	if (**p == ';' && (!*cur && !*n))
		return (error_handler(LEXER_ERROR, "`;\'"));
	if ((**p == '|' || **p == ';') && (*cur && **cur != '\'' && **cur != '\"')
		&& !*n)
		return (error_handler(LEXER_ERROR_FREE, cpy(*p)));
	if (*cur && (**cur == '>' || **cur == '<')
		&& (**p == '<' || (**p == '>' && *(*p + 1) != '>')) && !*n)
		return (error_handler(LEXER_ERROR_FREE, cpy(*p)));
	if (*cur && (**cur == '>' || **cur == '<')
		&& **p == '>' && *(*p + 1) == '>' && !*n)
	{
		++*p;
		return (error_handler(LEXER_ERROR, "`>>\'"));
	}
	if (!*cur && **p == '>' && *(*p + 1) == '>')
		++*p;
	*cur = *p;
	*n = 0;
	return (0);
}

static int	loop(char **p, char **cur, int *flag)
{
	int		tmp;
	int		n;

	n = 0;
	while (1)
	{
		while (**p == ' ')
			++*p;
		if (**p == '\0')
			return (n);
		tmp = step(p, *flag);
		(**p == '\'' && tmp) ? *flag ^= 1 : 0;
		(**p == '\"' && tmp) ? *flag ^= 2 : 0;
		if (tmp)
		{
			if (conflicts(p, cur, &n) == -1)
				return (-1);
		}
		else
			++n;
		++*p;
	}
}

int			lexer(char *line)
{
	char	*p;
	char	*cur;
	int		flag;
	int		n;

	p = line;
	cur = 0;
	flag = 0;
	while (*p == ' ')
		p++;
	if ((n = loop(&p, &cur, &flag)) == -1)
		return (-1);
	if (cur && ((*cur == '|' && !n) || flag))
		return (error_handler(LEXER_ERROR_FREE, cpy(cur)));
	if (cur && (*cur == '<' || *cur == '>') && !n)
		return (error_handler(LEXER_ERROR, "`newline\'"));
	return (0);
}
