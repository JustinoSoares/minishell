/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: justinosoares <justinosoares@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:59:09 by jsoares           #+#    #+#             */
/*   Updated: 2024/11/18 23:35:36 by justinosoar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void    ft_pwd(t_variables vars)
{
    char pwd[1024];
    
    if (vars.args[1] == NULL)
    {
        if (getcwd(pwd, sizeof(pwd)) != NULL)
            printf("%s\n", pwd);
    }
    else
        printf("pwd: can't have argument\n");
}

void    ft_exit(char *str, t_env  *ev)
{
	if (str == NULL || ft_strlen(str) == 0)
	{
		printf("exit\n");
		free(ev->env);
		free(ev->env_copy);
		exit(1);
	}
	else
		printf("bash: exit: %s: numeric argument required\n", str);
}