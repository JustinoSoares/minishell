/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 08:36:42 by jsoares           #+#    #+#             */
/*   Updated: 2024/12/08 09:22:16 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int ft_quotes_dup(char *str, t_words **array, int i, t_variables vars)
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
        expanded_word = is_expanded(word, vars);
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

int ft_empty(char *str, t_words **array, int i, t_variables vars)
{
    char *word;
    char *expanded_word;
    int index = i;
    int count = 0;

    while (str[index] && str[index] != '"' && str[index] != '\'' && str[index] != ' ')
    {
        index++;
        count++;
    }
    word = malloc(sizeof(char) * count + 1);
    if (!word)
        return (0);
    ft_memset(word, 0, count + 1);
    index = 0;
    while (str[i] && str[i] != '"' && str[i] != '\'' && str[i] != ' ')
        word[index++] = str[i++];
    word[index] = '\0';
    if (word)
    {
        expanded_word = is_expanded(word, vars);
        insert_str_end(array, expanded_word, 2);
    }
    free(word);
    return (i);
}

void get_elements(char *str, t_words **array, t_variables vars)
{
    int i = 0;
    char *word;

    while (str[i] && str[i] == ' ')
        i++;
    while (str[i])
    {
        if (str[i] && str[i] == '"')
            i = ft_quotes_dup(str, array, i + 1, vars);
        else if (str[i] && str[i] == '\'')
            i = ft_quotes_simples(str, array, i + 1);
        else if (str[i])
            i = ft_empty(str, array, i, vars);
        while (str[i] && str[i] == ' ')
            i++;
    }
}

int count_stack(t_words *array)
{
    int count = 0;
    t_words *tmp = array;

    while (tmp != NULL)
    {
        count++;
        tmp = tmp->next;
    }
    return (count);
}



char *filter_string(char *str, t_variables vars)
{
    t_words *array = NULL;
    t_words *tmp;
    char *new = NULL;

    get_elements(str, &array, vars);
    if (!array)
        return (NULL);
    tmp = array;
    while (tmp != NULL)
    {
        new = ft_strjoin(new, tmp->word);
        if (tmp->next)
            new = ft_strjoin(new, " ");
        tmp = tmp->next;
    }
    new = ft_strjoin(new, "\0");
    free_words(array);
    return (new);
}
