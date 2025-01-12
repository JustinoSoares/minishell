/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:22:22 by rquilami          #+#    #+#             */
/*   Updated: 2025/01/12 18:14:46 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	fill_env(t_env *ev, char **envp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (envp[i] != NULL)
		i++;
	ev->len = i;
	ev->env = ft_calloc((i + 1), sizeof(char *));
	if (!ev->env)
		return ;
	while (j < i)
	{
		ev->env[j] = ft_strdup(envp[j]);
		if (!ev->env[j])
		{
			while (j > 0)
				free(ev->env[--j]);
			free(ev->env);
			return ;
		}
		j++;
	}
}

void	env(t_env *ev, t_variables *vars)
{
	char	*str;
	int		i;

	str = get_args(vars->args, 1);
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
		write(2, "env:': No such file or directory\n", 34);
}

void	unset(char *key, t_env *ev)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (key == NULL || ft_strlen(key) == 0)
		return ;
	while (ev->env[i] != NULL)
	{
		if (ft_strncmp(ev->env[i], key, ft_strlen(key)) == 0)
		{
			(free(ev->env[i]), j = i);
			while (ev->env[j] != NULL)
				(ev->env[j] = ev->env[j + 1], j++);
			ev->len--;
		}
		else
			i++;
	}
	ev->env = realloc(ev->env, sizeof(char *) * (ev->len + 1));
	if (ev->env == NULL)
		return ;
}
