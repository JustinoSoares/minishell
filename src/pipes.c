/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:39:26 by rquilami          #+#    #+#             */
/*   Updated: 2025/01/12 18:15:03 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	count_pipes(t_words *words)
{
	int	count;

	count = 0;
	while (words)
	{
		if (words->word[0] == '|' && words->type == 0)
			count++;
		words = words->next;
	}
	return (count);
}
void	free_split_pipe(char **line)
{
	int	i;

	if (!line)
		return ;
	i = 0;
	while (line[i])
	{
		free(line[i]);
		i++;
	}
	free(line);
}

char	**aux_split_pipe(t_words *word, char c, char **line, char *new)
{
	char	*tmp;
	int		i;

	tmp = NULL;
	i = 0;
	while (word)
	{
		if (word->word[0] == c && word->type == 0)
		{
			line[i++] = new;
			new = NULL;
			word = word->next;
			continue ;
		}
		new = form_word(word, new, tmp);
		if (!new)
		{
			free_split_pipe(line);
			return (NULL);
		}
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
	int		count;

	new = NULL;
	word = *words;
	count = count_pipes(*words);
	line = ft_calloc(sizeof(char *), (count + 2));
	if (!line)
		return (NULL);
	line = aux_split_pipe(word, c, line, new);
	if (!line)
	{
		free_split_pipe(line);
		return (NULL);
	}
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
