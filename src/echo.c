/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:38:25 by jsoares           #+#    #+#             */
/*   Updated: 2024/11/15 13:11:55 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
        if (ft_isalnum(str[size]))
            size++;
        else
            break;
    }
    new = malloc(sizeof(char) * (size + 1));
    while (str[start] && str[start] != 32 && str[start] != '"' && str[start] != '\'')
    {
        if (ft_isalnum(str[start]))
            new[i++] = str[start];
        else
            break;
        start++;
    }
    new[i] = '\0';
    return (new);
}

int print_var(char *str, int i)
{
    char *macro;
    if (str[i] == '$' && str[i + 1] == '?')
    {
        printf("0");
        i += 2;
    }
    else if (str[i] == '$' && str[i + 1] != 32 && str[i + 1] != '"' && str[i + 1] != '\'' && str[i + 1] != '\0')
    {
        macro = getenv(get_word(str, i + 1));
        if (macro && ((is_in_aspas(str, i) == 1) || count_elements(str, '\'') == 0))
        {
            printf("%s", macro);
            i += ft_strlen(get_word(str, i + 1));
        }
        else if (!macro)
            i += ft_strlen(get_word(str, i + 1));
        else
            printf("%c", str[i++]);
    }
    return (i);
}

int is_duplas(char *str, int i)
{
    int get = 0;
    while (str[++i] && (str[i] != '"' || str[i - 1] == '\\') && str[i] != '|')
    {
        get = i;
        i = print_var(str, i);
        if (i == get)
            printf("%c", str[i]);
    }
    return (i);
}

int is_simples(char *str, int i)
{
    while (str[++i] && str[i] != '\'' && str[i] != '|')
        printf("%c", str[i]);
    return (i);
}

char *str_delimited(char *str)
{
    int i = 0;
    int j = 0;
    int len = 0;
    while (str[i])
    {
        if (str[i] == '|' && is_in_aspas(str, i) == 1)
            len = i;
        i++;
    }
    char *new = malloc(sizeof(char) * len);
    i = 0;
    while (i < len)
    {
        new[i] = str[i];
        i++;
    }
    new[i] = '\0';
    return (new);
}

void ft_echo(t_variables vars)
{
    int i = 0;
    int get = 0;
    char *str;

    str = vars.line + (start_write(vars.line, vars.args[0]) + new_line(vars.args[1]));
    if (aspas_error(str, true))
        return;
    while (str[i] && str[i] != '|')
    {
        i = is_contra_barra(str, i);
        if (str[i] == '"')
            i = is_duplas(str, i);
        else if (str[i] == '\'')
            while (str[++i] && str[i] != '\'' && str[i] != '|')
                printf("%c", str[i]);
        else
        {
            get = i;
            i = print_var(str, i);
            if (get == i)
                printf("%c", str[i]);
            i++;
        }
    }
}
