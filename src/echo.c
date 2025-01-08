/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:38:25 by jsoares           #+#    #+#             */
/*   Updated: 2025/01/08 08:53:38 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int get_last_in(char *str, char c, int index)
{
    int i = 0;
    int last = 0;
    int back = index;
    while (i < index)
    {
        if (str[i] == c)
            last = i;
        i++;
    }
    back = count_until(str, c, back);
    if (back % 2 != 0)
        return (last);
    return (-1);
}

char *str_delimited(char *str)
{
    int i = 0;
    int j = 0;
    int len = 0;
    while (str[i])
    {
        if (str[i] == '|' && is_in_aspas(str, i) == 1)
            len = i;
        i++;
    }
    char *new = malloc(sizeof(char) * len);
    i = 0;
    while (i < len)
    {
        new[i] = str[i];
        i++;
    }
    new[i] = '\0';
    return (new);
}

void ft_echo(t_variables *vars)
{
    int i = 0;
    int get = 0;
    char *str;

    str = vars->line + (start_write(vars->line, vars->args[0]) + new_line(vars->args[1]));
    if (aspas_error(str, true))
        return;
    while (str[i] && str[i] != '|')
    {
        printf("%c", str[i]);
        i++;
    }
}
