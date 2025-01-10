/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_expanded.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: justinosoares <justinosoares@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 11:15:23 by rquilami          #+#    #+#             */
/*   Updated: 2025/01/09 23:57:59 by justinosoar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char *get_key(char *env)
{
	int i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	return (ft_substr(env, 0, i));
}

char *ft_get_env(char *key, t_env *env)
{
	int i;
	int c;
	char *get_env;

	i = 0;
	c = 0;
	while (env->env[i])
	{
		get_env = get_key(env->env[i]);
		if (ft_strcmp(get_env, key) == 0)
		{
			while (env->env[i][c] && env->env[i][c] != '=')
				c++;
			if (env->env[i][c] == '=')
			{
				free(get_env);
				return (env->env[i] + c + 1);
			}
		}
		free(get_env);
		i++;
	}
	return (NULL);
}

char *call_status(char *str, t_variables *vars)
{
	if (g_status_signal == SIGINT)
		vars->status_command = 130;
	else if (g_status_signal == SIGQUIT)
		vars->status_command = 131;
	g_status_signal = 0;
	return (ft_itoa(vars->status_command));
}

char *aux_expanded(char *str, char *getter, t_variables *vars, int j)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] && str[i] == '$' && str[i + 1] == '?')
			return (call_status(str, vars));
		else if (str[i] && str[i] == '$' && str[i + 1] && ft_isalnum(str[i + 1]))
		{
			vars->ext->word = get_word(str, i + 1);
			vars->ext->macro = ft_get_env(vars->ext->word, vars->ev);
			if (vars->ext->macro && ft_strlen(vars->ext->macro) > 0)
				strcat(getter, vars->ext->macro);
			j += ft_strlen(vars->ext->macro);
			i += ft_strlen(vars->ext->word) + 1;
			free(vars->ext->word);
		}
		else if (str[i])
			getter[j++] = str[i++];
		else
			i++;
	}
	getter[j] = '\0';
	return (getter);
}