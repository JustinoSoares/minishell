/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_aux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: justinosoares <justinosoares@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:34:19 by rquilami          #+#    #+#             */
/*   Updated: 2025/01/09 23:08:29 by justinosoar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void new_prompt(int signal)
{
	if (signal == SIGINT)
		write(1, "\n", 1);
	else if (signal == SIGQUIT)
		write(1, "Good bye\n", 9);
}

void process_child(char *command_path, t_variables *vars)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (ft_strchr(command_path, '/') != NULL)
	{
		if (access(command_path, X_OK) != 0)
		{
			write(2, "Command not found\n", 18);
			vars->status_command = 127;
			free_matriz(vars->args);
			exit(127);
		}
	}
	else
	{
		command_path = find_executable(vars->args[0]);
		
		if (command_path == NULL)
		{
			write(2, "Command not found\n", 18);
			vars->status_command = 2;
			free_matriz(vars->args);
			exit(127);
		}
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
	if (command_path == NULL)
		return;
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

void ft_exec_functions(t_variables *vars, t_words **words)
{
	if (vars->args[0] && ft_strcmp(vars->args[0], "echo") == 0)
	{
		if (vars->args[1])
			ft_echo(vars);
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
