/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:34:08 by jsoares           #+#    #+#             */
/*   Updated: 2024/11/14 16:45:34 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void function_no_built(t_variables vars)
{
    vars.pid = fork();
    if (vars.pid == 0)
    {
        execve(ft_strjoin("/bin/", vars.args[0]), vars.args, NULL);
        perror("Error");
        exit(1);
    }
    else if (vars.pid > 0)
        waitpid(vars.pid, &vars.status_command, 0);
    else
        perror("Error");
}
char *remove_aspas(char *str)
{
    int i = 0;
    int j = 0;
    char *new = malloc(sizeof(char) * strlen(str) + 1);
    if (str[i] == '"' && str[i])
    {
        while (str[i] && str[++i] != '"')
            new[j++] = str[i];
    }
    else if (str[i] == '\'' && str[i])
    {
        while (str[i] && str[++i] != '\'')
            new[j++] = str[i];
    }
    else
        return (str);
    new[j] = '\0';
    return (new);
}

int ft_strcmp(char *s1, char *s2)
{
    int i = 0;
    if (!s1 || !s2)
        return (-1);
    if (aspas_error(s1))
        return (-1);
    while (s1[i] && s2[i] && s1[i] == s2[i])
    {
    }
    printf("s1: %s\n", s1);
    return (s1[i] - s2[i]);
}

void ft_exec_functions(t_variables vars)
{
    if (vars.args[0] && ft_strcmp(vars.args[0], "echo") == 0)
    {
        ft_echo(vars);
        if (new_line(vars.args[1]) == 0)
            printf("\n");
    }
    else
        function_no_built(vars);
}

void function_pipe(t_variables vars)
{
    int fd[2];
    char **args;
    char **get_args;

    args = ft_split(vars.line, '|');
    vars.quant = count_pipes(vars.line) + 1;
    vars.prev_fd = -1;
    vars.index = -1;
    while (++vars.index < vars.quant)
    {
        if (pipe(fd) == -1)
        {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
        vars.args = ft_split(args[vars.index], ' ');
        vars.pid = fork();
        if (vars.pid == 0)
        {
            if (vars.prev_fd != -1)
            {
                dup2(vars.prev_fd, 0);
                close(vars.prev_fd);
            }
            if (vars.index < vars.quant - 1)
                dup2(fd[1], 1);
            close(fd[0]);
            ft_exec_functions(vars);
            exit(0);
        }
        else if (vars.pid > 0)
        {
            waitpid(vars.pid, &vars.status_command, 0);
            close(fd[1]);
            vars.prev_fd = fd[0];
        }
        else
            perror("Error");
    }
    free_matriz(args);
}
