/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 13:56:42 by rquilami          #+#    #+#             */
/*   Updated: 2024/12/11 15:30:14 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Esta func pega as env e organiza elas em ordem alfabetica baseadas no valor da tabela ASCII
static void sort_env(char **env)
{
	int i;
	int n;
	int j;
	char *temp;

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
// Essa funcao verifica se o argumento passado no Export é valido
void verfi_arg(t_env *ev)
{
	ev->i = 0;
	while (ev->key[ev->i])
	{
		if (ev->key[ev->i] == '%' || ev->key[ev->i] == '#' ||
			ev->key[ev->i] == '{' || ev->key[ev->i] == '}' ||
			ev->key[ev->i] == ':' || ev->key[ev->i] == '?' ||
			ev->key[ev->i] == ';' || ev->key[ev->i] == '@' ||
			ev->key[ev->i] == ';' || ev->key[ev->i] == '@' ||
			ev->key[ev->i] == '+' || ev->key[ev->i] == '*' ||
			ev->key[ev->i] == ',' || ev->key[ev->i] == '.' ||
			ev->key[ev->i] == '^' || ev->key[ev->i] == '~' ||
			ev->key[ev->i] == '/' || ev->key[ev->i] == '-')
		{
			printf("export: `%s\' not a valid identifier\n", ev->key);
			return;
		}
		if (ev->key[ev->i] == '(' || ev->key[ev->i] == ')')
		{
			printf("syntax error near unexpected token `%c\'\n", ev->key[ev->i]);
			return;
		}
		ev->i++;
	}
}

static void print_env(t_env *ev)
{
	ev->i = 0;
	while (ev->env_copy[ev->i] != NULL)
	{
		ev->j = 0;
		printf("declare -x ");
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
		printf("\n");
		ev->i++;
	}
}

void export(t_env *ev, char *var, char *value)
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

int	count_key_value(char *var, int identify)
{
	int i = 0;
	int count = 0;

	while (var[i] != '=')
	{
		count++;
		i++;
	}
	printf("count key %d\n", count);
	if (identify == 0)
		return (count);
	count = 0;
	while (var[i] != '\0')
	{
		count++;
		i++;
	}
	printf("count value %d\n", count);
	return (count);
}

char *ft_key(char *var)
{
	int i = 0;
	int pos_key = 0;
	char *key;

	key = malloc(sizeof(char) * count_key_value(var, 0) + 1);
	if (key == NULL)
		return (NULL);
	while (var[i] != '=' && var[i] != 32 && var[i] != '\0' && var[i] != '$')
	{
		key[pos_key] = var[i];
		pos_key++;
		i++;
	}
	key[pos_key] = '\0';
	return (key);
}

char *ft_value(char *var)
{
	int pos_value = 0;
	char *value;
	int i = count_key_value(var, 0) + 1;

	value = malloc(sizeof(char) * count_key_value(var, 1) + 1);
	if (value == NULL)
		return (NULL);
	while (var[i] != '\0')
	{
		value[pos_value] = var[i];
		pos_value++;
		i++;
	}
	value[pos_value] = '\0';
	return (value);
}


void get_variable(t_env *ev, char *var)
{
	if (var == NULL || ft_strlen(var) == 0)
		export(ev, NULL, NULL);
	else
	{
		ev->i = 0;
		ev->just_var = 0;
		ev->key = ft_key(var);
		ev->value = ft_value(var);
		printf("key %s\n", ev->key);
		printf("value %s\n", ev->value);
		verfi_arg(ev);
		//set_values(ev, var, ev->i, ev->j);
		export(ev, ev->key, ev->value);
	}
}
