#include "minishell.h"

static char *cpy(const char *p)
{
	char	*s;

	s = malloc(2);
	s[0] = *p;
	s[1] = 0;
	return (s);
}

static int	conflicts(char **p, char **cur, int *n)
{
	if (!*n)
	{
		if ((**p == '|' || **p == ';') && *cur == 0 && !*n)
			return (error_handler(LEXER_ERROR, cpy(*p)));
		if ((**p == '|' || **p == ';') && **cur != '\'' && **cur != '\"')
			return (error_handler(LEXER_ERROR, cpy(*p)));
		if ((**cur == '>' || **cur == '<') && (**p == '<' || (**p == '>' && *(*p + 1) != '>')))
			return (error_handler(LEXER_ERROR, cpy(*p)));
		if ((**cur == '>' || **cur == '<') && **p == '>' && *(*p + 1) == '>')
		{
			++*p;
			return (error_handler(LEXER_ERROR, ">>"));
		}
	}
	*cur = *p;
//	++*p;
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

int			lexer(char *line)
{
	char	*p;
	char	*cur;
	int		flag;
	int		tmp;
	int		n;

	p = line;
	cur = 0;
	flag = 0;
	n = 0;
	while (*p == ' ')
		p++;
	while (1)
	{
		tmp = step(&p, flag);
		if (*p == 0)
			break;
		while (*p == ' ')
			p++;
		(cur && *cur == '\'' && !(flag & 2)) ? flag ^= 1 : 0;
		(cur && *cur == '\"' && !(flag & 1)) ? flag ^= 2 : 0;
		if (tmp)
			conflicts(&p, &cur, &n);
		else
			n++;
		++p;
	}
	if (cur && (*cur == '|' || flag))
		return (error_handler(LEXER_ERROR, cpy(cur)));
	else if (cur && (*cur == '<' || *cur == '>'))
		return (error_handler(LEXER_ERROR, "newline"));
	return (0);
}
