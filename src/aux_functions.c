/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquilami <rquilami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 09:55:32 by jsoares           #+#    #+#             */
/*   Updated: 2024/11/28 12:31:23 by rquilami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int count_pipes(char *str)
{
    int i = 0;
    int count = 0;
    while (str[i])
    {
        if (str[i] == '|')
            count++;
        i++;
    }
    return (count);
}

int redir_in_line(char *str)
{
    int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '>' || str[i] == '<')
			return (1);
		i++;
	}
    return (0);
}

char *find_executable(char *command)
{
    char *path = getenv("PATH");
    static char full_path[MAX_PATH];
    struct stat buffer;
    char **dirs;
    int i = 0;
    int len_dir;
    int len_cmd;
    dirs = ft_split(path, ':');
    while (dirs[i])
    {
        len_dir = ft_strlen(dirs[i]);
        len_cmd = ft_strlen(command);
        if (len_dir + 1 + len_cmd < MAX_PATH)
        {
            ft_strlcpy(full_path, dirs[i], MAX_PATH);
            ft_strlcat(full_path, "/", MAX_PATH);
            ft_strlcat(full_path, command, MAX_PATH);
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
