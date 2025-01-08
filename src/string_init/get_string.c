/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_string.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:32:47 by jsoares           #+#    #+#             */
/*   Updated: 2025/01/07 15:33:29 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
    printf("get2: %s \n", new);
}

char *main_word(char *str, int len, int start, int i)
{
    char *new;
    new = malloc(sizeof(char) * (len + 1));
    if (!new)
        return (NULL);
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

char *get_word(char *str, int start)
{
    int i;
    int size;
    int len;

    len = 0;
    i = 0;
    size = start;
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
    return (main_word(str, len, start, i));
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
        return NULL;
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
        return (NULL);

    while (str[start] && str[start] != '"' && str[start] != 32 && str[start] != '\'')
    {
        new[i++] = str[start];
        start++;
    }
    new[i] = '\0';
    return new;
}
