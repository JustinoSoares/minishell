/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:39:22 by jsoares           #+#    #+#             */
/*   Updated: 2024/12/12 13:00:56 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int aspas_error(char *str, int show_error)
{
    int i = 0;
    int duplas = 0;
    int simples = 0;
    int mutex = 0;
    while (str[i])
    {
        if (is_in_aspas(str, i) == 1)
        {
            if (str[i] == '"')
            {
                duplas++;
                if (mutex == 0)
                    mutex = 1;
                else
                    mutex = 0;
            }
        }
        if (str[i] == '\'' && mutex == 0)
            simples++;
        i++;
    }
    if (duplas % 2 != 0 || simples % 2 != 0)
        return (write(1, "\033[31mError: error nas aspas\033[m ", 32));
    return (0);
}

int error_pipe(char *str)
{
    int i = 0;
    int mutex = 0;
    int pipes = count_elements(str, '|');
    while (str[i])
    {
        if (str[i] == '|')
        {
            if (mutex == 0)
                mutex = 1;
            else
                return (write(1, "\033[31mError: error no pipe\033[m ", 30));
        }
        i++;
    }
    return (0);
}
