/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:34:08 by jsoares           #+#    #+#             */
/*   Updated: 2024/11/22 12:16:07 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void function_no_built(t_variables vars)
{
    char *command_path;
    vars.pid = fork();
    if (vars.pid == 0)
    {
        command_path = vars.args[0];
        if (ft_strchr(vars.args[0], '/') == NULL)
        {
            command_path = find_executable(vars.args[0]);
            if (command_path == NULL)
            {
                perror("Comando não encontrado");
                free_matriz(vars.args);
                exit(1);
            }
        }
        execve(command_path, vars.args, NULL);
        perror("\033[31mError\033[m");
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
    if (aspas_error(s1, false))
        return (-1);
    s1 = remove_aspas(s1);
    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;
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
    else if (vars.args[0] && ft_strcmp(vars.args[0], "env") == 0)
        env(vars.ev, vars);
    else if (vars.args[0] && ft_strcmp(vars.args[0], "cd") == 0)
        ft_cd(vars);
    else if (vars.args[0] && ft_strcmp(vars.args[0], "pwd") == 0)
        ft_pwd(vars);
    else if (vars.args[0] && ft_strcmp(vars.args[0], "exit") == 0)
        ft_exit(vars);
    else if (vars.args[0] && ft_strcmp(vars.args[0], "unset") == 0)
        unset(vars.args[1], vars.ev);
    else if (vars.args[0] && ft_strcmp(vars.args[0], "export") == 0)
        export(vars);
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
                dup2(fd[1], STDOUT_FILENO);
            ft_exec_functions(vars);
            close(fd[0]);
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
