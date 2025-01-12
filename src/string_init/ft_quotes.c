/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 11:28:20 by rquilami          #+#    #+#             */
/*   Updated: 2025/01/12 14:36:05 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int ft_count_quotes(char *str, int index, char c)
{
	int count;

	count = 0;
	while (str[index] && str[index] != c)
	{
		index++;
		count++;
	}
	return (count + 1);
}

void print_num(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		printf("%d\n", str[i]);
		i++;
	}
}

int ft_quotes_dup(char *str, t_words **array, int i, t_variables *vars)
{
	int index;
	int count;

	index = i;
	count = 0;
	while (str[index] && str[index] != '\"')
	{
		index++;
		count++;
	}
	vars->ext->word = calloc(sizeof(char), count + 1);
	if (vars->ext->word == NULL)	
		return (i);	
	index = 0;
	while (str[i] && str[i] != '"')
		vars->ext->word[index++] = str[i++];
	i++;
	if (str[i] && str[i] == ' ')
		vars->ext->word[index++] = ' ';
	if (vars->ext->word)
	{
		vars->ext->expanded_word = is_expanded(vars->ext->word, vars);
		insert_str_end(array, vars->ext->expanded_word, 2);
	}
	if (vars->ext->expanded_word)
	 	free(vars->ext->expanded_word);
	return (i);
}

int ft_quotes_simples(char *str, t_words **array, int i)
{
	char *word;
	int index;
	int count;

	index = i;
	count = 0;
	while (str[index] && str[index] != '\'')
	{
		index++;
		count++;
	}
	word = malloc(sizeof(char) * count + 1);
	if (!word)	
		return (0);	
	ft_memset(word, 0, count + 1);
	index = 0;
	while (str[i] && str[i] != '\'')
		word[index++] = str[i++];
	if (str[i + 1] == ' ')
		word[index++] = ' ';
	word[index] = '\0';
	if (word)
		insert_str_end(array, word, 1);
	free(word);
	return (i + 1);
}

int ft_empty(char *str, t_words **array, int i, t_variables *vars)
{
	int index;
	int count;

	index = i;
	count = 0;
	vars->ext->word_empty = NULL;
	while (str[index] && str[index] != '"' && str[index] != '\'' && str[index] != ' ')
	{
		index++;
		count++;
	}
	vars->ext->word_empty = ft_calloc(sizeof(char), 10000);
	if (!vars->ext->word_empty)
		return (0);
	i = form_word_empty(str, vars, array, i);
	return (i);
}

void get_elements(char *str, t_words **words, t_variables *vars)
{
	int i;

	i = 0;
	if (str == NULL || str[0] == '\0')
		return;
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i])
	{
		if (str[i] && str[i] == '"')
			i = ft_quotes_dup(str, words, i + 1, vars);
		else if (str[i] && str[i] == '\'')
			i = ft_quotes_simples(str, words, i + 1);
		else if (str[i])
			i = ft_empty(str, words, i, vars);
		while (str[i] != '\0' && str[i] == ' ')
			i++;
	}
}
