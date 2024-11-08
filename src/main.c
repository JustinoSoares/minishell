/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:59:09 by jsoares           #+#    #+#             */
/*   Updated: 2024/11/08 15:56:53 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../libft/libft.h"

int index_of(char *str, char *word)
{
    int i;
    i = 0;
    while (str[i])
    {
        if (ft_strncmp(str + i, word, ft_strlen(word)) == 0)
            return (i + ft_strlen(word) - 1);
        i++;
    }
    return (-1);
}

int start_write(char *str, char *command)
{
    int start;
    start = index_of(str, command) + 1;
    while (*(str + start) == ' ')
        start++;
    return (start);
}

void ctrl_c(int sig)
{
    (void)sig;
    write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}


void ft_get_terminal(char **envp)
{
    char *line;
    char **args;
    char **env;

    env = envp;
    signal(SIGINT, ctrl_c);  // quando o usuário aperta ctrl+c
    signal(SIGQUIT, ctrl_c); // quando o usuário aperta ctrl+
    while (true)
    {
        line = readline("\033[1;32mroot@minishell\033[m:~$ ");
        if (!line || strcmp(line, "exit") == 0)
            break;
        args = ft_split(line, ' ');
        if (args[0] && strcmp(args[0], "echo") == 0)
            ft_echo(line + start_write(line, "echo"));
        add_history(line);
        write_history("history");
        free(line);
    }
}

int main(int argc, char **argv, char **envp)
{
    ft_get_terminal(envp);
    return (0);
}