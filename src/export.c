/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 13:56:42 by rquilami          #+#    #+#             */
/*   Updated: 2024/12/13 06:20:41 by jsoares          ###   ########.fr       */
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

int count_key_value(char *var, int identify)
{
	int i = 0;
	int count = 0;

	while (var[i] && var[i] != '=')
	{
		count++;
		i++;
	}
	if (identify == 0)
		return (count);
	count = 0;
	if (var[i])
		i++;
	else
		return (0);
	if (var[i] && var[i] == '"')
		i++;
	while (var[i] != '\0')
	{
		count++;
		i++;
	}
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

char *ft_value_dup(char *var, char *value, int i)
{
	int pos_value = 0;
	while (var[i] != '\0' && var[i] != '"')
	{
		value[pos_value] = var[i];
		pos_value++;
		i++;
	}
	value[pos_value] = '\0';
	return (value);
}

char *ft_value_simple(char *var, char *value, int i)
{
	int pos_value = 0;
	while (var[i] != '\0' && var[i] != '\'')
	{
		value[pos_value] = var[i];
		pos_value++;
		i++;
	}
	value[pos_value] = '\0';
	return (value);
}

char *ft_value(char *var)
{
	int pos_value = 0;
	char *value;
	int i;

	if (ft_strchr(var, '=') == NULL)
		return (NULL);
	i = count_key_value(var, 0) + 1;
	value = malloc(sizeof(char) * count_key_value(var, 1) + 1);
	if (value == NULL)
		return (NULL);
	if (var[i] && var[i] == '"')
		value = ft_value_dup(var, value, i + 1);
	else if (var[i] && var[i] == '\'')
		value = ft_value_simple(var, value, i + 1);
	else
	{
		printf("value: %s\n", value);
		while (var[i] != '\0')
		{
			value[pos_value] = var[i];
			pos_value++;
			i++;
		}
		value[pos_value] = '\0';
	}
	return (value);
}

char *replace_space(char *s, char c)
{
	int i;
	char quote;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '"' || s[i] == '\'')
		{
			quote = s[i];
			i++;
			while (s[i] != '\0' && s[i] != quote)
				i++;
		}
		if (s[i] == ' ')
			s[i] = c;
		i++;
	}
	return (s);
}

int count_words(t_words *words)
{
	int count = 0;
	t_words *tmp;

	tmp = words;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

char *args_export(t_words **words)
{
	char *var = NULL;
	t_words *tmp = *words;

	if (!tmp || !tmp->next)
	{
		return NULL; // Return NULL if there are not enough words
	}

	tmp = tmp->next;				  // Move to the next word
	var = ft_strjoin(var, tmp->word); // Join first word

	if (tmp->next)
	{
		tmp = tmp->next; // Move to the next word
		if (tmp->type == 1)
		{									   // Single quotes
			char *temp = ft_strjoin(var, "'"); // Join single quote
			free(var);						   // Free previous var before reassigning
			var = temp;
			temp = ft_strjoin(var, tmp->word); // Join word inside quotes
			free(var);
			var = temp;
			temp = ft_strjoin(var, "'"); // Join closing single quote
			free(var);
			var = temp;
		}
		else if (tmp->type == 2)
		{										// Double quotes
			char *temp = ft_strjoin(var, "\""); // Join double quote
			free(var);
			var = temp;
			temp = ft_strjoin(var, tmp->word); // Join word inside quotes
			free(var);
			var = temp;
			temp = ft_strjoin(var, "\""); // Join closing double quote
			free(var);
			var = temp;
		}
	}
	return (var); // Return the constructed string
}

void get_variable(t_env *ev, t_words **words)
{
	char **split;
	char *var;

	var = args_export(words);
	if (!var)
	{
		export(ev, NULL, NULL);
		return;
	}
	ev->i = 0;
	ev->just_var = 0;
	ev->key = ft_key(var);
	ev->value = ft_value(var);
	verfi_arg(ev);
	export(ev, ev->key, ev->value);
	free(ev->key);
	free(ev->value);
	free(var);
}
