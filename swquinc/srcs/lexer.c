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

static int	conflicts(char **p, char **cur, int *n)
{
	if (!*n)
	{
		if ((**p == '|' || **p == ';')
			&& ((!*cur && !*n) || (**cur != '\'' && **cur != '\"')))
		{
			if (**p == ';' && (*(*p + 1) == ';' || (*cur && **cur == ';')))
				return (error_handler(LEXER_ERROR, "`;;\'"));
			return (error_handler(LEXER_ERROR, cpy(*p)));
		}
		if (*cur && (**cur == '>' || **cur == '<')
			&& (**p == '<' || (**p == '>' && *(*p + 1) != '>')))
			return (error_handler(LEXER_ERROR, cpy(*p)));
		if (*cur && (**cur == '>' || **cur == '<')
			&& **p == '>' && *(*p + 1) == '>')
		{
			++*p;
			return (error_handler(LEXER_ERROR, "`>>\'"));
		}
	}
	if (!*cur && **p == '>' && *(*p + 1) == '>')
		++*p;
	*cur = *p;
	*n = 0;
	return (0);
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

static int	loop(char **p, char **cur, int *flag)
{
	int		tmp;
	int		n;

	n = 0;
	while (1)
	{
		tmp = step(p, *flag);
		if (**p == 0)
			break ;
		while (**p == ' ')
			++*p;
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
	return (0);
}

int			lexer(char *line)
{
	char	*p;
	char	*cur;
	int		flag;

	p = line;
	cur = 0;
	flag = 0;
	while (*p == ' ')
		p++;
	if (loop(&p, &cur, &flag) == -1)
		return (-1);
	if (cur && (*cur == '|' || flag))
		return (error_handler(LEXER_ERROR, cpy(cur)));
	else if (cur && (*cur == '<' || *cur == '>'))
		return (error_handler(LEXER_ERROR, "`newline\'"));
	return (0);
}
