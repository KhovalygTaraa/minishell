#include "minishell.h"

// t_main		*init()
// {
// 	t_main	*main;

// 	if (!(main = (t_main *)malloc(sizeof(t_main))))
// 		return (0);
// 	ft_bzero(main, sizeof(t_main));
// 	if (!(main->cmd = (t_cmd *)malloc(sizeof(t_cmd))))
// 		return (0);
// 	ft_bzero(main->cmd, sizeof(t_cmd));
// 	return (main);
// }

static char	*ft_malloc(size_t size)
{
	char	*s;

	if (!(s = (char *)malloc(size)))
		return (0);
	s[size - 1] = '\0';
	return (s);
}

static int	step(char **p, int flag)
{
	if (**p == '\\' && (!(flag & 1) || (flag & 2
		&& (*(*p + 1) == '\\' || *(*p + 1) == '\"' || *(*p + 1) == '$'))))
	{
		++*p;
		return (0);
	}
	if (((**p == '\'' || **p == '\"' || **p == '|' || **p == ';'
		  || **p == '<' || **p == '>' || **p == ' ' || **p == '\0' || **p == '$')
		 && !(flag & 1) && !(flag & 2))
		|| ((flag & 1) && **p == '\'')
		|| ((flag & 2) && (**p == '\"' || **p == '$')))
		return (1);
	return (0);
}

static void	put(char **s, char c)
{
	static size_t	i;
	size_t			j;
	char			*copy;

	if (!c)
		return ;
	if (!*s)
	{
		i = 0;
		*s = ft_malloc(1);
	}
	copy = ft_malloc(i + 2);
	j = 0;
	while ((*s)[j])
	{
		copy[j] = (*s)[j];
		j++;
	}
	copy[i++] = c;
	free(*s);
	*s = copy;
}

static void		push(char ***cmd, char **s)
{
	static size_t	i;
	size_t			j;
	char			**copy;

	if (!*cmd)
	{
		if (!(*cmd = (char **)malloc(8 * 2)))
			return ;
		(*cmd)[0] = *s;
		(*cmd)[1] = 0;
		*s = 0;
		i = 1;
		return ;
	}
	if (!(copy = (char **)malloc(8 * (i + 2))))
		return ;
	j = 0;
	while (j < i)
	{
		copy[j] = (*cmd)[j];
		j++;
	}
	copy[i++] = *s;
	copy[i] = 0;
	*s = 0;
	free(*cmd);
	*cmd = copy;
}

static void		quote_handler(char **s, char **p)
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

static void		redirect_handler(char **s, char **p, t_cmd **cmd)
{
	while ('0' <= **p && **p <= '9')
		put(s, *(*p)++);
	if (**p != '<' && **p != '>')
		return ;
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

static int		terminate_handler(char **s, char **p, t_cmd **cmd)
{
	if (*s)
		push(&((*cmd)->cmd), s);
	if (**p != ' ')
	{
		if (**p == '|')
			(*cmd)->pipe = 1;
		else if (**p == '\0')
			return (0);
		++*p;
		return (1);
	}
	++*p;
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
		type = step(&p, 0);
		if (type)
		{
			if (*p == '$')
			{
				put(&s, *p++);
				put(&s, 1);
			}
			else if (*p == '<' || *p == '>' || ('0' <= *p && *p <= '9'))
				redirect_handler(&s, &p, cmd);
			else if (*p == '\'' || *p == '\"')
				quote_handler(&s, &p);
			else if (!(type = terminate_handler(&s, &p, cmd)))
			{
				p = NULL;
				return (0);
			}
			else if (type == 1)
				return (1);
		}
		else
			put(&s, *p++);
	}
}