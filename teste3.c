/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 08:48:30 by jsoares           #+#    #+#             */
/*   Updated: 2024/11/22 16:46:14 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

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

char *print_var_macro(char *str, int i)
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
    return (macro);
}
char *ft_strcat_index(char *str, char *str2, int index)
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
    int i = 0;
    int j = 0;
    char *new;
    char *macro;
    new = malloc(sizeof(char) * (ft_strlen(str) + 1));
    while (str[i])
    {
        if (str[i] == '$' && str[i + 1] != 32 && str[i + 1] != '"' && str[i + 1] != '\'')
        {
            macro = getenv(get_word(str, i + 1));
            if (macro && ((is_in_aspas(str, i) == 1) || count_elements(str, '\'') == 0))
                str = ft_strcat_index(str, macro, i);
            j++;
        }
        i++;
    }
    new = str;
    return (new);
}

int main(void)
{
    char *str = "echo $HOME";
    char *new = is_expanded(str);
    printf("%s\n", new);
    return (0);
}