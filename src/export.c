/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 13:56:42 by rquilami          #+#    #+#             */
/*   Updated: 2024/11/19 13:06:23 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	get_variable(t_env *ev, char *var)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	ev->just_var = 0;
	ev->key = malloc(sizeof(char) * ft_strlen(var) + 1);
	ev->value = malloc(sizeof(char) * ft_strlen(var) + 1);
	while (var[i] != '=' && var[i] != 32 && var[i] != '\0' && var[i] != '$')
	{
		ev->key[i] = var[i];
		i++;
	}
	ev->key[i] = '\0';
    verfi_arg(ev);
	if (var[i] == '\0')
		ev->just_var = 1;
	set_values(ev, var, i, j);
}
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
void	verfi_arg(t_env *ev)
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
        ev->key[ev->i] == '/' || ev->key[ev->i] == '-' )
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

void	export(t_variables vars)
{
	char *var;
	var = vars.args[1];
	if (var == NULL || ft_strlen(var) == 0)
	{
		copy_env(vars.ev);
		sort_env(vars.ev->env_copy);
		print_env(vars.ev);
	}
	else
	{
		get_variable(vars.ev, var);
		set_env(vars.ev->key, vars.ev);
	}
}