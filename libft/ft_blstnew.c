/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_blstnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 23:24:22 by swquinc           #+#    #+#             */
/*   Updated: 2020/11/01 00:00:17 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bilist	*ft_blstnew(void *content)
{
	t_bilist	*new;

	if (!(new = (t_bilist*)malloc(sizeof(t_bilist))))
		return (NULL);
	new->content = content;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}
