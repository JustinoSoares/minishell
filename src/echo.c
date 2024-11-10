/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:38:25 by jsoares           #+#    #+#             */
/*   Updated: 2024/11/10 17:30:19 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

char *get_word(char *str, int start)
{
    char *new;
    int i = 0;
    int size = 0;

    while (str[size] && str[size] != 32 && str[size] != '"' && str[size] != '\'')
    {
        if (ft_isalpha(str[size]))
            size++;
        else
            break;
    }
    new = malloc(sizeof(char) * (size + 1));
    while (str[start] && str[start] != 32 && str[start] != '"' && str[start] != '\'')
    {
        if (ft_isalpha(str[start]))
            new[i++] = str[start];
        else
            break;
        start++;
    }
    new[i] = '\0';
    return (new);
}

int is_in(char *str, char c, int index)
{
    int i = 0;
    int last = 0;
    while (i < index)
    {
        if (str[i] == c)
            last++;
        i++;
    }
    if (last % 2 == 0)
        return (0);
    return (1);
}

int is_in_in(char *str, char in, char out, int index)
{
    int i = 0;
    int what = 3;
    if (count_elements(str, in) && count_elements(str, out))
    {
        while (i < index)
        {
            if (str[i] == out)
                what = 0;
            else if ((str[i] == in))
                what = 1;
            i++;
        }
    }
    return (what);
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

int aspas_error(char *str)
{
    int i = 0;
    int duplas = 0;
    int simples = 0;
    int mutex = 0;
    while (str[i])
    {
        if (is_in_aspas(str, i) == 1)
        {
            if (str[i] == '"')
            {
                duplas++;
                if (mutex == 0)
                    mutex = 1;
                else
                    mutex = 0;
            }
        }
        if (str[i] == '\'' && mutex == 0)
            simples++;
        i++;
    }
    if (duplas % 2 != 0 || simples % 2 != 0)
        return (1);
    return (0);
}

int print_var(char *str, int i)
{
    char *macro;
    if (str[i] == '$' && str[i + 1] != 32 && str[i + 1] != '"' && str[i + 1] != '\'' && str[i + 1] != '\0')
    {
        macro = getenv(get_word(str, i + 1));
        if (macro && ((is_in_aspas(str, i) == 1) || count_elements(str, '\'') == 0))
        {
            printf("%s", macro);
            i += ft_strlen(get_word(str, i + 1)) + 1;
        }
        else if (!macro)
            i += ft_strlen(get_word(str, i + 1)) + 1;
        else
            printf("%c", str[i++]);
    }
    return (i);
}

void ft_echo(char *str)
{
    int i = 0;

    if (aspas_error(str))
    {
        printf("Error: invalid number of quotes\n");
        return;
    }
    while (str[i] && str[i] != '|' && (str[i] != ';' || (str[i] == ';' && is_in(str, '"', i) == 1)))
    {
        if (str[i++] == '"')
        {
            while (str[i] != '"' && str[i])
            {
                i = print_var(str, i);
                if ((str[i] == 92 && str[i + 1] == '"') || (str[i] == 92 && str[i + 1] == '\''))
                    i++;
                else
                    printf("%c", str[i++]);
            }
        }
        /*else if (str[i] == '"' && count_until(str, '"', i + 1) % 2 == 0)
            i++;
        else if (str[i] == '"' && (get_last_in(str, '\'', i) != -1))
            printf("%c", str[i++]);
        else if ((str[i] == '\'' && get_last_in(str, '"', i) != -1))
            printf("%c", str[i++]);

        else if ((str[i] == '"' && str[i - 1] != 92) || (str[i] == '\'' && str[i - 1] != 92))
            i++;*/
        else
            printf("%c", str[i++]);
    }
    printf("\n");
}
