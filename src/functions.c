/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:34:08 by jsoares           #+#    #+#             */
/*   Updated: 2024/11/12 13:54:03 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void ft_exec_functions(t_variables vars)
{
        if (vars.args[0] && strcmp(vars.args[0], "echo") == 0)
        {
            ft_echo(vars);
            if (new_line(vars.args[1]) == 0)
                printf("\n");
        }
        else
        {
            vars.pid = fork();
            if (vars.pid == 0)
            {
                execve(vars.args[0], vars.args, NULL);
                perror("Error");
                exit(1);
            }
            else if (vars.pid > 0)
            {
                waitpid(vars.pid, &vars.status_command, 0);
                if (WIFEXITED(vars.status_command))
                    printf("Exit status: %d\n", WEXITSTATUS(vars.status_command));
            }
            else
            {
                perror("Error");
            }
        }
}
