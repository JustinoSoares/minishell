/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:32:15 by jsoares           #+#    #+#             */
/*   Updated: 2024/11/13 09:50:15 by jsoares          ###   ########.fr       */
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
    int prev_fd = -1;
    char **args;
    char **get_args;
    int quant, i;

    if (ac != 2)
    {
        printf("Error: invalid number of arguments\n");
        return 1;
    }
    args = ft_split(av[1], '|');
    quant = count_pipes(av[1]) + 1;

    for (i = 0; i < quant; i++)
    {
        if (pipe(fd) == -1)
        {
            perror("pipe");
            exit(EXIT_FAILURE);
        }

        if (fork() == 0)
        {
            // Para o primeiro comando
            if (i == 0)
                dup2(fd[1], STDOUT_FILENO);
            // Para comandos intermediários
            else if (i < quant - 1)
            {
                dup2(prev_fd, STDIN_FILENO);
                dup2(fd[1], STDOUT_FILENO);
            }
            // Para o último comando
            else
                dup2(prev_fd, STDIN_FILENO);
            // Fechar todos os descritores de pipe
            close(fd[0]);
            close(fd[1]);
            if (prev_fd != -1)
                close(prev_fd);

            // Executa o comando atual
            get_args = ft_split(args[i], ' ');
            execve(get_args[0], get_args, NULL);
            perror("execve");
            exit(EXIT_FAILURE);
        }
        // Fechar o descritor antigo e atualizar `prev_fd`
        if (prev_fd != -1)
            close(prev_fd);
        close(fd[1]);
        prev_fd = fd[0];
    }

    // Espera todos os processos filhos
    for (i = 0; i < quant; i++)
        wait(NULL);

    // Libera a memória alocada para `args`
    for (i = 0; i < quant; i++)
        free(args[i]);
    free(args);

    return 0;
}
