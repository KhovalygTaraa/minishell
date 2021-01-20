/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 12:59:25 by swquinc           #+#    #+#             */
/*   Updated: 2021/01/20 16:39:49 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int     main(int argc, char **argv, char **env)
{
    int     status;
    char    *line;

    status = 1;
    (void)argc;
    (void)argv;
    (void)env;
    while (status)
    {
        ft_putstr_fd("sh> ", 1);
        get_next_line(1, &line);
        parser(line);
        free(line);
    }
    // while (env[i])
    // {
    //     pwd = ft_strnstr(env[i], "PWD", 3);
    //     if (pwd != NULL)
    //         printf("%s\n", pwd + 4);
    //     i++;
    // }
    return (0);
}