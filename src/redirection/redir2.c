/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 16:21:35 by rquilami          #+#    #+#             */
/*   Updated: 2025/01/12 18:14:09 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	token_cmd_args(t_words **words, t_variables *vars)
{
	t_words	*tmp;
	int		i;

	tmp = *words;
	i = 0;
	while (tmp != NULL)
	{
		if ((ft_strcmp(tmp->word, ">") == 0 && tmp->type == 0)
			|| (ft_strcmp(tmp->word, ">>") == 0 && tmp->type == 0)
			|| (ft_strcmp(tmp->word, "<") == 0 && tmp->type == 0)
			|| (ft_strcmp(tmp->word, "<<") == 0 && tmp->type == 0))
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

int	token_cmd_error(t_words **words, t_variables *vars)
{
	t_words	*tmp;
	int		has_args;

	tmp = *words;
	has_args = 0;
	while (tmp != NULL)
	{
		if ((ft_strcmp(tmp->word, ">") == 0 && tmp->type == 0)
			|| (ft_strcmp(tmp->word, ">>") == 0 && tmp->type == 0)
			|| (ft_strcmp(tmp->word, "<") == 0 && tmp->type == 0)
			|| (ft_strcmp(tmp->word, "<<") == 0 && tmp->type == 0))
		{
			tmp = tmp->next;
			continue ;
		}
		else
			has_args = 1;
		tmp = tmp->next;
	}
	return (has_args);
}

void	token_file_out(t_words **words, t_variables *vars)
{
	t_words	*tmp;

	tmp = *words;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->word, ">") == 0 || ft_strcmp(tmp->word, ">>") == 0)
		{
			tmp = tmp->next;
			if (tmp != NULL && (ft_strcmp(tmp->word, ">") != 0
					&& ft_strcmp(tmp->word, ">>") != 0))
			{
				vars->files_out[vars->count_out] = tmp->word;
				vars->count_out++;
			}
		}
		tmp = tmp->next;
	}
	vars->files_out[vars->count_out] = NULL;
}

void	token_file_in(t_words **words, t_variables *vars)
{
	t_words	*tmp;

	tmp = *words;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->word, "<") == 0 || ft_strcmp(tmp->word, "<<") == 0)
		{
			tmp = tmp->next;
			if (tmp != NULL && (ft_strcmp(tmp->word, "<") != 0
					&& ft_strcmp(tmp->word, "<<") != 0))
			{
				vars->files_in[vars->count_in] = tmp->word;
				vars->count_in++;
			}
		}
		tmp = tmp->next;
	}
	vars->files_in[vars->count_in] = NULL;
}

void	redir_out(t_variables *vars, char *command)
{
	int	i;

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
				vars->fd = open(vars->files_out[i],
						O_CREAT | O_WRONLY | O_TRUNC, 0644);
				if (vars->fd != -1)
					close(vars->fd);
			}
			i++;
		}
	}
	close(vars->fd);
	close(vars->saved_std);
}

void	redir_in(t_variables *vars, char *command)
{
	int	i;

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
				vars->fd = open(vars->files_in[i], O_CREAT | O_WRONLY | O_TRUNC,
						0644);
				if (vars->fd != -1)
					close(vars->fd);
			}
			i++;
		}
	}
	close(vars->fd);
	close(vars->saved_std);
}
