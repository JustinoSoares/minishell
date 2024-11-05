/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:59:09 by jsoares           #+#    #+#             */
/*   Updated: 2024/11/05 16:46:33 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void ft_get_terminal(void)
{
    char *line;
    while (true)
    {
        line = readline("\033[1;32mroot@minishell\033[m:~$ ");
        if (line && *line)
        {
            add_history(line);
            //printf("%d\n", ft_strlen(line));
        }
        free(line);
    }
}

int main(int argc, char **argv, char **envp)
{
    ft_get_terminal();
    return (0);
}