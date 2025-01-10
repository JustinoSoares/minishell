/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: justinosoares <justinosoares@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 13:56:42 by rquilami          #+#    #+#             */
/*   Updated: 2025/01/09 21:17:26 by justinosoar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	verfi_arg(t_env *ev)
{
	ev->i = 0;
	while (ev->key[ev->i])
	{
		if (ev->key[ev->i] == '%' || ev->key[ev->i] == '#'
			|| ev->key[ev->i] == '{' || ev->key[ev->i] == '}'
			|| ev->key[ev->i] == ':' || ev->key[ev->i] == '?'
			|| ev->key[ev->i] == ';' || ev->key[ev->i] == '@'
			|| ev->key[ev->i] == ';' || ev->key[ev->i] == '@'
			|| ev->key[ev->i] == '+' || ev->key[ev->i] == '*'
			|| ev->key[ev->i] == ',' || ev->key[ev->i] == '.'
			|| ev->key[ev->i] == '^' || ev->key[ev->i] == '~'
			|| ev->key[ev->i] == '/' || ev->key[ev->i] == '-')
		{
			write(2, "export: not a valid identifier\n", 31);
			return ;
		}
		if (ev->key[ev->i] == '(' || ev->key[ev->i] == ')')
		{
			write(2, "syntax error near unexpected token\n", 35);
			return ;
		}
		ev->i++;
	}
}

char	*replace_space(char *s, char c)
{
	int		i;
	char	quote;

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

static char	*word_with_quotes(char *var, t_words *tmp, char *quotes)
{
	char	*temp;

	temp = ft_strjoin(var, quotes);
	free(var);
	var = temp;
	temp = ft_strjoin(var, tmp->word);
	free(var);
	var = temp;
	temp = ft_strjoin(var, quotes);
	free(var);
	var = temp;
	return (var);
}

static char	*args_export(t_words **words)
{
	char	*var;
	t_words	*tmp;

	tmp = *words;
	var = NULL;
	if (!tmp || !tmp->next)
		return (NULL);
	tmp = tmp->next;
	var = ft_strjoin(var, tmp->word);
	if (tmp->next)
	{
		tmp = tmp->next;
		if (tmp->type == 1)
			var = word_with_quotes(var, tmp, "'");
		else if (tmp->type == 2)
			var = word_with_quotes(var, tmp, "\"");
	}
	return (var);
}

void	get_variable(t_env *ev, t_words **words)
{
	char	**split;
	char	*var;
	int		pos_value;

	var = args_export(words);
	if (!var)
	{
		export(ev, NULL, NULL);
		return ;
	}
	ev->i = 0;
	ev->just_var = 0;
	ev->key = ft_key(var);
	if (ft_value(var, pos_value) == NULL)
		ev->just_var = 1;
	else
		ev->value = ft_value(var, pos_value);
	verfi_arg(ev);
	export(ev, ev->key, ev->value);
	free(ev->key);
	free(ev->value);
	free(var);
}
