/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: justinosoares <justinosoares@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 08:48:30 by jsoares           #+#    #+#             */
/*   Updated: 2024/11/19 22:11:18 by justinosoar      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

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
        if (s[i] == '\'')
            while (s[i] && s[++i] != '\'')
                ;
        else if (s[i] == '"')
            while (s[i] && s[++i] != '"')
                ;
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
        if (s[i] != c)
            count++;
        if (s[i] == '\'')
        {
            count = 0;
            while (s[i] && s[++i] != '\'')
                count++;
            strs[x] = malloc(sizeof(char) * (count + 1));
            if (!strs[x])
                return (NULL);
            x++;
        }
        else if (s[i] == '"')
        {
            count = 0;
            while (s[i] && s[++i] != '"')
                count++;
            strs[x] = malloc(sizeof(char) * (count + 1));
            if (!strs[x])
                return (NULL);
            x++;
        }
        if ((s[i] == c && i > 0 && s[i - 1] != c) || (s[i] != c && s[i + 1] == '\0'))
        {
            strs[x] = malloc(sizeof(char) * (count + 1));
            if (!strs[x])
                return (NULL);
            count = 0;
            x++;
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
        if (s[i] == '\'')
        {
            y = 0;
            while (s[++i] != '\'' && s[i])
                strs[x][y++] = s[i];
            strs[x][y] = '\0';
            //printf("dentro :%c\n", strs[x][y]);
            y = 0;
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
        printf("fora : %s\n", strs[x]);
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

int main(int ac, char **av)
{
    char **strs;
    char str[] = "'oi tudo' bem ana carla";

    strs = ft_split_aspa(str, ' ');
    //printf("%s\n", strs[atoi(av[1])]);
}