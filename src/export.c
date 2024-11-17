/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rquilami <rquilami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 13:56:42 by rquilami          #+#    #+#             */
/*   Updated: 2024/11/17 13:17:25 by rquilami         ###   ########.fr       */
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
            printf("export: `%s\' not a valid identifier\n", ev->key);
            return;
        }
       /* if (ev->key[i] == '(' || ev->key[i] == ')')
        {
            printf("syntax error near unexpected token `%c\'\n", ev->key[i]);
            return;
        }*/
        i++;
    }
}

static void print_env(t_env *ev)
{
	int		i;
	int		j;

	i = 0;
	while (ev->env_copy[i] != NULL)
	{
		j = 0;
		printf("declare -x ");
		while (ev->env_copy[i][j] != '\0')
		{
			if (ev->env_copy[i][j] == '=')
			{
				printf("%c", ev->env_copy[i][j]);
				printf("\"");
				j++;
				while (ev->env_copy[i][j] != '\0')
				{
					printf("%c", ev->env_copy[i][j]);
					j++;
				}
				printf("\"");
			}
			else
			{
				printf("%c", ev->env_copy[i][j]);
				j++;
			}
		}
		printf("\n");
		i++;
	}
}

void	export(t_env *ev, char *var)
{
	int	i;

	i = 0;
	if (var == NULL || ft_strlen(var) == 0)
	{
		copy_env(ev);
		sort_env(ev->env_copy);
		print_env(ev);
	}
	else
	{
		get_variable(ev, var);
		set_env(ev->key, ev);
	}
}
