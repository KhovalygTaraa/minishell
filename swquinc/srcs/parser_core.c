/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_core.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 19:44:05 by swquinc           #+#    #+#             */
/*   Updated: 2021/02/14 19:44:07 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put(char **s, char c)
{
	static size_t	i;
	size_t			j;
	char			*copy;

	if (!c)
		return ;
	if (!*s)
	{
		i = 0;
		if (!(*s = (char *)malloc(1)))
			return ;
		**s = '\0';
	}
	if (!(copy = (char *)malloc(i + 2)))
		return ;
	copy[i + 1] = '\0';
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

void	push(char ***cmd, char **s)
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
	j = -1;
	while (++j < i)
		copy[j] = (*cmd)[j];
	copy[i++] = *s;
	copy[i] = 0;
	*s = 0;
	free(*cmd);
	*cmd = copy;
}

int		terminate_handler(char **s, char **p, t_cmd **cmd)
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
