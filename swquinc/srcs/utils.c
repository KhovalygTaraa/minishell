/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 16:23:49 by swquinc           #+#    #+#             */
/*   Updated: 2021/01/26 18:51:04 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



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