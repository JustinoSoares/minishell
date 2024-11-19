/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquilami <rquilami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:22:22 by rquilami          #+#    #+#             */
/*   Updated: 2024/11/19 12:42:41 by rquilami         ###   ########.fr       */
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


static void clean_all(t_env *ev)
{
	free(ev->env);
	free(ev->env_copy);
}
//Precisa também aceitar números como argumento...e sair normalmente
void    ft_exit(char *str, t_env  *ev)
{
	int i;

	i = 0;
	clean_all(ev);
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

