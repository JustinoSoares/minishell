/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:34:08 by jsoares           #+#    #+#             */
/*   Updated: 2024/12/08 13:03:34 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void new_prompt(int signal)
{
    if (signal == SIGINT)
        write(1, "\n", 1);
    else if (signal == SIGQUIT)
        write(1, "Sair\n", 5);
}

void function_no_built(t_variables vars)
{
    char *command_path;
    int g_exit_status;
    command_path = vars.args[0];
    vars.pid = fork();
    if (vars.pid == 0)
    {
        if (ft_strchr(vars.args[0], '/') == NULL)
        {
            command_path = find_executable(vars.args[0]);
            printf("Comando: %s\n", command_path);
            if (command_path == NULL)
            {
                perror("Comando não encontrado");
                vars.status_command = 2;
                free_matriz(vars.args);
                exit(127);
            }
        }
        execve(command_path, vars.args, NULL);
        perror("\033[31mError\033[m");
        exit(1);
    }
    else if (vars.pid > 0)
    {
        signal(SIGINT, new_prompt);
        signal(SIGQUIT, new_prompt);
        waitpid(vars.pid, &vars.status_command, 0);
        if (WIFEXITED(vars.status_command))
        {
            vars.status_command = WEXITSTATUS(vars.status_command); // Captura o código de saída
            printf("Código de saída: %d\n", vars.status_command);
        }
        vars.status_command = 1;
        if (WIFSIGNALED(vars.status_command))
        {
            vars.status_command = 128 + WTERMSIG(vars.status_command); // Sinal que terminou o processo
            printf("Código de saída: %d\n", vars.status_command);
        }
    }
    else
    {
        vars.status_command = 1;
        perror("Error");
    }
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
    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    return (s1[i] - s2[i]);
}

void ft_exec_functions(t_variables vars)
{
    if (vars.args[0] && ft_strcmp(vars.args[0], "echo") == 0)
    {
        if (vars.args[1])
        {
            ft_echo(vars);
            if (new_line(vars.args[1]) == 0)
                printf("\n");
        }
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
