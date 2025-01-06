/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 07:18:26 by jsoares           #+#    #+#             */
/*   Updated: 2024/12/10 07:52:36 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>

int main(void)
{
    int fd;
    char **args = malloc(sizeof(char *) * 3);
    args[0] = strdup("/bin/cat");
    args[1] = strdup("log.txt");
    args[2] = NULL;
    fd = open("log.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("open");
        return (1);
    }
    if (dup2(fd, STDIN_FILENO) == -1)
    {
        perror("dup2");
        return (1);
    }
    close(fd);
    execve(args[0], args, NULL);
}