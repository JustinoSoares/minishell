/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 08:36:42 by jsoares           #+#    #+#             */
/*   Updated: 2025/01/08 08:53:12 by jsoares          ###   ########.fr       */
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

int ft_quotes_dup(char *str, t_words **array, int i, t_variables *vars)
{
    char *word;
    char *expanded_word;
    int index = i;
    int count = 0;

    count = ft_count_quotes(str, i + 1, '"');
    word = malloc(sizeof(char) * count + 1);
    if (!word)
        return (0);
    ft_memset(word, 0, count + 1);
    index = 0;
    while (str[i] && str[i] != '"')
        word[index++] = str[i++];
    i++;
    if (str[i] && str[i] == ' ')
        word[index++] = ' ';
    word[index++] = '\0';
    if (word)
    {
        expanded_word = is_expanded(word, vars);
        insert_str_end(array, expanded_word, 2);
    }
    free(word);
    free(expanded_word);
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
    if (str[i + 1] == ' ')
        word[index++] = ' ';
    word[index] = '\0';
    if (word)
        insert_str_end(array, word, 1);
    free(word);
    return (i + 1);
}

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

int form_word_empty(char *str, t_variables *vars, t_words **array, int i, char *word)
{
    char *expanded_word;
    int index;
    expanded_word = NULL;

    index = 0;
    while (str[i] && str[i] != '"' && str[i] != '\'' && str[i] != ' ')
    {
        i = insert_redirect(str, array, i);
        word[index++] = str[i++];
    }
    if (str[i] == ' ')
        word[index++] = ' ';
    word[index] = '\0';
    if (word)
    {
        expanded_word = is_expanded(word, vars);
        insert_str_end(array, expanded_word, 0);
    }
    free(expanded_word);
    free(word);
    return (i);
}

int ft_empty(char *str, t_words **array, int i, t_variables *vars)
{
    char *word;

    int index;
    int count;

    index = i;
    count = 0;
    word = NULL;
    while (str[index] && str[index] != '"' && str[index] != '\'' && str[index] != ' ')
    {
        index++;
        count++;
    }
    word = malloc(sizeof(char) * count + 2);
    if (!word)
        return (0);
    ft_memset(word, 0, count + 2);
    i = form_word_empty(str, vars, array, i, word);
    return (i);
}

void get_elements(char *str, t_words **words, t_variables *vars)
{
    int i = 0;

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
    char *final_str;

    new = NULL;
    final_str = NULL;
    get_elements(str, words, vars);
    if (!words || !*words)
        return (NULL);
    tmp = *words;
    while (tmp != NULL)
    {
        if (tmp->word)
        {
            char *temp = ft_strjoin(new, tmp->word);
            if (new)
                free(new);
            new = temp;
        }
        tmp = tmp->next;
    }
    return (end_filter(new, final_str));
}
