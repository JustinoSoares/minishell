/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: justinosoares <justinosoares@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:22:22 by rquilami          #+#    #+#             */
/*   Updated: 2024/11/18 23:43:28 by justinosoar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void env(t_env *ev, t_variables vars)
{
    char *str;
    int		i;

    str = vars.line + (start_write(vars.line, vars.args[0]));
	if (str == NULL || ft_strlen(str) == 0)
	{
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