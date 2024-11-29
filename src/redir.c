/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquilami <rquilami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 08:34:50 by rquilami          #+#    #+#             */
/*   Updated: 2024/11/29 13:26:49 by rquilami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char    *find_comand(char *line)
{
    int i;
    int j;
    char *command;

    i = 0;
    j = 0;
    if (line == NULL || *line == '\0')
        return NULL;
    while (line[i] != '>' && line[i] != '\0')
        i++;
    if (line[i] == '\0')
        return NULL;
    command = malloc(sizeof(char) * i);
    if (command == NULL)
    {
        perror("Erro ao alocar memória para o comando");
        return (NULL);
    }
    while (j < i - 1)
    {
        command[j] = line[j];
        j++;
    }
    command[j] = '\0';
    return (find_executable(command));
}


int redir_out(t_variables *vars, const char *file, char *command)
{
    int fd;
    int saved_stdout;
    pid_t   pid;

    fd = 0;
    if (file == NULL || strlen(file) == 0)
    {
        printf("bash: syntax error near unexpected token `newline\'\n");
        return (-1);
    }
    saved_stdout = dup(STDOUT_FILENO);
    if (saved_stdout == -1) {
        perror("Erro ao salvar o stdout");
        close(fd);
        return -1;
    }
    fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        perror("Erro ao abrir o arquivo para redirecionar a saída");
        return (-1);
    }
    if (dup2(fd, STDOUT_FILENO) == -1)
    {
        perror("Erro ao redirecionar stdout");
        close(fd);
        return (-1);
    }
    pid = fork();
    if (pid == 0)
    {
        execve(command, vars->args, NULL);
    }
    if (pid > 0)
    {
        if (dup2(saved_stdout, STDOUT_FILENO) == -1)
        {
            perror("Erro ao restaurar o stdout original");
            close(fd);
            close(saved_stdout);
            return (-1);
        }
    }
    close(fd);
    close(saved_stdout);
    return (0);
}

void    redir_main(t_variables *vars, char *line)
{
    int i;
    int j;
    char    *file;

    i = 0;
    j = 0;
    while (line[i] != '>')
        i++;
    file = malloc(sizeof(char) * (ft_strlen(line) - i));
    i++;
    if (line[i] != '\0')
    {
        while (line[i] != '\0')
        {
            file[j++] = line[i];
            i++;
        }
        file[j] = '\0';
    }
    redir_out(vars, file, find_comand(line));
    free(file);
}

