/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsoares <jsoares@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 08:46:13 by jsoares           #+#    #+#             */
/*   Updated: 2024/12/04 08:47:02 by jsoares          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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