/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 08:36:42 by jsoares           #+#    #+#             */
/*   Updated: 2024/12/06 16:09:59 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int ft_quotes_dup(char *str, t_words **array, int i)
{
    char *word;
    char *expanded_word;
    int index = i;
    int count = 0;

    while (str[index] && str[index] != '"')
    {
        index++;
        count++;
    }
    word = malloc(sizeof(char) * count + 1);
    if (!word)
        return (0);
    ft_memset(word, 0, count + 1);
    index = 0;
    while (str[i] && str[i] != '"')
        word[index++] = str[i++];
    word[index] = '\0';
    if (word)
    {
        expanded_word = is_expanded(word);
        insert_str_end(array, expanded_word, 2);
    }
    free(word);
    return (i + 1);
}

int ft_quotes_simples(char *str, t_words **array, int i)
{
    char *word;
    int index = i;
    int count = 0;

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
    word[index] = '\0';
    if (word)
        insert_str_end(array, word, 1);
    free(word);
    return (i + 1);
}

int ft_empty(char *str, t_words **s_array, int i)
{
    char *word;
    char *expanded_word;
    int index = i;
    int count = 0;

    while (str[index] && str[index] != 32 && str[index] != '"' && str[index] != '\'')
    {
        index++;
        count++;
    }
    word = malloc(sizeof(char) * count + 1);
    if (!word)
        return (0);
    ft_memset(word, 0, count + 1);
    index = 0;
    while (str[i] && str[i] != 32 && str[i] != '"' && str[i] != '\'')
        word[index++] = str[i++];
    word[index] = '\0';
    if (word)
    {
        expanded_word = is_expanded(word);
        insert_str_end(s_array, expanded_word, 0);
    }
    free(word);
    return (i + 1);
}

void get_elements(char *str, t_words **array)
{
    int i = 0;
    char *word;
    char *expanded_word;
    char *expanded_empty;
    char *expanded_simple;

    while (str[i] && str[i] == ' ')
        i++;
    while (str[i])
    {
        if (str[i] && str[i] == '"')
            i = ft_quotes_dup(str, array, i + 1);
        else if (str[i] && str[i] == '\'')
            i = ft_quotes_simples(str, array, i + 1);
        else
            i = ft_empty(str, array, i);
    }
}
char *filter_string(char *str)
{
    t_words *array = NULL;
    t_words *tmp;
    char *new;

    get_elements(str, &array);
    new = ft_strdup("");
    tmp = array;
    while (tmp != NULL)
    {
        new = ft_strjoin(new, tmp->word);
        if (tmp->next)
            new = ft_strjoin(new, " ");
        tmp = tmp->next;
    }
    new = ft_strjoin(new, "\0");
    return (new);
}
