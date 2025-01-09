/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 16:13:36 by rquilami          #+#    #+#             */
/*   Updated: 2025/01/08 19:36:16 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	other_func(t_variables *vars, char *command)
{
	int	i;

	i = 0;
	if (ft_strcmp(command, "export") == 0)
	{
		export(vars->ev, NULL, NULL);
	}
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

void	init_vars(t_variables *vars)
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

int	open_file(char *file, char *redir_type)
{
	int	fd;

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

void	clean_cmd(t_variables *vars)
{
	int	i;

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
