/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 08:36:42 by jsoares           #+#    #+#             */
/*   Updated: 2025/01/10 16:09:18 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int redirect_right(char *str, int i, t_words **array)
{
	if (str[i + 1] && str[i + 1] == '>')
	{
		insert_str_end(array, ">>", 0);
		i++;
	}
	else
		insert_str_end(array, ">", 0);
	i++;
	return (i);
}

void free_wordss(t_words *word)
{
	t_words *tmp;

	while (word)
	{
		tmp = word;
		word = word->next;
		free(tmp->word);
		free(tmp);
	}
}

int insert_redirect(char *str, t_words **array, int i)
{
	if (str[i] && (str[i] == '|'))
	{
		insert_str_end(array, "|", 0);
		i++;
	}
	else if (str[i] && (str[i] == '>'))
		i = redirect_right(str, i, array);
	else if (str[i] && (str[i] == '<'))
	{
		if (str[i + 1] && str[i + 1] == '<')
		{
			insert_str_end(array, "<<", 0);
			i++;
		}
		else
			insert_str_end(array, "<", 0);
		i++;
	}
	return (i);
}

int form_word_empty(char *str, t_variables *vars, t_words **array, int i)
{
	char *expanded_word;
	int index;

	expanded_word = NULL;
	index = 0;
	while (str[i] && str[i] != '"' && str[i] != '\'' && str[i] != ' ')
	{
		i = insert_redirect(str, array, i);
		vars->ext->word_empty[index++] = str[i++];
	}
	if (str[i] == ' ')
		vars->ext->word_empty[index++] = ' ';
	vars->ext->word_empty[index] = '\0';
	if (vars->ext->word_empty)
	{
		expanded_word = is_expanded(vars->ext->word_empty, vars);
		insert_str_end(array, expanded_word, 0);
	}
	free(expanded_word);
	free(vars->ext->word_empty);
	return (i);
}


char *end_filter(char *new, char *final_str)
{
	if (new)
	{
		final_str = ft_strjoin(new, "\0");
		free(new);
		return (final_str);
	}
	return (NULL);
}

char *filter_string(char *str, t_variables *vars, t_words **words)
{
	t_words *tmp;
	char *new;
	char *temp;

	new = NULL;
	if (str == NULL || *str == '\0')
		return (NULL);
	get_elements(str, words, vars);
	if (!words || !*words)
		return (NULL);
	tmp = *words;
	while (tmp != NULL)
	{
		if (tmp->word)
		{
			temp = ft_strjoin(new, tmp->word);
			if (new)
				free(new);
			new = temp;
		}
		tmp = tmp->next;
	}
	return (end_filter(new, NULL));
}
