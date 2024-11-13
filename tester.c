/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:37:07 by jsoares           #+#    #+#             */
/*   Updated: 2024/11/12 11:32:10 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int pipefd[2];  // Array para o pipe (pipefd[0] para leitura, pipefd[1] para escrita)
    pid_t pid1, pid2;

    if (pipe(pipefd) == -1) {  // Cria o pipe
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Cria o primeiro processo filho para executar o comando `ls`
    if ((pid1 = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0) {
        // Processo filho 1: executa `ls`
        close(pipefd[0]);           // Fecha o lado de leitura do pipe
        dup2(pipefd[1], STDOUT_FILENO); // Redireciona a saída padrão para o pipe
        close(pipefd[1]);           // Fecha o lado de escrita do pipe (já duplicado)

        execlp("ls", "ls", NULL);    // Executa o comando `ls`
        perror("execlp");           // Se execlp falhar
        exit(EXIT_FAILURE);
    }

    // Cria o segundo processo filho para executar o comando `grep`
    if ((pid2 = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid2 == 0) {
        // Processo filho 2: executa `grep ".c"`
        close(pipefd[1]);           // Fecha o lado de escrita do pipe
        dup2(pipefd[0], STDIN_FILENO);  // Redireciona a entrada padrão para o pipe
        close(pipefd[0]);           // Fecha o lado de leitura do pipe (já duplicado)

        execlp("grep", "grep", ".c", NULL); // Executa o comando `grep ".c"`
        perror("execlp");           // Se execlp falhar
        exit(EXIT_FAILURE);
    }

    // Processo pai: fecha os dois lados do pipe e espera os filhos terminarem
    close(pipefd[0]);
    close(pipefd[1]);

    waitpid(pid1, NULL, 0); // Espera pelo processo `ls`
    waitpid(pid2, NULL, 0); // Espera pelo processo `grep`

    return 0;
}
