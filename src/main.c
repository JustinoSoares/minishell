/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:59:09 by jsoares           #+#    #+#             */
/*   Updated: 2025/01/08 10:43:11 by jsoares          ###   ########.fr       */
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
    int i = 0;
    int j = 0;

    while (envp[i] != NULL)
        i++;
    ev->len = i;
    ev->env = malloc((i + 1) * sizeof(char *));
    if (!ev->env)
        return;
    while (j < i)
    {
        ev->env[j] = ft_strdup(envp[j]);
        if (!ev->env[j])
        {
            while (j > 0)
            {
                free(ev->env[--j]);
            }
            free(ev->env);
            return;
        }
        j++;
    }
    ev->env[i] = NULL; // Null-terminate the array
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

void free_error(char *read, t_words *words, t_variables *vars)
{
    free_words(words);
    free(vars->line);
    free(read);
    return;
}

char **free_args(t_variables *vars)
{
    if (vars->args)
        free_matriz(vars->args);
    return (NULL);
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
        if (aspas_error(read, true) || read[0] == '\0' || is_string_space(read) == 1)
            continue;
        vars->line = filter_string(read, vars, &words);
        if (!vars->line)
            free_error(read, words, vars);
        vars->args = ft_split(vars->line, ' ');
        if (!vars->args)
            free_error(read, words, vars);
        function_pipe(vars, &words);
        vars->args = free_args(vars);
        free_error(read, words, vars);
        words = NULL;
    }
}

void free_env(t_env *ev)
{
    int i;

    i = 0;
    if (!ev)
        return;
    while (i < ev->len)
    {
        free(ev->env[i]);
        i++;
    }
    free(ev->env);
    free(ev);
}

void init_ev(t_env *ev)
{
    ev->value = NULL;
    ev->key = NULL;
    ev->env = NULL;
    ev->env_copy = NULL;
    ev->len = 0;
    ev->found = 0;
    ev->just_var = 0;
    ev->i = 0;
    ev->j = 0;
}

void init_variables(t_variables *vars)
{
    vars->status_command = 0;
    vars->prev_fd = 0;
    vars->fd = 0;
    vars->files_out[0] = NULL;
    vars->files_in[0] = NULL;
    vars->cmd_args[0] = NULL;
    vars->index = 0;
    vars->redir_found = 0;
    vars->quant = 0;
    vars->count_out = 0;
    vars->count_in = 0;
    vars->redir_here_doc_found = 0;
    vars->redir_greater_found = 0;
    vars->redir_lesser_found = 0;
    vars->saved_std = 0;
    vars->line = NULL;
    vars->type_redir = NULL;
    vars->last_redir_type = NULL;
    vars->args = NULL;
    vars->env = NULL;
    vars->pid = 0;
    vars->ext = malloc(sizeof(t_extented));
    vars->ev = malloc(sizeof(t_env));
    vars->words = NULL;
    vars->next = NULL;
}

int main(int argc, char **argv, char **envp)
{
    t_variables vars;
    init_variables(&vars);
    init_ev(vars.ev);
    fill_env(vars.ev, envp);
    ft_get_terminal(envp, &vars);
    free_env(vars.ev);
    free_matriz(vars.env);
    return (0);
}
