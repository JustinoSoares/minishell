/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:37:07 by jsoares           #+#    #+#             */
/*   Updated: 2024/11/11 16:35:04 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int status;
    pid_t pid = fork();

    if (pid == 0) {
        // Processo filho: executa o comando
        execlp("echo", "echo", "/diretorio_nao_existente", NULL);
        exit(1);  // Saia com erro se o comando falhar
    } else if (pid > 0) {
        // Processo pai: espera o comando e pega o status
        wait(&status);
        // Verifica e exibe o status de saída
        if (WIFEXITED(status)) {
            int exit_status = WEXITSTATUS(status);
            printf("Código de saída: %d\n", exit_status);
        }
    } else {
        perror("Erro ao criar processo");
        return 1;
    }

    return 0;
}