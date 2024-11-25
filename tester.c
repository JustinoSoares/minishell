/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquilami <rquilami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:37:07 by jsoares           #+#    #+#             */
/*   Updated: 2024/11/25 18:38:27 by rquilami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"


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

int main(void)
{
    redir_out("test", execute_command("pwd"));
	return (0);
}
