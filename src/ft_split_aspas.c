/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_aspas.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: justinosoares <justinosoares@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 08:48:30 by jsoares           #+#    #+#             */
/*   Updated: 2024/11/21 07:34:53 by justinosoar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int next_exist(const char *str, char c, int i)
{
    while (str[i])
    {
        if (str[i] == c)
            return (i);
        i++;
    }
    return (0);
}

static int ft_count_words(const char *s, char c)
{
    int words;
    int i;

    words = 0;
    i = 0;
    while (s[i])
    {
        if (i == 0 && s[i] != c)
            words++;
        if (s[i] == '\'' && next_exist(s, '\'', i + 1))
            while (s[i] && s[++i] != '\'')
                ;
        else if (s[i] == '"' && next_exist(s, '"', i + 1))
            while (s[i] && s[++i] != '"')
                ;
        if (s[i] != c && s[i + 1] == '\0')
            words++;
        if (i > 0 && s[i] != c && s[i - 1] == c)
            words++;
        i++;
    }
    return (words);
}

static char **ft_malloc_strs(char **strs, const char *s, char c)
{
    int count;
    int i;
    int x;

    count = 0;
    i = 0;
    x = 0;
    while (s[i])
    {
        if (s[i] == '\'' && next_exist(s, '\'', i + 1))
        {
            count = 0;
            while (s[i] && s[++i] != '\'')
                count++;
            strs[x] = malloc(sizeof(char) * (count + 1));
            if (!strs[x])
                return (NULL);
        }
        else if (s[i] == '"' && next_exist(s, '"', i + 1))
        {
            count = 0;
            while (s[i] && s[++i] != '"')
                count++;
            strs[x] = malloc(sizeof(char) * (count + 1));
            if (!strs[x])
                return (NULL);
        }
        else
        {
            if (s[i] != c && s[i])
                count++;
            if ((s[i] == c && i > 0 && s[i - 1] != c) || (s[i] != c && s[i + 1] == '\0'))
            {
                strs[x] = malloc(sizeof(char) * (count + 1));
                if (!strs[x])
                    return (NULL);
                count = 0;
                x++;
            }
        }
        i++;
    }
    return (strs);
}

static char **ft_cpy_strs(char **strs, const char *s, char c)
{
    int i;
    int x;
    int y;

    i = 0;
    x = 0;
    y = 0;
    while (s[i])
    {
        if (s[i] == '\'' && next_exist(s, '\'', i + 1))
        {
            y = 0;
            while (s[++i] != '\'' && s[i])
                strs[x][y++] = s[i];
            strs[x][y] = '\0';
        }
        else if (s[i] == '"' && next_exist(s, '"', i + 1))
        {
            y = 0;
            while (s[++i] != '"' && s[i])
                strs[x][y++] = s[i];
            strs[x][y] = '\0';
        }
        else
        {
            if (s[i] != c)
                strs[x][y++] = s[i];
            if (s[i] != c && s[i + 1] == '\0')
                strs[x][y] = '\0';
            if (s[i] == c && i > 0 && s[i - 1] != c)
            {
                strs[x][y] = '\0';
                x++;
                y = 0;
            }
        }
        i++;
    }
    return (strs);
}

static char **ft_merror(char **strs)
{
    int i;

    i = 0;
    while (strs[i])
    {
        free(strs[i]);
        strs[i] = NULL;
        i++;
    }
    free(strs);
    return (NULL);
}

char **ft_split_aspa(char const *s, char c)
{
    char **strs;
    int wordcount;

    if (!s)
    {
        strs = malloc(sizeof(char) * 1);
        if (!strs)
            return (NULL);
        *strs = NULL;
        return (strs);
    }
    wordcount = ft_count_words(s, c);
    printf("%d\n", wordcount);
    strs = malloc(sizeof(*strs) * (wordcount + 1));
    if (!strs)
        return (NULL);
    if (ft_malloc_strs(strs, s, c))
    {
        ft_cpy_strs(strs, s, c);
        strs[wordcount] = NULL;
    }
    else
        strs = ft_merror(strs);
    return (strs);
}