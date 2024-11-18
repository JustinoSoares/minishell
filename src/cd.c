/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: justinosoares <justinosoares@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:54:14 by justinosoar       #+#    #+#             */
/*   Updated: 2024/11/18 23:03:51 by justinosoar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void ft_cd(t_variables vars)
{
    char *path;

    if (vars.args[1] != NULL)
    {
        path = vars.args[1];
        if (path == NULL || ft_strlen(path) == 0)
        {
            printf("cd: no such file or directory:\n");
            return;
        }
        if (chdir(path) == -1)
        {
            printf("cd: no such file or directory: %s\n", path);
            return;
        }
    }
    else
        printf("cd: no such file or directory:\n");
}
