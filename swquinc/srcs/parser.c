#include "minishell.h"

// // static void	error_handler(int code, char *s)
// // {
// // 	return ;
// // }

// static char	*ft_malloc(size_t size)
// {
// 	char	*s;

// 	if (!(s = (char *)malloc(size)))
// 		error_handler(MALLOC, "ft_mallloc");
// 	s[size - 1] = '\0';
// 	return (s);
// }


// static int		step(char **p, int flag)
// {
// 	if (**p == '\\' && (!(flag & 1) || (flag & 2
// 		&& (*(*p + 1) == '\\' || *(*p + 1) == '\"' || *(*p + 1) == '$'))))
// 	{
// 		++*p;
// 		return (0);
// 	}
// 	if (((**p == '\'' || **p == '\"' || **p == '|' || **p == ';'
// 		|| **p == '<' || **p == '>' || **p == ' ' || **p == '\0')
// 		&& !(flag & 1) && !(flag & 2))
// 		|| ((flag & 1) && **p == '\'')
// 		|| ((flag & 2) && (**p == '\"' || **p == '$')))
// 		return (1);
// 	return (0);
// }

// static void	put(char **s, char c)
// {
// 	static size_t	i;
// 	size_t			j;
// 	char			*copy;

// 	printf("-------------%c\n", c);
// 	if (!c)
// 		return ;
// 	if (!*s)
// 	{
// 		*s = ft_malloc(2);
// 		**s = c;
// 		i = 1;
// 		return ;
// 	}
// 	copy = ft_malloc(i + 2);
// 	j = 0;
// 	while ((*s)[j])
// 	{
// 		copy[j] = (*s)[j];
// 		j++;
// 	}
// 	copy[i++] = c;
// 	free(*s);
// 	*s = copy;
// }

// static void		push(char ***cmd, char **s)
// {
// 	// static size_t i;
// 	size_t j;
// 	char **copy;

// 	if (!*cmd)
// 	{
// 		if (!(*cmd = (char **)malloc(8 * 2)))
// 			error_handler(1, "");
// 		(*cmd)[0] = *s;
// 		(*cmd)[1] = 0;
// 		*s = 0;
// 		// i = 1;
// 		return ;
// 	}
// 	j = 0;
// 	while ((*cmd)[j])
// 		j++;
// 	if (!(copy = (char **)malloc(8 * (j + 2))))
// 		error_handler(1, "");
// 	j = 0;
// 	while ((*cmd)[j])
// 	{
// 		copy[j] = (*cmd)[j];
// 		j++;
// 	}
// 	copy[j++] = *s;
// 	copy[j] = 0;
// 	*s = 0;
// 	free(*cmd);
// 	*cmd = copy;
// 	j = 0;
// }
// // static void	push(t_main *main, char **s)
// // {
// // 	static size_t	i;
// // 	size_t			j;
// // 	char			**copy;

// // 	if (!main->cmd)
// // 	{
// // 		// if (!(*cmd = (char **)malloc(8)))
// // 			// error_handler(1, "");
// // 		*cmd = ft_stradd(main->cmd, *s);
// // 		free(*s);
// // 		*s = 0;
// // 		i = 1;
// // 		return ;
// // 	}
// // 	if (!(copy = (char **)malloc(8)))
// // 		error_handler(1, "");
// // 	j = 0;
// // 	while ((*cmd)[j])
// // 	{
// // 		printf("%s\n", (*cmd)[j]);
// // 		copy[j] = (*cmd)[j];
// // 		j++;
// // 	}
// // 	copy[i++] = *s;
// // 	*s = 0;
// // 	free(*cmd);
// // 	*cmd = copy;
// // }

// static void	quote_handler(char **s, char **p)
// {
// 	int		type;

// 	if (**p == '\'')
// 	{
// 		put(s, '\'');
// 		++*p;
// 		while (**p != '\'')
// 		{
// 			put(s, *(*p)++);
// 			// if (*(*p - 1) == '$')
// 				// put(s, ' ');
// 		}
// 		put(s, '\'');
// 		++*p;
// 	}
// 	else if (*(*p)++ == '\"')
// 	{
// 		put(s, '\"');
// 		while (!(type = step(p, 2)) || **p != '\"')
// 		{
// 			put(s, *(*p)++);
// 			// if (!type && *(*p - 1) == '$')
// 				// put(s, ' ');
// 		}
// 		put(s, '\"');
// 		++*p;
// 	}
// }
// //	echo hi 1> file
// static void	redirect_handler(char **s, char **p, t_main *main)
// {
// //	if (**)
// //	{
// 	put(s, *(*p)++);
// 	if (**p == '>')
// 		put(s, *(*p)++);
// 	while (**p == ' ')
// 		++*p;
// 	while (!(**p == '|' || **p == ';' || **p == ' '
// 			 || **p == '<' || **p == '>' || **p == '\0'))
// 	{
// 		while (!step(p, 0))
// 			put(s, *(*p)++);
// 		if (**p == '\'' || **p == '\"')
// 			quote_handler(s, p);
// 	}
// 	push(&((main)->cmd->red), s);
// //	}
// }

// static int		terminate_handler(char **s, char **p, t_main *main)
// {
// 	int		a;

// 	a = 0;
// 	if (*s)
// 	{
// 		push(&((main)->cmd->cmd), s);
// 		// main->cmd->cmd = ft_stradd(main->cmd->cmd, *s);
// 		*s = NULL;
// 	}
// 	if (**p != ' ')
// 	{
// 		if (**p == '|')
// 			main->cmd->pipe = 1;
// 		if (**p == '\0')
// 			return (0);
// 	}
// 	else
// 	{
// 		++*p;
// 		return (1);
// 	}
// 	++*p;
// 	return (0);
// }

// int		parser(t_main *main, char *line)
// {
// 	char	*s;
// 	char	*p;
// 	int		type;

// 	free(main->cmd);
// 	main->cmd = malloc(sizeof(t_cmd));
// 	main->cmd->cmd = malloc(sizeof(char*));
// 	main->cmd->cmd[0] = NULL;
// 	// if (p == NULL)
// 	p = line;
// 	s = NULL;
// 	// while (*line)
// 	// {
// 	// 	put(&s, *line);
// 	// 	line++;
// 	// }
// 	// push(&main->cmd->cmd, &s);
// 	while (1)
// 	{
// 		type = step(&p, 0);
// 		printf("=%d\n", type);
// 		if (type)
// 		{
// 			if (*p == '<' || *p == '>')
// 			{
// 				redirect_handler(&s, &p, main);
// 			}
// 			else if (*p == '\'' || *p == '\"')
// 			{
// 				quote_handler(&s, &p);
// 			}
// 			else if (!terminate_handler(&s, &p, main))
// 				break;
// 		}
// 		else
// 		{
// 			put(&s, *p);
// 			p++;
// 		}
// 	}
// 	return (0);
// }

int 		parser(t_cmd **cmd, char *line)
{
	static char	*p;
	int			i;

	if (p == NULL)
		p = line;
	else
		p = NULL;
	if (p)
	{
		i = 1;
		*cmd = malloc(sizeof(t_cmd));
		ft_bzero(*cmd, sizeof(t_cmd));
		(*cmd)->cmd = ft_split(line, ' ');
	}
	else
		i = 0;
	return (i);
}