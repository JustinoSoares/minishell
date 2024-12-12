/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:59:09 by jsoares           #+#    #+#             */
/*   Updated: 2024/12/12 17:08:51 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int status_signal = 0;

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

void fill_env(t_env *ev, char **envp)
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

int is_valid_macro_char(char str)
{
    while (str != 32 && str != '$' && str != '"' && str != '\'' && str != '\0' && str != '$')
        return (1);
    return (0);
}

void ctrl_c(int sig)
{
    write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
    status_signal = sig;
}
int is_string_space(char *str)
{
    int i = 0;
    while (str[i])
    {
        if (str[i] != ' ' && str[i] != '\t')
            return (0);
        i++;
    }
    return (1);
}

char *ft_input(char *read)
{
    signal(SIGINT, ctrl_c);
    signal(SIGQUIT, SIG_IGN);
    read = readline("Minishell: ");
    if (!read)
    {
        free(read);
        printf("exit\n");
        exit(0);
    }
    add_history(read);
    return (read);
}

void ft_get_terminal(char **envp, t_variables *vars)
{
    char *line;
    char *read;
    t_words *words;

    words = NULL;
    vars->status_command = 0;
    vars->env = envp;
    while (true)
    {
        read = ft_input(read);
        if (aspas_error(read, true) || read[0] == '\0'
                || is_string_space(read) == 1)
            continue;
        vars->line = filter_string(read, vars, &words);
        while (words)
        {
            printf("word: %s\n", words->word);
            words = words->next;
        }
        printf("line: %s\n", vars->line);
        if (!vars->line)
            return (free(vars->line));
        vars->args = ft_split(vars->line, ' ');
        if (!vars->args)
            return (free(vars->args));
        function_pipe(vars, &words);
        words = NULL;
        write_history("history");
        free(vars->line);
        free(read);
    }
}

int main(int argc, char **argv, char **envp)
{
    t_variables vars;
    vars.ev = malloc(sizeof(t_env));
    fill_env(vars.ev, envp);
    ft_get_terminal(envp, &vars);
    return (0);
}