/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 08:36:42 by jsoares           #+#    #+#             */
/*   Updated: 2024/12/10 04:53:09 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int ft_quotes_dup(char *str, t_words **array, int i, t_variables *vars)
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
int insert_redirect(char *str, t_words **array, int i)
{
    if (str[i] && (str[i] == '|'))
    {
        insert_str_end(array, "|", 0);
        i++;
    }
    else if (str[i] && (str[i] == '>'))
    {
        if (str[i + 1] && str[i + 1] == '>')
        {
            insert_str_end(array, ">>", 0);
            i++;
        }
        else
            insert_str_end(array, ">", 0);
        i++;
    }
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

int ft_empty(char *str, t_words **array, int i, t_variables *vars)
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
    {
        i = insert_redirect(str, array, i);
        word[index++] = str[i++];
    }
    word[index] = '\0';
    if (word)
    {
        expanded_word = is_expanded(word, vars);
        insert_str_end(array, expanded_word, 2);
    }
    free(word);
    return (i);
}

void get_elements(char *str, t_words **array, t_variables *vars)
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

char *filter_string(char *str, t_variables *vars, t_words **words)
{
    //t_words *array = NULL;
    t_words *tmp;
    char *new = NULL;

    get_elements(str, words, vars);
    if (!words)
        return (NULL);
    tmp = *words;
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
