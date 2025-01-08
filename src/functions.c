/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:34:08 by jsoares           #+#    #+#             */
/*   Updated: 2025/01/08 10:52:28 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void new_prompt(int signal)
{
    if (signal == SIGINT)
        write(1, "\n", 1);
    else if (signal == SIGQUIT)
        write(1, "Sair\n", 5);
}

void process_child(char *command_path, t_variables *vars)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    if (ft_strchr(vars->args[0], '/') == NULL)
    {
        command_path = find_executable(vars->args[0]);
        if (command_path == NULL)
        {
            perror("Comando não encontrado");
            vars->status_command = 2;
            free_matriz(vars->args);
            exit(127);
        }
    }
    if (!command_path || access(command_path, X_OK) != 0)
    {
        perror("Comando não encontrado");
        vars->status_command = 127;
        free_matriz(vars->args);
        exit(127);
    }
    execve(command_path, vars->args, vars->ev->env);
    perror("Error");
    exit(1);
}

void process_parent(t_variables *vars)
{
    signal(SIGINT, new_prompt);
    signal(SIGQUIT, new_prompt);
    waitpid(vars->pid, &vars->status_command, 0);
    if (WIFEXITED(vars->status_command))
        vars->status_command = WEXITSTATUS(vars->status_command);
    else if (WIFSIGNALED(vars->status_command))
        vars->status_command = 128 + WTERMSIG(vars->status_command);
}

void function_no_built(t_variables *vars)
{
    char *command_path;

    command_path = vars->args[0];
    vars->pid = fork();
    if (vars->pid == 0)
        process_child(command_path, vars);
    if (vars->pid > 0)
        process_parent(vars);
    else
    {
        vars->status_command = 1;
        perror("Error");
    }
}

char *remove_aspas(char *str)
{
    int i = 0;
    int j = 0;
    char *new = malloc(sizeof(char) * strlen(str) + 1);
    if (str[i] == '"' && str[i])
    {
        while (str[i] && str[++i] != '"')
            new[j++] = str[i];
    }
    else if (str[i] == '\'' && str[i])
    {
        while (str[i] && str[++i] != '\'')
            new[j++] = str[i];
    }
    else
        return (str);
    new[j] = '\0';
    return (new);
}

int ft_strcmp(char *s1, char *s2)
{
    int i = 0;
    if (!s1 || !s2)
        return (-1);
    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    return (s1[i] - s2[i]);
}

void ft_exec_functions(t_variables *vars, t_words **words)
{
    if (vars->args[0] && ft_strcmp(vars->args[0], "echo") == 0)
    {
        if (vars->args[1])
        {
            ft_echo(vars);
            if (new_line(vars->args[1]) == 0)
                printf("\n");
        }
    }
    else if (vars->args[0] && ft_strcmp(vars->args[0], "env") == 0)
        env(vars->ev, vars);
    else if (vars->args[0] && ft_strcmp(vars->args[0], "cd") == 0)
        ft_cd(vars);
    else if (vars->args[0] && ft_strcmp(vars->args[0], "pwd") == 0)
        ft_pwd(vars);
    else if (vars->args[0] && ft_strcmp(vars->args[0], "exit") == 0)
        ft_exit(vars, words);
    else if (vars->args[0] && ft_strcmp(vars->args[0], "unset") == 0)
        unset(vars->args[1], vars->ev);
    else if (vars->args[0] && ft_strcmp(vars->args[0], "export") == 0)
        get_variable(vars->ev, words);
    else
        function_no_built(vars);
}

int count_pipes(t_words *words)
{
    int count = 0;
    while (words)
    {
        if (words->word[0] == '|')
            count++;
        words = words->next;
    }
    return (count);
}
static char *form_word(t_words *word, char *new, char *tmp)
{

    tmp = ft_strjoin(new, word->word);
    if (new)
        free(new);
    new = tmp;
    if (word->next)
    {
        tmp = ft_strjoin(new, " ");
        if (new)
            free(new);
        new = tmp;
    }
    return (new);
}

char **aux_split_pipe(t_words *word, char c, char **line, char *new)
{
    char *tmp;
    int i;

    tmp = NULL;
    i = 0;
    while (word)
    {
        if (word->word[0] == c)
        {
            line[i++] = new;
            new = NULL;
            word = word->next;
            continue;
        }
        new = form_word(word, new, tmp);
        word = word->next;
    }
    line[i++] = new;
    line[i] = NULL;
    return (line);
}

char **split_pipe(t_words **words, char c)
{
    char **line;
    char *new;
    t_words *word;
    int i;

    i = 0;
    new = NULL;
    word = *words;
    line = malloc(sizeof(char *) * (count_pipes(*words) + 2));
    if (!line)
        return NULL;
    line = aux_split_pipe(word, c, line, new);
    return (line);
}

char **init_pipe(t_words **words, t_variables *vars)
{
    char **args;
    int i = 0;
    args = split_pipe(words, '|');
    vars->quant = count_pipes(*words) + 1;
    vars->prev_fd = -1;
    vars->index = -1;
    return (args);
}

void process_child_pipe(t_variables *vars, int fd[2], t_words **words)
{
    if (vars->prev_fd != -1)
    {
        dup2(vars->prev_fd, 0);
        close(vars->prev_fd);
    }
    if (vars->index < vars->quant - 1)
        dup2(fd[1], STDOUT_FILENO);
    // ft_exec_functions(vars, words);
    if (strchr(vars->args[0], '>') != NULL || strchr(vars->args[0], '<') != NULL)
        function_redir(vars, words);
    else
        ft_exec_functions(vars, words);
    close(fd[0]);
    exit(0);
}

void init_process(t_variables *vars, int fd[2], char **args, t_words **words)
{
    if (pipe(fd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    free_matriz(vars->args);
    vars->args = NULL;
    vars->args = ft_split(args[vars->index], ' ');
    vars->pid = fork();
    if (vars->pid == 0)
        process_child_pipe(vars, fd, words);
    else if (vars->pid > 0)
    {
        waitpid(vars->pid, &vars->status_command, 0);
        close(fd[1]);
        vars->prev_fd = fd[0];
    }
    else
    {
        waitpid(vars->pid, &vars->status_command, 0);
        perror("Error");
    }
    free_matriz(vars->args);
    vars->args = NULL;
}

char *first_word(char *str)
{
    int i = 0;
    int j = 0;

    while (str[i] && (str[i] == ' ' || str[i] == '\t'))
        i++;
    while (str[j] && (str[j] != ' ' || str[j] != '\t'))
        j++;
    char *new = ft_substr(str, i, j);
    return (new);
}

void function_pipe(t_variables *vars, t_words **words)
{
    int fd[2];
    char **args;
    char **get_args;
    int i;
    int j = 0;

    i = 0;
    args = init_pipe(words, vars);
    if (args == NULL)
        return;
    if (vars->quant == 1)
    {
        if (strchr(args[0], '>') != NULL || strchr(args[0], '<') != NULL)
            function_redir(vars, words);
        else
            ft_exec_functions(vars, words);
        if (args)
            free_matriz(args);
        return;
    }
    while (++vars->index < vars->quant)
        init_process(vars, fd, args, words);
    free_matriz(args);
}
