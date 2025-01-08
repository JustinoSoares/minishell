/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquilami <rquilami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 09:55:32 by jsoares           #+#    #+#             */
/*   Updated: 2025/01/08 16:53:37 by rquilami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_variables(t_variables *vars)
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

void	init_ev(t_env *ev)
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

void	cat_path(char *full_path, char *dirs, char *command)
{
	ft_strlcpy(full_path, dirs, MAX_PATH);
	ft_strlcat(full_path, "/", MAX_PATH);
	ft_strlcat(full_path, command, MAX_PATH);
}

char	*find_executable(char *command)
{
	char		*path;
	static char	full_path[MAX_PATH];
	struct stat	buffer;
	char		**dirs;
	int			i;

	i = 0;
	path = getenv("PATH");
	if (!path)
		return (NULL);
	dirs = ft_split(path, ':');
	while (dirs[i++])
	{
		if (ft_strlen(dirs[i]) + 1 + ft_strlen(command) < MAX_PATH)
		{
			cat_path(full_path, dirs[i], command);
			if (stat(full_path, &buffer) == 0 && (buffer.st_mode & S_IXUSR))
			{
				free_matriz(dirs);
				return (full_path);
			}
		}
	}
	free_matriz(dirs);
	return (NULL);
}
