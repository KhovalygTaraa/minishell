/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swquinc <swquinc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 15:20:41 by swquinc           #+#    #+#             */
/*   Updated: 2021/01/20 16:46:12 by swquinc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int  cmd_selector(char *cmd, char *line)
{
    int     i;

    i = 0;
    (void)line;
    if (!ft_strncmp(cmd, "echo", 4))
        i = parse_echo(line);
    else
    {
        ft_putstr_fd("sh: ", 1);
        ft_putstr_fd(cmd, 1);
        ft_putendl_fd(": command now found", 1);
    }
    return (0);
}

// get first argument - command name.
static char    *gfa(char *line)
{
    int     i;
    char    *arg;

    i = 0;
    while (line[i] != ' ' && line[i] != 0)
        i++;
    if (!(arg = malloc(sizeof(char) * i)))
        return (NULL);
    i = 0;
    while (line[i] != ' ' && line[i] != 0)
    {
        arg[i] = line[i];
        i++;
    }
    free(line);
    return (arg);
}

int     parser(char *line)
{
    char    *cmd;
    char    *trimmed_line;

    trimmed_line = ft_strtrim(line, " ");
    cmd = gfa(trimmed_line);
    cmd_selector(cmd, line);
    return (0);
}