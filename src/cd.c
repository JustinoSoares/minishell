/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquilami <rquilami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:54:14 by justinosoar       #+#    #+#             */
/*   Updated: 2024/11/22 21:10:06 by rquilami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void    ft_cd(t_env *ev, char *path)
{
    char oldpwd[1024];
    char pwd[1024];

    getcwd(oldpwd, 1024);
    if (path == NULL || ft_strlen(path) == 0)
    {
        printf("cd: no such file or directory:\n");
        return ;
    }
    if (chdir(path) == -1)
    {
        printf("cd: no such file or directory: %s\n", path);
        return;
    }
    getcwd(pwd, 1024);
    export(ev, "OLDPWD", oldpwd);
    export(ev, "PWD", pwd);
}
