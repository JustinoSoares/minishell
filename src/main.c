/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:59:09 by jsoares           #+#    #+#             */
/*   Updated: 2024/11/11 17:38:45 by jsoares          ###   ########.fr       */
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
    int start = 0;
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

int new_line(char *str)
{
    int i = 1;
    while (str[i])
    {
        if (str[i] != 'n')
            return (0);
        i++;
    }
    if (str[0] == '-')
        return (i + 1);
    return (0);
}

void ft_get_terminal(char **envp)
{
    
    t_variables vars;
    vars.status_command = 0;
    vars.env = envp;
    signal(SIGINT, ctrl_c);  // quando o usuário aperta ctrl+c
    signal(SIGQUIT, ctrl_c); // quando o usuário aperta ctrl+
    while (true)
    {
        vars.line = readline("\033[1;32mroot@minishell\033[m:~$ ");
        vars.args = ft_split(vars.line, ' ');
        if (!vars.line || strcmp(vars.args[0], "exit") == 0)
            return (free(vars.line));
        if (vars.args[0] && strcmp(vars.args[0], "echo") == 0)
        {
            ft_echo(vars);
            if (new_line(vars.args[1]) == 0)
                printf("\n");
        }
        else
        {
            vars.pid = fork();
            if (vars.pid == 0)
            {
                execve(vars.args[0], vars.args, NULL);
                perror("Error");
                exit(1);
            }
            else if (vars.pid > 0)
            {
                waitpid(vars.pid, &vars.status_command, 0);
                if (WIFEXITED(vars.status_command))
                    printf("Exit status: %d\n", WEXITSTATUS(vars.status_command));
            }
            else
            {
                perror("Error");
            }
        }
        add_history(vars.line);
        write_history("history");
        free(vars.line);
    }
}

int main(int argc, char **argv, char **envp)
{
    ft_get_terminal(envp);
    return (0);
}