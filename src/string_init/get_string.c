/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_string.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:32:47 by jsoares           #+#    #+#             */
/*   Updated: 2024/12/04 16:35:01 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char *get_word_full(char *str, int start, int is_space)
{
    char *new;
    int i = 0;
    int size = 0;

    while (str[size] && (str[size] != 32 || is_space == 1) && str[size] != '"' && str[size] != '\'')
    {
        if (ft_isalnum(str[size]) || str[size] == '_' || (str[size] == 32 && is_space == 1))
            size++;
        else
            break;
    }
    new = malloc(sizeof(char) * (size + 1));
    while (str[start] && (str[start] != 32 || is_space == 1) && str[start] != '"' && str[start] != '\'')
    {
        if (ft_isalnum(str[start]) || str[start] == '_' || (str[start] == 32 && is_space == 1))
            new[i++] = str[start];
        else
            break;
        start++;
    }
    new[i] = '\0';
    return (new);
}

char *get_word_s(char *str, int start)
{
    char *new;
    int i = 0;
    int size = start;
    int len = 0;

    while (str[size] && str[size] != '\'')
    {
        size++;
        len++;
    }
    new = malloc(sizeof(char) * (size + 1));
    while (str[start] && str[start] != '\'')
    {
        new[i++] = str[start];
        start++;
    }
    new[i] = '\0';
    return (new);
}

char *get_word(char *str, int start)
{
    char *new;
    int i = 0;
    int size = start;
    int len = 0;

    while (str[size] && str[size] != 32)
    {
        if (ft_isalnum(str[size]) || str[size] == '_')
        {
            size++;
            len++;
        }
        else
            break;
    }
    new = malloc(sizeof(char) * (len + 1));
    while (str[start] && str[start] != 32)
    {
        if (ft_isalnum(str[start]) || str[start] == '_')
            new[i++] = str[start];
        else
            break;
        start++;
    }
    new[i] = '\0';
    return (new);
}

char *get_word_d(char *str, int start)
{
    char *new;
    char *macro;
    int i = 0;
    int size = start;
    int len = 0;

    while (str[size] && str[size] != '"')
    {
        size++;
        len++;
    }
    new = malloc(sizeof(char) * (len + 1));
    if (!new)
        return NULL; // Check for allocation failure

    while (str[start] && str[start] != '"')
    {
        new[i++] = str[start];
        start++;
    }
    new[i] = '\0';
    return new;
}

char *get_word_empty(char *str, int start)
{
    char *new;
    char *macro;
    int i = 0;
    int size = start;
    int len = 0;

    while (str[size] && str[size] != '"' && str[size] != 32 && str[size] != '\'')
    {
        size++;
        len++;
    }
    new = malloc(sizeof(char) * (len + 1));
    if (!new)
        return (NULL); // Check for allocation failure

    while (str[start] && str[start] != '"' && str[start] != 32 && str[start] != '\'')
    {
        new[i++] = str[start];
        start++;
    }
    new[i] = '\0';
    return new;
}