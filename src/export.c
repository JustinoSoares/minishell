/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquilami <rquilami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 13:56:42 by rquilami          #+#    #+#             */
/*   Updated: 2024/11/13 20:33:40 by rquilami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Esta func pega as env e organiza elas em ordem alfabetica baseadas no valor da tabela ASCII
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

//Essa funcao verifica se o argumento passado no Export é valido
static void verfi_arg(t_env *ev)
{
    int i;

    i = 0;
    while (ev->key[i])
    {
        if (ev->key[i] == '%' || ev->key[i] == '#' ||
        ev->key[i] == '{' || ev->key[i] == '}' ||
        ev->key[i] == ':' || ev->key[i] == '?' ||
        ev->key[i] == ';' || ev->key[i] == '@' ||
        ev->key[i] == '+' || ev->key[i] == '*' ||
        ev->key[i] == ',' || ev->key[i] == '.' ||
        ev->key[i] == '^' || ev->key[i] == '~' ||
        ev->key[i] == '/' || ev->key[i] == '-' )
        {
            printf("export: `%s' not a valid identifier\n", ev->key);
            return;
        }
        if (ev->key[i] == '(' || ev->key[i] == ')')
        {
            printf("syntax error near unexpected token `%c\'\n", ev->key[i]);
            return;
        }
        i++;
    }
}

static void	get_variable(t_env *ev, char *var)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	ev->just_var = 0;
	ev->key = malloc(sizeof(char) * ft_strlen(var) + 1);
	ev->value = malloc(sizeof(char) * ft_strlen(var) + 1);
	while (var[i] != '=' && var[i] != '\0' && var[i] != 32 && var[i] != '$')
	{
		ev->key[i] = var[i];
		i++;
	}
    verfi_arg(ev);
	if (var[i] == '\0')
		ev->just_var = 1;
	ev->key[i] = '\0';
	i++;
	while (var[i] != '\0')
	{
		ev->value[j++] = var[i];
		i++;
	}
	ev->value[j] = '\0';
}


static void	replace_env(int i, int j, int n, char *key, t_env *ev)
{
	if (!ev->just_var)
	{
		ev->env[i] = realloc(ev->env[i], ft_strlen(ev->key)
				+ ft_strlen(ev->value) + 2);
		if (!ev->env[i])
			return ;
		j = 0;
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

//Essa funcao substitui o valor da variavel se no arg for
//passado uma variavel com o mesmo nome e algum valor ou NULL
static void	var_value(int i, int j, int n, char *key, t_env *ev)
{
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

//Essa funcao cria uma nova var se a var que for passada como par
//nao existe nas env
static void	new_env(int i, int j, int n, char *key, t_env *ev)
{
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
		var_value(i, j, n, key, ev);
	ev->env[i + 1] = NULL;
	ev->len++;
}

static void	set_env(char *key, t_env *ev)
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
                return;
			replace_env(i, j, n, key, ev);
        }
		i++;
	}
	if (!ev->found)
		new_env(i, j, n, key, ev);
	ev->found = 0;
}

void	export(t_env *ev, char *var)
{
	int	i;

	i = 0;
	if (var == NULL || ft_strlen(var) == 0)
	{
		sort_env(ev->env);
		while (ev->env[i])
		{
			printf("declare -x ");
			printf("%s\n", ev->env[i]);
			i++;
		}
	}
	else
	{
		get_variable(ev, var);
		set_env(ev->key, ev);
	}
}
