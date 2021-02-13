#include "minishell.h"

static int		conflicts(int c, int *p)
{
	if ((c - 256 == '|' || c - 256 == ';') && *p == 0)
		return (-1);
	if (c > 255 && *p > 255)
	{
		if (*p == '>' + 512 && c - 256 == '>')
			return (-1);
		if (c - 256 != '\'' && c - 256 != '\"'
			&& *p - 256 != '\'' && *p - 256 != '\"'
			&& (*p - 256 == '|' || *p - 256 == '<' || *p - 256 == '>'
				|| c - 256 == '|' || c - 256 == ';'))
		{
			if (*p - 256 == '>' && c - 256 == '>')
				*p = c + 256;
			else
				return (-1);
		}
	}
	if (*p < 512)
		*p = c;
	return (0);
}

static int		step(char *line, int *i, int flag)
{
	if (line[*i] == '\\' && (!(flag & 1) || (flag & 2
		&& (line[*i + 1] == '\\' || line[*i + 1] == '\"'))))
	{
		++*i;
		if (line[(*i)++])
			return (line[*i - 1]);
		else
			return (256);
	}
	if (((line[*i] == '\'' || line[*i] == '\"' || line[*i] == '|'
		|| line[*i] == ';' || line[*i] == '<' || line[*i] == '>')
		&& !(flag & 1) && !(flag & 2))
		|| ((flag & 1) && line[*i] == '\'')
		|| ((flag & 2) && (line[*i] == '\"' || line[*i] == '\\')))
		return (line[(*i)++] + 256);
	return (line[(*i)++]);
}

int		lexer(char *line)
{
	int		i;
	int		c;
	int		p;
	int		flag;

	i = 0;
	p = 0;
	flag = 0;
	while (line[i] == ' ')
		i++;
	while ((c = step(line, &i, flag)) != 0)
	{
		while (line[i] == ' ' && !flag)
			i++;
		if (conflicts(c, &p))
			return (-1);
		(c == '\'' + 256 && !(flag & 2)) ? flag ^= 1 : 0;
		(c == '\"' + 256 && !(flag & 1)) ? flag ^= 2 : 0;
	}
	if (p == 256 || p - 256 == '|' || p - 256 == '<' || p - 256 == '>' || flag)
		return (-1);
	return (0);
}
