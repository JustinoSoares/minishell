/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 12:55:18 by jsoares           #+#    #+#             */
/*   Updated: 2024/12/15 14:16:06 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

// Função para separar o comando e os redirecionamentos
void parse_command(char *input, char **args, char **file, char *operator) {
    char *redir_pos;

    // Checa o tipo de redirecionamento
    if ((redir_pos = strstr(input, ">>"))) {
        *operator = 'a'; // Append
        *redir_pos = '\0';
        *file = redir_pos + 2;
    } else if ((redir_pos = strstr(input, ">"))) {
        *operator = 'w'; // Write
        *redir_pos = '\0';
        *file = redir_pos + 1;
    } else if ((redir_pos = strstr(input, "<"))) {
        *operator = 'r'; // Read
        *redir_pos = '\0';
        *file = redir_pos + 1;
    } else if ((redir_pos = strstr(input, "<<"))) {
        *operator = 'h'; // Here-document
        *redir_pos = '\0';
        *file = redir_pos + 2;
    } else {
        *operator = '\0';
    }

    // Remove espaços ao redor do arquivo
    if (*file) 
        *file = strtok(*file, " \t\n");
    // Divide o comando principal em argumentos
    char *token = strtok(input, " \t\n");
    int i = 0;
    while (token) {
        args[i++] = token;
        token = strtok(NULL, " \t\n");
    }
    args[i] = NULL; // Finaliza o array de argumentos
}

// Função para redirecionar entrada ou saída
int handle_redirection(char operator, char *file) {
    int fd = -1;

    switch (operator) {
    case 'w': // >
        fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
        break;
    case 'a': // >>
        fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
        break;
    case 'r': // <
        fd = open(file, O_RDONLY);
        break;
    case 'h': { // <<
        int pipe_fd[2];
        char *line;

        if (pipe(pipe_fd) == -1) {
            perror("pipe");
            return -1;
        }
        while ((line = readline("> ")) && strcmp(line, file) != 0) {
            write(pipe_fd[1], line, strlen(line));
            write(pipe_fd[1], "\n", 1);
            free(line);
        }
        free(line);
        close(pipe_fd[1]);
        return pipe_fd[0];
    }
    default:
        return -1;
    }
    if (fd < 0)
        perror("open");
    return fd;
}

int main() {
    char *input, *file = NULL, *args[1024];
    char operator;
    pid_t pid;

    while (1) {
        input = readline("minishell> ");
        if (!input) break; // Ctrl+D para sair

        if (strlen(input) == 0) {
            free(input);
            continue;
        }
        add_history(input); // Adiciona o comando à história
        parse_command(input, args, &file, &operator);
        if (!args[0]) {
            free(input);
            continue;
        }
        pid = fork();
        if (pid == 0) { // Processo filho
            int fd;
            // Configura o redirecionamento se necessário
            if (operator != '\0') {
                fd = handle_redirection(operator, file);
                if (fd < 0) 
                    exit(EXIT_FAILURE);
                if (operator == 'r' || operator == 'h') {
                    dup2(fd, STDIN_FILENO); // Redireciona entrada
                } else {
                    dup2(fd, STDOUT_FILENO); // Redireciona saída
                }
                close(fd);
            }
            // Executa o comando usando execve
            char *envp[] = { NULL }; // Variáveis de ambiente vazias
            if (execve(args[0], args, envp) == -1) {
                perror("execve");
                exit(EXIT_FAILURE);
            }
        } else if (pid > 0) { // Processo pai
            wait(NULL);
        } else {
            perror("fork");
        }

        free(input);
    }

    return 0;
}