/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquilami <rquilami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:22:00 by rquilami          #+#    #+#             */
/*   Updated: 2025/01/08 15:08:24 by rquilami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	set_values(t_env *ev, char *var, int i, int j)
{
	j = 0;
	i++;
	if (var[i] == '"' || var[i] == '\'')
	{
		i++;
		while (var[i] != '"' && var[i] != '\'')
		{
			ev->value[j++] = var[i];
			i++;
		}
	}
	else
	{
		while (var[i] != '\0' && var[i] != 32)
		{
			ev->value[j++] = var[i];
			i++;
		}
	}
	ev->value[j] = '\0';
}

static void	replace_env(int i, int j, char *key, t_env *ev)
{
	int	n;

	if (!ev->just_var)
	{
		ev->env[i] = realloc(ev->env[i], ft_strlen(ev->key)
				+ ft_strlen(ev->value) + 2);
		if (!ev->env[i])
			return ;
		while (j < ft_strlen(ev->key))
		{
			ev->env[i][j] = ev->key[j];
			j++;
		}
		ev->env[i][j] = '=';
		j++;
		n = 0;
		while (n < ft_strlen(ev->value))
		{
			ev->env[i][j] = ev->value[n];
			j++;
			n++;
		}
		ev->env[i][j] = '\0';
		ev->found = 1;
	}
}

static void	var_value(int i, int n, char *key, t_env *ev)
{
	int	j;

	ev->env[i] = malloc(sizeof(char) * (ft_strlen(key) + ft_strlen(ev->value)
				+ 2));
	if (!ev->env[i])
		return ;
	j = 0;
	while (j < ft_strlen(key))
	{
		ev->env[i][j] = ev->key[j];
		j++;
	}
	ev->env[i][j] = '=';
	j++;
	n = 0;
	while (n < ft_strlen(ev->value))
	{
		ev->env[i][j] = ev->value[n];
		j++;
		n++;
	}
	ev->env[i][j] = '\0';
}

static void	new_env(int i, int n, char *key, t_env *ev)
{
	int	j;

	ev->env = realloc(ev->env, sizeof(char *) * (ev->len + 2));
	if (!ev->env)
		return ;
	if (ev->just_var)
	{
		j = 0;
		ev->env[i] = malloc(sizeof(char) * (ft_strlen(key)) + 1);
		while (j < ft_strlen(key))
		{
			ev->env[i][j] = ev->key[j];
			j++;
		}
		ev->env[i][j] = '\0';
	}
	else
		var_value(i, n, key, ev);
	ev->env[i + 1] = NULL;
	ev->len++;
}

void	set_env(char *key, t_env *ev)
{
	int	i;
	int	j;
	int	n;

	i = 0;
	j = 0;
	n = 0;
	while (ev->env[i] != NULL && !ev->found)
	{
		if (strncmp(ev->env[i], key, ft_strlen(key)) == 0)
		{
			if (ev->just_var)
				return ;
			replace_env(i, j, key, ev);
		}
		i++;
	}
	if (!ev->found)
		new_env(i, n, key, ev);
	ev->found = 0;
}