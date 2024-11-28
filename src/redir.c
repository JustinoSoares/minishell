/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquilami <rquilami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 08:34:50 by rquilami          #+#    #+#             */
/*   Updated: 2024/11/28 09:18:12 by rquilami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char    *find_comand(char *line)
{
    int i;
    int j;
    int saved_stdout;
    char *command;

    i = 0;
    j = 0;
    if (line == NULL || *line == '\0')
        return NULL;
    while (line[i] != '>' && line[i] != '\0')
        i++;
    if (line[i] == '\0')
        return NULL;
    command = malloc(sizeof(char) * (i + 1));
    if (command == NULL)
    {
        perror("Erro ao alocar memória para o comando");
        return (NULL);
    }
    while (j < i)
    {
        command[j] = line[j];
        j++;
    }
    command[i] = '\0';
    return (command);
}


int redir_out(t_variables *vars, const char *file, char *command)
{
    int fd;
    int saved_stdout;
    pid_t   pid;

    fd = 0;
    if (file == NULL || command == NULL)
    {
        perror(" ");
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
        command = vars->args[0];
        if (ft_strchr(vars->args[0], '/') == NULL)
        {
            command = find_executable(vars->args[0]);
            if (command == NULL)
            {
                perror("Comando não encontrado");
                free_matriz(vars->args);
                exit(1);
            }
        }
        execve(command, vars->args, vars->ev->env);
        perror("\033[31mError\033[m");
        exit(1);
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
    while (line[i] != '\0')
    {
        file[j++] = line[i];
        i++;
    }
    file[j] = '\0';
    redir_out(vars, file, find_comand(line));
    free(file);
}

