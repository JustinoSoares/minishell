/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: justinosoares <justinosoares@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:32:15 by jsoares           #+#    #+#             */
/*   Updated: 2024/11/12 23:07:27 by justinosoar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

int count_pipes(char *str)
{
    int i = 0;
    int count = 0;
    while (str[i])
    {
        if (str[i] == '|')
            count++;
        i++;
    }
    return (count);
}

void only_a(char *str)
{
    int i = 0;
    while (str[i] && str[i] != '|')
    {
        if (str[i] == 'a')
            printf("%c", str[i]);
        i++;
    }
    printf("\n");
}

int main(int ac, char **av)
{
    int fd[2];
    pid_t pid1, pid2;
    char **args;
    int quant = 0, i = 0;
    char **get_args;

    args = ft_split(av[1], '|');
    quant = count_pipes(av[1]);
    while (i < quant)
    {
        if (pipe(fd) == -1)
        {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
        pid1 = fork();
        if (pid1 == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        if (pid1 == 0)
        {
            close(fd[0]);
            dup2(fd[1], STDOUT_FILENO);
            close(fd[1]);
            get_args = ft_split(args[i], ' ');
            execve(get_args[0], get_args, NULL);
            perror("execv");
            exit(EXIT_FAILURE);
        }
        pid2 = fork();
        if (pid2 == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        if (pid2 == 0)
        {
            close(fd[1]);
            dup2(fd[0], STDIN_FILENO);
            close(fd[0]);
            dup2(fd[1], STDOUT_FILENO);
            close(fd[1]);
            get_args = ft_split(args[i + 1], ' ');
            execve(get_args[0], get_args, NULL);
            perror("execve");
            exit(EXIT_FAILURE);
        }
        i++;
    }
    close(fd[0]);
    close(fd[1]);
    wait(NULL);
    wait(NULL);
    return (0);
}