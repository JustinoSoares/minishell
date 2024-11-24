/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 08:48:30 by jsoares           #+#    #+#             */
/*   Updated: 2024/11/24 15:23:27 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int count_elements(char *str, char c)
{
    int count = 0;
    while (*str)
    {
        if (*str == c)
            count++;
        str++;
    }
    return (count);
}

char *get_word(char *str, int start)
{
    char *new;
    int i = 0;
    int size = 0;

    while (str[size] && str[size] != 32 && str[size] != '"' && str[size] != '\'')
    {
        if (ft_isalnum(str[size]) || str[size] == '_')
            size++;
        else
            break;
    }
    new = malloc(sizeof(char) * (size + 1));
    while (str[start] && str[start] != 32 && str[start] != '"' && str[start] != '\'')
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

int count_until(char *str, char c, int index)
{
    int count = 0;
    int i = 0;
    while (i < index)
    {
        if (str[i] == c)
            count++;
        i++;
    }
    return (count);
}

int get_last_in(char *str, char c, int index)
{
    int i = 0;
    int last = 0;
    int back = index;
    while (i < index)
    {
        if (str[i] == c)
            last = i;
        i++;
    }
    back = count_until(str, c, back);
    if (back % 2 != 0)
        return (last);
    return (-1);
}

int is_in_aspas(char *str, int index)
{
    int start;
    int dup = get_last_in(str, '"', index);
    int simple = get_last_in(str, '\'', index);
    if (dup != -1)
    {
        start = get_last_in(str, '\'', dup);
        if (start != -1)
            return (0);
        return (1);
    }
    if (simple != -1)
    {
        start = get_last_in(str, '"', simple);
        if (start != -1)
            return (1);
        return (0);
    }
    return (1);
}

char *ft_strcat_macro(char *str, char *str2, int index, int size_word)
{
    char *new;
    int i = 0;
    int j = 0;
    int x = 0;
    int len = strlen(str) + strlen(str2);
    new = malloc(sizeof(char) * (strlen(str) + strlen(str2) + 1));
    while (str[i] && i < index)
    {
        new[i] = str[i];
        i++;
    }
    x = i;
    while (str2[j])
    {
        new[i] = str2[j];
        i++;
        j++;
    }
    x += size_word;
    while (str[x])
    {
        new[i] = str[x];
        i++;
        x++;
    }
    return (new);
}

int count_words(char *str)
{
    int count = 0;
    int i = 0;
    while (str[i])
    {
        if (str[i] == 32 && str[i] != '$')
            count++;
        i++;
    }
    return (count + 1);
}
int is_valid_macro_char(char str)
{
    while (str != 32 && str != '$' && str != '"' && str != '\'' && str != '\0' && str != '$')
        return (1);
    return (0);
}
char *ft_strncpy(char *s1, char *s2, int n)
{
    int i;

    i = -1;
    while (++i < n && s2[i])
        s1[i] = s2[i];
    s1[i] = '\0';
    return (s1);
}

char **ft_split_new(char *s)
{
    int i = 0;
    int k = 0;
    int j = 0;
    char **split;

    split = malloc(sizeof(char *) * 256);
    if (!split)
        return (NULL);
    while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
        i++;
    while (s[i])
    {
        j = 0;
        split[k] = (char *)malloc(sizeof(char) * 4096);
        if (!split[k])
            return (NULL);
        while (s[i] != ' ' && s[i] != '\t' && s[i] != '\n' && s[i] && s[i] != '$')
            split[k][j++] = s[i++];
        while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n' || s[i] == '$')
            i += 1;
        split[k][j] = '\0';
        k += 1;
    }
    split[k] = NULL;
    return (split);
}

char *is_expanded(char *str)
{
    char *macro;
    char **each_word;
    int i = 0;

    each_word = ft_split_new(str);
    while (each_word[i])
    {
        if (each_word[i][0] == '$')
        {
            macro = getenv(get_word(each_word[i], 1));
            each_word[i] = ft_strdup(macro);
        }
        printf("%s\n", each_word[i]);
        i++;
    }
    return (str);
}

int main(void)
{
    char *str = "echo '-$HOME $USER' CAntar";

    char *new = is_expanded(str);
    // str = ft_strcat_macro(str, "MIlaa", 5, 5);
    printf("%d\n", count_words(str));
    return (0);
}