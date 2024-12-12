/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:59:09 by jsoares           #+#    #+#             */
/*   Updated: 2024/12/12 14:12:42 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void    ft_pwd(t_variables *vars)
{
    char pwd[1024];
    
    if (vars->args[1] == NULL)
    {
        if (getcwd(pwd, sizeof(pwd)) != NULL)
            printf("%s\n", pwd);
    }
    else
        printf("pwd: can't have argument\n");
}

static void clean_all(t_env *ev)
{
	free(ev->env);
	free(ev->env_copy);
}

void    ft_exit(t_variables *vars)
{
	int i;
	char *str;

	i = 0;
	str = vars->args[1];
	clean_all(vars->ev);
	if (str != NULL || ft_strlen(str) != 0)
	{
		while (str[i] != '\0')
		{
			if (!ft_isdigit(str[i]))
			{
				printf("bash: exit: %s: numeric argument required\n", str);
				exit (2);
			}
			i++;
		}
		printf("exit\n");
		exit(ft_atoi(str));
	}
	else
	{
		printf("exit\n");
		exit(0);
	}
}
