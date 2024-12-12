/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 09:55:32 by jsoares           #+#    #+#             */
/*   Updated: 2024/12/12 12:59:47 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void cat_path(char *full_path, char *dirs, char *command)
{
    ft_strlcpy(full_path, dirs, MAX_PATH);
    ft_strlcat(full_path, "/", MAX_PATH);
    ft_strlcat(full_path, command, MAX_PATH);
}

char *find_executable(char *command)
{
    char *path;
    static char full_path[MAX_PATH];
    struct stat buffer;
    char **dirs;
    int i;

    i = 0;
    path = getenv("PATH");
    if (!path)
        return (NULL);
    dirs = ft_split(path, ':');
    while (dirs[i])
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
        i++;
    }
    free_matriz(dirs);
}
