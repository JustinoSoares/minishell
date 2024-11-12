/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:32:15 by jsoares           #+#    #+#             */
/*   Updated: 2024/11/12 16:01:45 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

int count_pipes(char *str)
{
    while (*str)
    {
        if (*str == '|')
            return (1);
        str++;
    }
    return (0);
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
            execlp("ls", "ls", NULL);
            perror("execlp");
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
            execlp("grep", "grep", ".c", NULL);
            perror("execlp");
            exit(EXIT_FAILURE);
        }
        i++;
    }
}