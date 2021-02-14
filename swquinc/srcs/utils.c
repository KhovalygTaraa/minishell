/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 16:23:49 by swquinc           #+#    #+#             */
/*   Updated: 2021/02/13 15:39:47 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_2array(char **array)
{
	int		i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int		ft_strchr_index(const char *s, int c)
{
	size_t	i;
	size_t	size;
	char	*ptr;

	ptr = (char*)s;
	size = ft_strlen(s);
	i = 0;
	while (i < size + 1)
	{
		if (ptr[i] == (char)c)
			return (i);
		i++;
	}
	return (INT_MAX);
}

/*
** This function add string to two-dimensional array of strings.
*/

char	**ft_stradd(char **array, char *str)
{
	int		i;
	char	**new;

	if (str == NULL)
		return (NULL);
	i = 0;
	while (array[i] != NULL)
		i++;
	if (!(new = malloc(sizeof(char*) * (i + 2))))
		return (NULL);
	i = 0;
	if (array[0] != NULL)
	{
		while (array[i] != NULL)
		{
			new[i] = array[i];
			i++;
		}
	}
	// if (!(new[i] = ft_strdup(str)))
	// 	return (NULL);
	new[i] = str;
	new[i + 1] = NULL;
	free(array);
	return (new);
}

/*
** This function duplicate two-dimensional array of strings
*/

char	**ft_2arraydup(char **array)
{
	int		i;
	char	**new;

	i = 0;
	if (!array)
		return (NULL);
	while (array[i] != NULL)
		i++;
	if (!(new = malloc(sizeof(char*) * (i + 1))))
		return (NULL);
	i = 0;
	while (array[i] != NULL)
	{
		new[i] = ft_strdup(array[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}

void	ft_perror(const char *str)
{
	char	*s1;
	size_t	i;

	s1 = strerror(errno);
	if (s1 == NULL)
		return ;
	write(2, "minishell: ", 11);
	if (str != NULL && (i = ft_strlen(str)) != 0)
	{
		write(2, str, i);
		write(2, ": ", 2);
	}
	i = ft_strlen(s1);
	write(2, s1, i);
	write(2, "\n", 1);
}
