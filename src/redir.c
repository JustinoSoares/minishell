/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquilami <rquilami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 08:34:50 by rquilami          #+#    #+#             */
/*   Updated: 2024/11/25 18:44:32 by rquilami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char* execute_command(const char *command, t_variables *vars)
{
    int pipefd[2]; // Pipe para comunicação entre o processo pai e o filho
    pid_t pid;
    char *output = malloc(MAX_BUFFER);
    if (output == NULL)
    {
        perror("malloc");
        exit(1);
    }
    // Cria o pipe
    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        exit(1);
    }
    // Cria o processo filho
    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(1);
    }
    if (pid == 0)
    {  // Processo filho
        // Fecha a extremidade de leitura do pipe, pois o filho vai escrever nele
        close(pipefd[0]);

        // Redireciona a saída padrão (stdout) para o pipe
        dup2(pipefd[1], STDOUT_FILENO);

        close(pipefd[1]);

        // Executa o comando
		execve(getenv("PATH"), command, vars->env);
        command = find_executable(vars->args[0]);
        if (command != NULL)
        {
            
        }
        else
        {
            perror("Comando não encontrado");
            free_matriz(vars->args);
            exit(1);
        }
        perror("execlp");
        exit(1);
    }
    else
    {  // Processo pai
        // Fecha a extremidade de escrita do pipe, pois o pai vai ler dela
        close(pipefd[1]);

        int bytesRead = read(pipefd[0], output, MAX_BUFFER - 1);
        if (bytesRead == -1)
        {
            perror("read");
            exit(1);
        }
        output[bytesRead] = '\0';
        close(pipefd[0]);
        wait(NULL);
    }

    return output;
}


int redir_out(const char *file, char *str)
{
    int fd;

    fd = 0;
    fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        perror("Erro ao abrir o arquivo para redirecionar a saída");
        return -1;
    }
    if (dup2(fd, STDOUT_FILENO) == -1)
    {
        perror("Erro ao redirecionar stdout");
        close(fd);
        return -1;
    }
	printf("%s\n",str);
    close(fd);
    return 0;
}

/*int redir_in(const char *file)
{
    int fd;

    fd = 0;
    fd = open(file, O_RDONLY);
    if (fd == -1)
    {
        perror("Erro ao abrir o arquivo para redirecionar a entrada");
        return -1;
    }
    if (dup2(fd, STDIN_FILENO) == -1)
    {
        perror("Erro ao redirecionar stdin");
        close(fd);
        return -1;
    }
    close(fd);
    return 0;
}*/




void    redir_main(char *line)
{
    int i;
    redir_out("test", execute_command("ls"));
}

