
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquilami <rquilami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 08:34:50 by rquilami          #+#    #+#             */
/*   Updated: 2024/12/06 12:58:54 by rquilami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void other_func(t_variables *vars, char *command)
{
    int i;

    i = 0;
    if (ft_strcmp(command, "export") == 0)
        export(vars->ev, NULL, NULL);
    else if (ft_strcmp(command, "env") == 0)
    {
        while (vars->ev->env[i] != NULL)
        {
            printf("%s\n", vars->ev->env[i]);
            i++;
        }
    }
    exit(0);
}

void execute_redir(char *command, t_variables *vars, int std)
{
    if (dup2(vars->fd, std) == -1)
    {
        perror("Erro ao redirecionar stdout");
        close(vars->fd);
        return;
    }
    vars->pid = fork();
    if (vars->pid == 0) // Processo filho
    {
        vars->cmd_args[0] = find_executable(command);
        if (ft_strcmp(command, "export") == 0 || ft_strcmp(command, "env") == 0)
        {
            other_func(vars, command);
        }
        else
        {
            execve(vars->cmd_args[0], vars->cmd_args, vars->env);
            // Caso execve falhe
            perror("Erro ao executar comando");
            exit(EXIT_FAILURE);
        }
    }
    else if (vars->pid > 0) // Processo pai
    {
        int status;
        waitpid(vars->pid, &status, 0); // Espera pelo término do processo filho

        if (dup2(vars->saved_std, std) == -1)
        {
            perror("Erro ao restaurar o stdout original");
        }
        close(vars->fd);
    }
    else // Erro no fork
    {
        perror("Erro ao criar processo filho");
        close(vars->fd);
    }
}

int here_doc(const char *file)
{
    int pipe_fd[2];
    char *line;
    int fd;

    if (pipe(pipe_fd) == -1)
    {
        perror("pipe");
        return -1;
    }
    while ((line = readline("> ")) != NULL && strcmp(line, file) != 0)
    {
        write(pipe_fd[1], line, strlen(line));
        write(pipe_fd[1], "\n", 1);
        free(line);
    }
    free(line);
    close(pipe_fd[1]);
    fd = pipe_fd[0];
    return (fd);
}

int open_file(char *file, char *redir_type)
{
    int fd;

    fd = -1;
    if (ft_strcmp(redir_type, ">") == 0)
        fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    else if (ft_strcmp(redir_type, ">>") == 0)
        fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
    else if (ft_strcmp(redir_type, "<") == 0)
        fd = open(file, O_RDONLY);
    else if (ft_strcmp(redir_type, "<<") == 0)
        fd = here_doc(file);
    return (fd);
}

void define_redir(t_words **words, t_variables *vars)
{
    t_words *tmp = *words;

    while (tmp != NULL)
    {
        if (ft_strcmp(tmp->word, "<<") == 0)
        {
            vars->type_redir = "<<";
            vars->redir_here_doc_found = 1;
        }
        else if (ft_strcmp(tmp->word, ">") == 0 || ft_strcmp(tmp->word, ">>") == 0)
        {
            if (!vars->redir_here_doc_found)
                vars->type_redir = tmp->word;
            vars->redir_greater_found = 1;
        }
        else if (ft_strcmp(tmp->word, "<") == 0)
        {
            if (!vars->redir_here_doc_found && !vars->redir_greater_found)
                vars->type_redir = "<";
            vars->redir_lesser_found = 1;
        }
        tmp = tmp->next;
    }
}

void token_cmd_args(t_words **words, t_variables *vars)
{
    t_words *tmp = *words;
    int i = 0;

    while (tmp != NULL)
    {
        if (ft_strcmp(tmp->word, ">") == 0 || ft_strcmp(tmp->word, ">>") == 0 ||
            ft_strcmp(tmp->word, "<") == 0 || ft_strcmp(tmp->word, "<<") == 0)
            tmp = tmp->next;
        else
        {
            vars->cmd_args[i] = tmp->word;
            i++;
        }
        tmp = tmp->next;
    }
    vars->cmd_args[i] = NULL;
}

void token_file_out(t_words **words, t_variables *vars)
{
    t_words *tmp = *words;

    while (tmp != NULL)
    {
        if (ft_strcmp(tmp->word, ">") == 0 || ft_strcmp(tmp->word, ">>") == 0)
        {
            tmp = tmp->next;
            if (tmp != NULL && (ft_strcmp(tmp->word, ">") != 0 && ft_strcmp(tmp->word, ">>") != 0))
            {
                vars->files_out[vars->count_out] = tmp->word;
                vars->count_out++;
            }
        }
        tmp = tmp->next;
    }
    vars->files_out[vars->count_out] = NULL;
}

void token_file_in(t_words **words, t_variables *vars)
{
    t_words *tmp = *words;

    while (tmp != NULL)
    {
        if (ft_strcmp(tmp->word, "<") == 0 || ft_strcmp(tmp->word, "<<") == 0)
        {
            tmp = tmp->next;
            if (tmp != NULL && (ft_strcmp(tmp->word, "<") != 0 && ft_strcmp(tmp->word, "<<") != 0))
            {
                vars->files_in[vars->count_in] = tmp->word;
                vars->count_in++;
            }
        }
        tmp = tmp->next;
    }
    vars->files_in[vars->count_in] = NULL;
}

void remove_space(char *str, char ch)
{
    int i;
    int j;
    int len;

    i = 0;
    j = 0;
    if (str == NULL || str[0] == '\0')
        return;
    len = ft_strlen((const char *)str);
    while (i < len)
    {
        if (str[i] != ch)
            str[j++] = str[i];
        i++;
    }
    str[j] = '\0';
}

void clean_cmd(t_variables *vars)
{
    int i;

    i = 0;
    while (vars->cmd_args[i] != NULL)
    {
        remove_space(vars->cmd_args[i], ' ');
        i++;
    }
    i = 0;
    while (vars->files_out[i] != NULL)
    {
        remove_space(vars->files_out[i], ' ');
        i++;
    }
    i = 0;
    while (vars->files_in[i] != NULL)
    {
        remove_space(vars->files_in[i], ' ');
        i++;
    }
}

int redir_out(t_variables *vars, char *command)
{
    int i;

    i = 0;
    vars->saved_std = dup(STDOUT_FILENO);
    if (vars->files_out[0] != NULL)
    {
        while (i < vars->count_out)
        {
            if (i == vars->count_out - 1)
            {
                vars->fd = open_file(vars->files_out[i], vars->type_redir);
                execute_redir(command, vars, 1);
            }
            else
            {
                vars->fd = open(vars->files_out[i], O_CREAT | O_WRONLY | O_TRUNC, 0644);
                if (vars->fd != -1)
                    close(vars->fd);
            }
            i++;
        }
    }
    close(vars->fd);
    close(vars->saved_std);
    return (0);
}

int redir_in(t_variables *vars, char *command)
{
    int i;

    i = 0;
    vars->saved_std = dup(STDIN_FILENO);
    if (vars->files_in[0] != NULL)
    {
        while (i < vars->count_in)
        {
            if (i == vars->count_in - 1)
            {
                vars->fd = open_file(vars->files_in[i], vars->type_redir);
                execute_redir(command, vars, 0);
            }
            else
            {
                vars->fd = open(vars->files_in[i], O_CREAT | O_WRONLY | O_TRUNC, 0644);
                if (vars->fd != -1)
                    close(vars->fd);
            }
            i++;
        }
    }
    close(vars->fd);
    close(vars->saved_std);
    return 0;
}

void init_vars(t_variables *vars)
{
    vars->last_redir_type = NULL;
    vars->saved_std = 0;
    vars->redir_here_doc_found = 0;
    vars->redir_greater_found = 0;
    vars->redir_lesser_found = 0;
    vars->redir_found = 0;
    vars->count_out = 0;
    vars->count_in = 0;
    vars->fd = 0;
    vars->files_in[0] = NULL;
    vars->files_out[0] = NULL;
    vars->cmd_args[0] = NULL;
    vars->type_redir = NULL;
}

void function_redir(t_variables *vars, t_words **words)
{
    int i = 0;

    init_vars(vars);
    define_redir(words, vars);
    token_cmd_args(words, vars);
    if (ft_strcmp(vars->type_redir, ">") == 0 || ft_strcmp(vars->type_redir, ">>") == 0)
        token_file_out(words, vars);
    else if (ft_strcmp(vars->type_redir, "<") == 0 || ft_strcmp(vars->type_redir, "<<") == 0)
        token_file_in(words, vars);
    clean_cmd(vars);
    if ((ft_strcmp(vars->type_redir, ">") == 0) || ft_strcmp(vars->type_redir, ">>") == 0)
        redir_out(vars, vars->cmd_args[0]);
    else if ((ft_strcmp(vars->type_redir, "<") == 0) || ft_strcmp(vars->type_redir, "<<") == 0)
        redir_in(vars, vars->cmd_args[0]);
}