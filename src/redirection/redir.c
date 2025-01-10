/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: justinosoares <justinosoares@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 08:34:50 by rquilami          #+#    #+#             */
/*   Updated: 2025/01/09 22:24:01 by justinosoar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void execute_redir(char *command, t_variables *vars, int std)
{
	int status;

	dup2(vars->fd, std);
	vars->pid = fork();
	if (vars->pid == 0)
	{
		if (ft_strcmp(command, "export") == 0 || ft_strcmp(command, "env") == 0)
			other_func(vars, command);
		else
		{
			vars->cmd_args[0] = find_executable(command);
			if (vars->cmd_args[0] == NULL)
				exit(127);
			execve(vars->cmd_args[0], vars->cmd_args, vars->env);
			perror("Erro ao executar comando");
			exit(EXIT_FAILURE);
		}
	}
	else if (vars->pid > 0)
	{
		waitpid(vars->pid, &status, 0);
		dup2(vars->saved_std, std);
		close(vars->fd);
	}
}

int here_doc(const char *file)
{
	int pipe_fd[2];
	char *line;
	int fd;

	if (file == NULL || file[0] == '\0')
		write(2, "bash: syntax error near unexpected token\n", 41);
	if (pipe(pipe_fd) == -1)
		perror("pipe");
	if (file == NULL || file[0] == '\0' || pipe_fd[0] == -1)
		return (-1);
	while (true)
	{
		line = readline("> ");
		if (line == NULL || strcmp(line, file) == 0)
			break;
		write(pipe_fd[1], line, strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
	}
	free(line);
	close(pipe_fd[1]);
	fd = pipe_fd[0];
	return (fd);
}

void define_redir(t_words **words, t_variables *vars)
{
	t_words *tmp;

	tmp = *words;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->word, "<<") == 0)
		{
			vars->type_redir = "<<";
			vars->redir_here_doc_found = 1;
		}
		else if (ft_strcmp(tmp->word, ">") == 0 || ft_strcmp(tmp->word,
															 ">>") == 0)
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

void function_redir(t_variables *vars, t_words **words)
{
	int i;

	i = 0;
	init_vars(vars);
	token_cmd_args(words, vars);
	define_redir(words, vars);
	if (ft_strcmp(vars->type_redir, ">") == 0 
			|| ft_strcmp(vars->type_redir, ">>") == 0)
		token_file_out(words, vars);
	else if (ft_strcmp(vars->type_redir, "<") == 0 
			|| ft_strcmp(vars->type_redir, "<<") == 0)
		token_file_in(words, vars);
	clean_cmd(vars);
	if ((ft_strcmp(vars->type_redir, ">") == 0)
			|| ft_strcmp(vars->type_redir, ">>") == 0)
		redir_out(vars, vars->cmd_args[0]);
	else if ((ft_strcmp(vars->type_redir, "<") == 0)
			|| ft_strcmp(vars->type_redir, "<<") == 0)
		redir_in(vars, vars->cmd_args[0]);
}
