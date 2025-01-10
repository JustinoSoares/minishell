/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: justinosoares <justinosoares@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:39:26 by rquilami          #+#    #+#             */
/*   Updated: 2025/01/10 01:41:37 by justinosoar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	count_pipes(t_words *words)
{
	int	count;

	count = 0;
	while (words)
	{
		if (words->word[0] == '|')
			count++;
		words = words->next;
	}
	return (count);
}

char	**aux_split_pipe(t_words *word, char c, char **line, char *new)
{
	char	*tmp;
	int		i;

	tmp = NULL;
	i = 0;
	while (word)
	{
		if (word->word[0] == c)
		{
			line[i++] = new;
			new = NULL;
			word = word->next;
			continue ;
		}
		new = form_word(word, new, tmp);
		word = word->next;
	}
	line[i++] = new;
	line[i] = NULL;
	return (line);
}

char	**split_pipe(t_words **words, char c)
{
	char	**line;
	char	*new;
	t_words	*word;
	int		i;

	i = 0;
	new = NULL;
	word = *words;
	line = malloc(sizeof(char *) * (count_pipes(*words) + 2));
	if (!line)
		return (NULL);
	line = aux_split_pipe(word, c, line, new);
	return (line);
}

char	**init_pipe(t_words **words, t_variables *vars)
{
	char	**args;
	int		i;

	i = 0;
	args = split_pipe(words, '|');
	if (args == NULL)
		return (NULL);
	vars->quant = count_pipes(*words) + 1;
	vars->prev_fd = -1;
	vars->index = -1;
	return (args);
}
