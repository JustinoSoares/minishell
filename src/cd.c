/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: justinosoares <justinosoares@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:54:14 by justinosoar       #+#    #+#             */
/*   Updated: 2025/01/09 23:34:29 by justinosoar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void ft_cd(t_variables *vars)
{
	char *path;

	if (vars->args[1] == NULL || ft_strlen(vars->args[1]) == 0)
		write(2, "cd: no such file or directory\n", 31);
	else if (vars->args[2] != NULL)
		write(2, "bash: cd: demasiados argumentos\n", 32);
	else if (vars->args[1] != NULL)
	{
		path = vars->args[1];
		if (path == NULL || ft_strlen(path) == 0)
			write(2, "cd: no such file or directory\n", 31);
		else if (chdir(path) == -1)
			write(2, "cd: no such file or directory\n", 31);
	}
}
