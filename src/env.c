/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquilami <rquilami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:22:22 by rquilami          #+#    #+#             */
/*   Updated: 2024/11/18 12:36:20 by rquilami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void env(t_env *ev, char *str)
{
	if (str == NULL || ft_strlen(str) == 0)
	{
		int		i;

		i = 0;
		while (ev->env[i] != NULL)
		{
			printf("%s\n", ev->env[i]);
			i++;
		}
	}
	else
		printf("env: `%s\': No such file or directory\n", str);
}

void	unset(char *key, t_env *ev)
{
    int i;
	int j;

	
	i = 0;
	j = 0;
    while (ev->env[i] != NULL)
	{
        if (strncmp(ev->env[i], key, ft_strlen(key)) == 0 && ev->env[i][ft_strlen(key)] == '=')
		{
            free(ev->env[i]);
            while (j < ev->len)
			{
                ev->env[j] = ev->env[j + 1];
				j++;
            }
		}
        i++;
    }
	ev->env = realloc(ev->env, sizeof(char *) * i--);
	if (ev->env == NULL && ev->len > 0)
		return;
}

//Será alterada em funcao da neccessidade de free
//que houver no decorrer do desenvolvimento do projeto

//Precisa também aceitar números como argumento...e sair normalmente
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

