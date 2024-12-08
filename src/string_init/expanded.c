/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanded.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:38:08 by jsoares           #+#    #+#             */
/*   Updated: 2024/12/08 02:28:38 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int size_expanded(char *str)
{
    int i = 0;
    int size = 0;
    char *macro;
    char *word;

    while (str[i])
    {
        if (str[i] == '$')
        {
            word = get_word(str, i + 1);
            macro = getenv(word);
            if (macro)
            {
                size += strlen(macro);
            }
            i += strlen(word);
            free(word); // Libere a memória se get_word alocar
        }
        else
        {
            i++;
            size++;
        }
    }
    return size;
}

char *is_expanded(char *str)
{
    int i = 0;
    int j = 0;
    char *new;
    char *word;
    char *macro;

    new = malloc(sizeof(char) * size_expanded(str) + 1);
    new = ft_memset(new, 0, size_expanded(str) + 1);
    if (new == NULL)
        return NULL;
    while (str[i])
    {
        if (str[i] && str[i] == '$' && str[i + 1])
        {
            word = get_word(str, i + 1);
            if (word == NULL)
                return NULL;
            macro = getenv(word);
            if (macro && strlen(macro) > 0)
            {
                strcat(new, macro); // Use strcat com cuidado
                j += ft_strlen(macro);
                i += ft_strlen(word) + 1;
            }
            else
                i += strlen(word) + 1;
            free(word);
        }
        else if (str[i] && str[i] == '$' && str[i + 1] == '\0')
            i++;
        else if (str[i])
            new[j++] = str[i++];
    }
    new[j] = '\0';
    return (new);
}
