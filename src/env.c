/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:22:22 by rquilami          #+#    #+#             */
/*   Updated: 2025/01/08 19:11:16 by jsoares          ###   ########.fr       */
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
	ev->env = malloc((i + 1) * sizeof(char *));
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
	ev->env[i] = NULL;
}

void	env(t_env *ev, t_variables *vars)
{
	char	*str;
	int		i;

	str = get_args(vars->args);
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
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (ev->env[i] != NULL)
	{
		if (strncmp(ev->env[i], key, ft_strlen(key)) == 0
			&& ev->env[i][ft_strlen(key)] == '=')
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
		return ;
}
