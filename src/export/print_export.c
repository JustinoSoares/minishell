/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquilami <rquilami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 14:03:40 by rquilami          #+#    #+#             */
/*   Updated: 2025/01/08 15:09:13 by rquilami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	sort_env(char **env)
{
	int		i;
	int		n;
	int		j;
	char	*temp;

	i = 0;
	n = 0;
	while (env[n] != NULL)
		n++;
	while (i < n - 1)
	{
		j = 0;
		while (j < n - i - 1)
		{
			if (strcmp(env[j], env[j + 1]) > 0)
			{
				temp = env[j];
				env[j] = env[j + 1];
				env[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

static void	copy_env(t_env *ev)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (ev->env[i] != NULL)
		i++;
	ev->len = i;
	ev->env_copy = malloc((i + 1) * sizeof(char *));
	if (!ev->env_copy)
		return ;
	while (j < i)
	{
		ev->env_copy[j] = strdup(ev->env[j]);
		j++;
	}
	ev->env_copy[i] = NULL;
}

static void	aux_print_env(t_env *ev)
{
	while (ev->env_copy[ev->i][ev->j] != '\0')
	{
		if (ev->env_copy[ev->i][ev->j] == '=')
		{
			printf("%c", ev->env_copy[ev->i][ev->j]);
			printf("\"");
			ev->j++;
			while (ev->env_copy[ev->i][ev->j] != '\0')
			{
				printf("%c", ev->env_copy[ev->i][ev->j]);
				ev->j++;
			}
			printf("\"");
		}
		else
		{
			printf("%c", ev->env_copy[ev->i][ev->j]);
			ev->j++;
		}
	}
}

static void	print_env(t_env *ev)
{
	ev->i = 0;
	while (ev->env_copy[ev->i] != NULL)
	{
		ev->j = 0;
		printf("declare -x ");
		aux_print_env(ev);
		printf("\n");
		ev->i++;
	}
}

void	export(t_env *ev, char *var, char *value)
{
	if (var == NULL || ft_strlen(var) == 0)
	{
		copy_env(ev);
		sort_env(ev->env_copy);
		print_env(ev);
	}
	else
	{
		ev->key = var;
		ev->value = value;
		set_env(ev->key, ev);
	}
}
