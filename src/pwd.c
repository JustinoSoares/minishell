/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquilami <rquilami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:59:09 by jsoares           #+#    #+#             */
/*   Updated: 2024/11/22 23:35:25 by rquilami         ###   ########.fr       */
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

static void clean_all(t_env *ev)
{
	free(ev->env);
	free(ev->env_copy);
}

void    ft_exit(t_variables vars)
{
	int i;

	i = 0;
	clean_all(vars.ev);
	if (vars.args[1] != NULL && ft_strlen(vars.args[1]) != 0)
	{
		while (vars.args[1][i] != '\0')
		{
			if (!ft_isdigit(vars.args[1][i]))
			{
				printf("bash: exit: %s: numeric argument required\n", vars.args[1]);
				exit (2);
			}
			i++;
		}
		printf("exit\n");
		
		exit(ft_atoi(vars.args[1]));
	}
	else
	{
		printf("exit\n");
		exit(0);
	}
}

