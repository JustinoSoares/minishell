/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: justinosoares <justinosoares@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:59:09 by jsoares           #+#    #+#             */
/*   Updated: 2024/11/18 22:41:31 by justinosoar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

void    fill_env(t_env *ev, char **envp)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (envp[i] != NULL)
        i++;
    ev->len = i;
    ev->env = malloc((i + 1) * sizeof(char *));
    if (!ev->env)
        return;
    while (j < i)
    {
        ev->env[j] = strdup(envp[j]);
        j++;
    }
    ev->env[i] = NULL;
}

char *ft_strcat_index(char *str, char *str2, int index)
{
    char *new;
    int i = 0;
    int j = 0;
    int x = 0;
    int len = strlen(str) + strlen(str2);
    new = malloc(sizeof(char) * (strlen(str) + strlen(str2) + 1));
    while (str[i] && i < index)
    {
        new[i] = str[i];
        i++;
    }
    x = i;
    while (str2[j])
    {
        new[i] = str2[j];
        i++;
        j++;
    }
    while (str[x])
    {
        new[i] = str[x];
        i++;
        x++;
    }
    return (new);
}

char *last_word(char *str, char limited)
{
    int i = 0;
    char **word;

    word = ft_split(str, limited);
    if (!word)
        return (NULL);
    while (word[i])
        i++;
    return (word[i - 1]);
}

void ft_get_terminal(char **envp)
{
    
    t_variables vars;
    char *line;
    vars.status_command = 0;
    vars.env = envp;
    signal(SIGINT, ctrl_c);  // quando o usuário aperta ctrl+c
    signal(SIGQUIT, ctrl_c); // quando o usuário aperta ctrl+d
    while (true)
    {
        line = ft_strcat_index("\033[1;32mroot@minishell\033[m:~/ $ ",
            last_word(getcwd(NULL, 0), '/'), 27);
        vars.line = readline(line);
        vars.args = ft_split(vars.line, ' ');
        if (!vars.line || strcmp(vars.args[0], "exit") == 0)
            return (free(vars.line));
        vars.ev = malloc(sizeof(t_env));
        fill_env(vars.ev, envp);
        ft_exec_functions(vars);
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