/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: justinosoares <justinosoares@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 08:48:30 by jsoares           #+#    #+#             */
/*   Updated: 2024/11/24 07:40:22 by justinosoar      ###   ########.fr       */
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

char *is_expanded(char *str)
{
    char *macro;
    int i = 0;
    while (str[i])
    {
        if (str[i] == '"')
        {
            i++;
            while (str[i] && str[i] != '"')
            {
                if (str[i] == '$' && str[i + 1] != 32 && str[i + 1] != '"' && str[i + 1] != '\'' && str[i + 1] != '\0')
                {
                    macro = getenv(get_word(str, i + 1));
                    if (macro)
                    {
                        str = ft_strcat_macro(str, macro, i, ft_strlen(get_word(str, i + 1)) + 1);
                        i += ft_strlen(get_word(str, i + 1));
                    }
                    else
                        i += ft_strlen(get_word(str, i + 1));
                }
                else
                    i++;
            }
        }
        else if (str[i] == '\'')
        {
            while (str[++i] && str[i] != '\'')
                i++;
        }
        else
        {
            if (str[i] == '$' && str[i + 1] != 32 && str[i + 1] != '"' && str[i + 1] != '\'' && str[i + 1] != '\0')
            {
                macro = getenv(get_word(str, i + 1));
                if (macro)
                {
                    str = ft_strcat_macro(str, macro, i, ft_strlen(get_word(str, i + 1)) + 1);
                    i += ft_strlen(get_word(str, i + 1));
                }
                else
                    i += ft_strlen(get_word(str, i + 1));
            }
            else
                i++;
        }
    }
    return (str);
}

int main(void)
{
    char *str = "echo '$HOME' CAntar";

    char *new = is_expanded(str);
    // str = ft_strcat_macro(str, "MIlaa", 5, 5);
    printf("%s\n", new);
    return (0);
}