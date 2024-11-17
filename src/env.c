/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquilami <rquilami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:22:22 by rquilami          #+#    #+#             */
/*   Updated: 2024/11/17 14:04:06 by rquilami         ###   ########.fr       */
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
    int i = 0;
	int j = 0;

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
	ev->env = realloc(ev->env, sizeof(char *) * ev->len--);
	if (ev->env == NULL && ev->len > 0)
		return;
}

