/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquilami <rquilami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 08:34:50 by rquilami          #+#    #+#             */
/*   Updated: 2024/11/26 14:23:46 by rquilami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char    *find_comand(char *line)
{
    int i;
    char *new;

    i = 0;
    while (line[i] != '>' && line[i] != '\0')
        i++;
    new = malloc(sizeof(char) * (i + 1));
    i = 0;
    while (line[i] != '>')
    {
        new[i] = line[i];
        i++;
    }
    new[i] = '\0';
    return (new);
}
int redir_out(const char *file, char *command)
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
	printf("%s\n",command);
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
    redir_out(file, find_comand(line));
    free(file);
}

