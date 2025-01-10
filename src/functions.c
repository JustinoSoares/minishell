/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: justinosoares <justinosoares@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:34:08 by jsoares           #+#    #+#             */
/*   Updated: 2025/01/10 02:09:17 by justinosoar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char *form_word(t_words *word, char *new, char *tmp)
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

void process_child_pipe(t_variables *vars, int fd[2], t_words **words)
{
	if (vars->prev_fd != -1)
	{
		dup2(vars->prev_fd, 0);
		close(vars->prev_fd);
	}
	if (vars->index < vars->quant - 1)
		dup2(fd[1], STDOUT_FILENO);
	if (ft_strchr(vars->args[0], '>') != NULL
			|| ft_strchr(vars->args[0], '<') != NULL)
		redirect_error(vars->args[0], vars, words);
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
	if (vars->args == NULL)
		return;
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
	int i;
	int j;
	char *new;

	i = 0;
	j = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	while (str[j] && (str[j] != ' ' || str[j] != '\t'))
		j++;
	new = ft_substr(str, i, j);
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
		return ;
	if (vars->quant == 1)
	{
		if (ft_strchr(args[0], '>') != NULL 
			|| ft_strchr(args[0], '<') != NULL)
			redirect_error(args[0], vars, words);
		else
			ft_exec_functions(vars, words);
		free_matriz(args);
		args = NULL;
		return;
	}
	while (++vars->index < vars->quant)
		init_process(vars, fd, args, words);
	free_matriz(args);
	args = NULL;
}
